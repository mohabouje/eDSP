/**
 * Copyright (C) 2019 mboujemaoui
 * 
 * This file is part of eDSP.
 * 
 * eDSP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * eDSP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with eDSP.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "io.hpp"
#include "boost_numpy_dependencies.hpp"

#define ENABLE_SINGLE
#include <cedsp/types.h>

#include <edsp/io/metadata.hpp>
#include <edsp/io/encoder.hpp>
#include <edsp/io/decoder.hpp>
#include <edsp/io/resampler.hpp>

using encoder   = edsp::io::encoder<real_t>;
using decoder   = edsp::io::decoder<real_t>;
using resampler = edsp::io::resampler<real_t>;

auto encoder_wrapper(encoder& enc, bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    auto in         = reinterpret_cast<real_t*>(input.get_data());
    return enc.write(in, in + size);
}

auto decoder_wrapper(decoder& dec, unsigned int size) {
    Py_intptr_t shape[1] = {size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto data            = reinterpret_cast<real_t*>(result.get_data());
    const auto sizes     = dec.read(data, data + size);
    const auto frames    = sizes / dec.channels();
    result.reshape(bp::make_tuple(frames, dec.channels()));
    return result;
}

std::string resampler_error_string_wrapper(resampler& res) {
    return res.error_string().to_string();
}

auto resampler_process_wrapper(resampler& res, bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size          = input.shape(0);
    const auto expected_size = static_cast<unsigned int>(size * res.ratio());

    Py_intptr_t shape[1] = {expected_size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto data            = reinterpret_cast<real_t*>(result.get_data());
    auto in              = reinterpret_cast<real_t*>(input.get_data());
    const auto sizes     = res.process(in, in + size, data);

    Py_intptr_t final_shape[2] = {sizes.second, res.channels()};
    const auto final_samples   = sizes.second * res.channels();
    auto final_result          = bn::empty(1, final_shape, bn::dtype::get_builtin<real_t>());
    auto final_data            = reinterpret_cast<real_t*>(final_result.get_data());
    std::copy(data, data + final_samples, final_data);
    final_result.reshape(bp::make_tuple(sizes.second, res.channels()));
    return bp::make_tuple(final_result, sizes.first);
}

void add_io_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".io");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("io") = nested_module;
    bp::scope parent       = nested_module;

    bp::class_<edsp::io::metadata>("MetaDataReader", bp::init<const std::string&>())
        .def("title", &edsp::io::metadata::title)
        .def("genre", &edsp::io::metadata::genre)
        .def("year", &edsp::io::metadata::year)
        .def("album", &edsp::io::metadata::album)
        .def("artist", &edsp::io::metadata::artist)
        .def("track", &edsp::io::metadata::track);

    bp::class_<encoder>("Encoder", bp::init<std::size_t, std::size_t>())
        .def("open", &encoder::open)
        .def("is_open", &encoder::is_open)
        .def("close", &encoder::close)
        .def("channels", &encoder::channels)
        .def("samplerate", &encoder::sample_rate)
        .def("write", encoder_wrapper);

    bp::class_<decoder>("Decoder", bp::init<>())
        .def("open", &decoder::open)
        .def("is_open", &decoder::is_open)
        .def("close", &decoder::close)
        .def("channels", &decoder::channels)
        .def("samplerate", &decoder::sample_rate)
        .def("frames", &decoder::frames)
        .def("seekable", &decoder::seekable)
        .def("seek", &decoder::seek)
        .def("read", decoder_wrapper);

    bp::enum_<edsp::io::resample_quality>("ResampleQuality")
        .value("Linear", edsp::io::resample_quality::linear)
        .value("MediumQuality", edsp::io::resample_quality::medium_quality)
        .value("BestQuality", edsp::io::resample_quality::best_quality)
        .value("Fastest", edsp::io::resample_quality::sinc_fastest)
        .value("ZeroOrderHold", edsp::io::resample_quality::zero_order_hold);

    bp::class_<resampler>("Resampler", bp::init<std::size_t, edsp::io::resample_quality, real_t>())
        .def("process", resampler_process_wrapper)
        .def("error_string", resampler_error_string_wrapper)
        .def("quality", &resampler::quality)
        .def("reset", &resampler::reset)
        .def("error", &resampler::error)
        .def("valid_ratio", &resampler::valid_ratio)
        .staticmethod("valid_ratio")
        .def("ratio", &resampler::ratio);
}