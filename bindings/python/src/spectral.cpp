/*
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
* Filename: spectral.cpp
* Author: Mohammed Boujemaoui
* Date: 29/03/19
*/

#include "spectral.hpp"
#include "boost_numpy_dependencies.hpp"
#include <cedsp/spectral.h>

template <typename Functor>
bn::ndarray execute(Functor&& f, bn::ndarray& left, bn::ndarray& right) {
    if (left.get_nd() != 1 || right.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = left.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result          = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());

    auto* left_data  = reinterpret_cast<real_t*>(left.get_data());
    auto* right_data = reinterpret_cast<real_t*>(right.get_data());
    auto result_data = reinterpret_cast<real_t*>(result.get_data());
    f(left_data, right_data, size, result_data);
    return result;
}

template <typename Functor>
bn::ndarray execute(Functor&& f, bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result          = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());

    auto* input_data = reinterpret_cast<real_t*>(input.get_data());
    auto result_data = reinterpret_cast<real_t*>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

template <typename Functor>
bn::ndarray execute_r2r_half(Functor&& f, bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {get_fft_size(size)};
    auto result          = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());

    auto* input_data = reinterpret_cast<real_t*>(input.get_data());
    auto result_data = reinterpret_cast<real_t*>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

template <typename Functor>
bn::ndarray execute_r2c_full(Functor&& f, bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result          = bn::zeros(1, shape, bn::dtype::get_builtin<std::complex<real_t>>());

    auto* input_data = reinterpret_cast<real_t*>(input.get_data());
    auto result_data = reinterpret_cast<complex_t*>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

template <typename Functor>
bn::ndarray execute_r2c_half(Functor&& f, bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {get_fft_size(size)};
    auto result          = bn::zeros(1, shape, bn::dtype::get_builtin<std::complex<real_t>>());

    auto* input_data = reinterpret_cast<real_t*>(input.get_data());
    auto result_data = reinterpret_cast<complex_t*>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

template <typename Functor>
bn::ndarray execute_c2r(Functor&& f, bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {get_ifft_size(size)};
    auto result          = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());

    auto* input_data = reinterpret_cast<complex_t*>(input.get_data());
    auto result_data = reinterpret_cast<real_t*>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

template <typename Functor>
bn::ndarray execute_c2c(Functor&& f, bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result          = bn::zeros(1, shape, bn::dtype::get_builtin<std::complex<real_t>>());

    auto* input_data  = reinterpret_cast<complex_t*>(input.get_data());
    auto* result_data = reinterpret_cast<complex_t*>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

bn::ndarray conv_python(bn::ndarray& left, bn::ndarray& right) {
    return execute(conv, left, right);
}

bn::ndarray correlation_python(bn::ndarray& left, bn::ndarray& right) {
    return execute(xcorr, left, right);
}

bn::ndarray cepstrum_python(bn::ndarray& ceps) {
    return execute(cepstrum, ceps);
}

bn::ndarray dct_python(bn::ndarray& data) {
    return execute(dct, data);
}

bn::ndarray idct_python(bn::ndarray& data) {
    return execute(idct, data);
}

bn::ndarray spectrum_python(bn::ndarray& data) {
    return execute_r2r_half(spectrum, data);
}

bn::ndarray hartley_python(bn::ndarray& data) {
    return execute(hartley, data);
}

bn::ndarray hilbert_python(bn::ndarray& data) {
    return execute_r2c_full(hilbert, data);
}

bn::ndarray fft_python(bn::ndarray& data) {
    return execute_r2c_half(fft, data);
}

bn::ndarray ifft_python(bn::ndarray& data) {
    return execute_c2r(ifft, data);
}

bn::ndarray cfft_python(bn::ndarray& data) {
    return execute_c2c(complex_fft, data);
}

bn::ndarray cifft_python(bn::ndarray& data) {
    return execute_c2c(complex_ifft, data);
}

void add_spectral_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".spectral");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("spectral") = nested_module;
    bp::scope parent             = nested_module;

    bp::def("conv", conv_python);
    bp::def("xcorr", correlation_python);
    bp::def("cepstrum", cepstrum_python);
    bp::def("dct", dct_python);
    bp::def("idct", idct_python);
    bp::def("spectrum", spectrum_python);
    bp::def("hilbert", hilbert_python);
    bp::def("hartley", hartley_python);
    bp::def("rfft", fft_python);
    bp::def("irfft", ifft_python);
    bp::def("fft", cfft_python);
    bp::def("ifft", cifft_python);
}
