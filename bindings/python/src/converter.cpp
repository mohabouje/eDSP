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
* Filename: converter.cpp
* Author: Mohammed Boujemaoui
* Date: 2019-03-31
*/

#include "converter.hpp"
#include "boost_numpy_dependencies.hpp"
#include <cedsp/converter.h>

real_t peak2rms_python(bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }
    const auto size = input.shape(0);
    auto* data      = reinterpret_cast<real_t*>(input.get_data());

    return peak2rms(data, size);
}

real_t peak2peak_python(bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }
    const auto size = input.shape(0);
    auto* data      = reinterpret_cast<real_t*>(input.get_data());

    return peak2peak(data, size);
}

bn::ndarray real2complex_python(bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<std::complex<real_t>>());

    auto* real        = reinterpret_cast<real_t*>(result.get_data());
    auto* result_data = reinterpret_cast<complex_t*>(result.get_data());
    real2complex(real, size, result_data);
    return result;
}

bn::ndarray ri2complex_python(bn::ndarray& real, bn::ndarray& imag) {
    if (real.get_nd() != 1 || imag.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = real.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<std::complex<real_t>>());

    auto* real_data   = reinterpret_cast<real_t*>(real.get_data());
    auto* imag_data   = reinterpret_cast<real_t*>(imag.get_data());
    auto* result_data = reinterpret_cast<complex_t*>(result.get_data());
    ri2complex(real_data, imag_data, size, result_data);
    return result;
}

bp::tuple complex2real_python(bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto real            = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto imag            = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());

    auto* complex_data = reinterpret_cast<complex_t*>(input.get_data());
    auto* real_data    = reinterpret_cast<real_t*>(real.get_data());
    auto* imag_data    = reinterpret_cast<real_t*>(imag.get_data());
    complex2real(complex_data, size, real_data, imag_data);
    return bp::make_tuple(real, imag);
}

void add_converter_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".converter");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("converter") = nested_module;
    bp::scope parent              = nested_module;

    bp::def("db2mag", db2mag);
    bp::def("db2pow", db2pow);
    bp::def("deg2rad", deg2rad);
    bp::def("mag2db", mag2db);
    bp::def("pow2db", pow2db);
    bp::def("rad2deg", rad2deg);
    bp::def("peak2peak", peak2peak_python);
    bp::def("peak2rms", peak2rms_python);
    bp::def("complex2real", complex2real_python);
    bp::def("real2complex", real2complex_python);
    bp::def("ri2complex", ri2complex_python);
}