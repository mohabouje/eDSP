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

#include "auditory.hpp"
#include "boost_numpy_dependencies.hpp"
#include <cedsp/types.h>
#include <edsp/auditory/audspace.hpp>
#include <edsp/auditory/converter/mel2hertz.hpp>
#include <edsp/auditory/converter/erb2hertz.hpp>
#include <edsp/auditory/converter/cent2hertz.hpp>
#include <edsp/auditory/converter/bark2hertz.hpp>

#include <edsp/auditory/converter/hertz2bark.hpp>
#include <edsp/auditory/converter/hertz2erb.hpp>
#include <edsp/auditory/converter/hertz2mel.hpp>
#include <edsp/auditory/converter/hertz2cent.hpp>

template <class Functor, typename T>
constexpr auto converter_python(Functor&& f, T frequency) noexcept {
    return f(frequency);
}

template <class Functor, typename T, typename Integer>
bn::ndarray generate_python(Functor&& f, T min, T max, Integer size) noexcept {
    Py_intptr_t shape[1] = {size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto* data           = reinterpret_cast<real_t*>(result.get_data());
    f(data, data + size, min, max);
    return result;
}

real_t hertz2mel(real_t frequency) noexcept {
    return converter_python(edsp::auditory::hertz2mel<real_t>, frequency);
}

real_t hertz2bark(real_t frequency) noexcept {
    return converter_python(edsp::auditory::hertz2bark<real_t>, frequency);
}

real_t hertz2cent(real_t frequency) noexcept {
    return converter_python(edsp::auditory::hertz2cent<real_t>, frequency);
}

real_t hertz2erb(real_t frequency) noexcept {
    return converter_python(edsp::auditory::hertz2erb<real_t>, frequency);
}

real_t mel2hertz(real_t frequency) noexcept {
    return converter_python(edsp::auditory::mel2hertz<real_t>, frequency);
}

real_t bark2hertz(real_t frequency) noexcept {
    return converter_python(edsp::auditory::bark2hertz<real_t>, frequency);
}

real_t cent2hertz(real_t frequency) noexcept {
    return converter_python(edsp::auditory::cent2hertz<real_t>, frequency);
}

real_t erb2hertz(real_t frequency) noexcept {
    return converter_python(edsp::auditory::erb2hertz<real_t>, frequency);
}

bn::ndarray erbspace(real_t min, real_t max, long size) noexcept {
    return generate_python(edsp::auditory::erbspace<real_t*, real_t>, min, max, size);
}

bn::ndarray barkspace(real_t min, real_t max, long size) noexcept {
    return generate_python(edsp::auditory::barkspace<real_t*, real_t>, min, max, size);
}

bn::ndarray centspace(real_t min, real_t max, long size) noexcept {
    return generate_python(edsp::auditory::centspace<real_t*, real_t>, min, max, size);
}

bn::ndarray melspace(real_t min, real_t max, long size) noexcept {
    return generate_python(edsp::auditory::melspace<real_t*, real_t>, min, max, size);
}

void add_auditory_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".auditory");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("auditory") = nested_module;
    bp::scope parent             = nested_module;

    bp::def("hertz2mel", hertz2mel);
    bp::def("hertz2bark", hertz2bark);
    bp::def("hertz2cent", hertz2cent);
    bp::def("hertz2erb", hertz2erb);
    bp::def("mel2hertz", mel2hertz);
    bp::def("bark2hertz", bark2hertz);
    bp::def("cent2hertz", cent2hertz);
    bp::def("erb2hertz", erb2hertz);
    bp::def("erbspace", erbspace);
    bp::def("barkspace", barkspace);
    bp::def("centspace", centspace);
    bp::def("melspace", melspace);
}