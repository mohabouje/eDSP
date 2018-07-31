/*
 * EasyDSP, Yet another header-only library for C++ meta-programming.
 * Copyright (C) 2018 Mohammed Boujemaoui
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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: windowing_binding.cpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-29
 */

#include "transform_binding.hpp"
#include "windowing_binding.hpp"
#include "standard_binding.hpp"

BOOST_PYTHON_MODULE(PYTHON_MODULE_NAME) {
    scope windowing = class_<Windowing>("Windowing")
            .def("apply", &Windowing::apply)
            .staticmethod("apply");

    declare_window<Bartlett<double>>("Bartlett");
    declare_window<Blackman<double>>("Blackman");
    declare_window<Hamming<double>>("Hamming");
    declare_window<Hanning<double>>("Hanning");
    declare_window<Rectangular<double>>("Rectangular");
    declare_window<FlatTop<double>>("FlatTop");
    declare_window<Triangular<double>>("Triangular");

    scope transform = class_<Transform>("Transform")
            .def("dft", &Transform::dft)
            .def("idft", &Transform::idft)
            .def("dct", &Transform::dct)
            .def("idct", &Transform::idct)
            .def("dht", &Transform::dht)
            .staticmethod("dft")
            .staticmethod("idft")
            .staticmethod("dct")
            .staticmethod("idct")
            .staticmethod("dht");

    scope standard = class_<Standard>("Standard");
    declare_standard();
}


