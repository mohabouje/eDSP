/**
* eDSP, A cross-platform Digital Signal Processing library written in modern C++.
* Copyright (C) 2019 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 3 of the License, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along width
* this program.  If not, see <http://www.gnu.org/licenses/>
*
* Filename: oscillator.cpp
* Author: Mohammed Boujemaoui
* Date: 2019-04-01
*/

#include "oscillator.hpp"
#include "boost_numpy_dependencies.hpp"
#include <cedsp/types.h>
#include <edsp/oscillator.hpp>

template <typename Generator>
bn::ndarray generate_python(Generator& gen, long size) {
    Py_intptr_t shape[1] = {size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto* data           = reinterpret_cast<real_t*>(result.get_data());
    std::generate(data, data + size, std::ref(gen));
    return result;
}

void add_oscillator_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".oscillator");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("oscillator") = nested_module;
    bp::scope parent               = nested_module;

    using base_class = edsp::oscillators::oscillator<real_t>;
    bp::class_<base_class>("Oscillator", bp::init<real_t, real_t, real_t, real_t>(
                                             (bp::arg("amp"), bp::arg("sr"), bp::arg("f"), bp::arg("p")), ""))
        .def("set_phase", &base_class::set_phase, (bp::arg("p")))
        .def("set_amplitude", &base_class::set_amplitude, (bp::arg("a")))
        .def("set_frequency", &base_class::set_frequency, (bp::arg("f")))
        .def("set_timestamp", &base_class::set_timestamp, (bp::arg("t")))
        .def("set_sample_rate", &base_class::set_sample_rate, (bp::arg("sr")))
        .def("reset", &base_class::reset)
        .def("phase", &base_class::phase)
        .def("amplitude", &base_class::amplitude)
        .def("frequency", &base_class::frequency)
        .def("timestamp", &base_class::timestamp)
        .def("sample_rate", &base_class::sample_rate);

    bp::class_<edsp::oscillators::sin_oscillator<real_t>, bp::bases<base_class>>(
        "Sinusoidal",
        bp::init<real_t, real_t, real_t, real_t>((bp::arg("amp"), bp::arg("sr"), bp::arg("f"), bp::arg("p")), ""))
        .def("generate", generate_python<edsp::oscillators::sin_oscillator<real_t>>, (bp::arg("N")));

    bp::class_<edsp::oscillators::square_oscillator<real_t>, bp::bases<base_class>>(
        "Square",
        bp::init<real_t, real_t, real_t, real_t>((bp::arg("amp"), bp::arg("sr"), bp::arg("f"), bp::arg("duty")), ""))
        .def("set_duty", &edsp::oscillators::square_oscillator<real_t>::set_duty, (bp::arg("duty")))
        .def("duty", &edsp::oscillators::square_oscillator<real_t>::duty)
        .def("generate", generate_python<edsp::oscillators::square_oscillator<real_t>>, (bp::arg("N")));

    bp::class_<edsp::oscillators::sawtooth_oscillator<real_t>, bp::bases<base_class>>(
        "Sawtooth",
        bp::init<real_t, real_t, real_t, real_t>((bp::arg("amp"), bp::arg("sr"), bp::arg("f"), bp::arg("width")), ""))
        .def("set_width", &edsp::oscillators::sawtooth_oscillator<real_t>::set_width, (bp::arg("width")))
        .def("width", &edsp::oscillators::sawtooth_oscillator<real_t>::width)
        .def("generate", generate_python<edsp::oscillators::sawtooth_oscillator<real_t>>, (bp::arg("N")));

    bp::class_<edsp::oscillators::triangular_oscillator<real_t>,
               bp::bases<edsp::oscillators::sawtooth_oscillator<real_t>>>(
        "Triangular", bp::init<real_t, real_t, real_t>((bp::arg("amp"), bp::arg("sr"), bp::arg("f")), ""))
        .def("generate", generate_python<edsp::oscillators::triangular_oscillator<real_t>>, (bp::arg("N")));
}
