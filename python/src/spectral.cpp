/*
* edsp, Yet another framework for building deep RNN networks written in modern C++.
*
* The 2-Clause BSD License
*
* Copyright (c) 2019 Mohammed Boujemaoui Boulaghmoudi,
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Filename: spectral.cpp
* Author: Mohammed Boujemaoui
* Date: 29/03/19
*/

#include "spectral.hpp"
#include "boost_numpy_dependencies.hpp"
#include <spectral.h>

template <typename Functor>
bn::ndarray execute(Functor&& f, bn::ndarray& left, bn::ndarray& right) {
    if (left.get_nd() != 1 || right.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = left.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());

    auto* left_data = reinterpret_cast<real_t*>(left.get_data());
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

    const auto size = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());

    auto* input_data = reinterpret_cast<real_t*>(input.get_data());
    auto result_data = reinterpret_cast<real_t*>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

template <typename Functor>
bn::ndarray execute_r2c_full(Functor &&f, bn::ndarray &input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<std::complex<real_t>>());

    auto* input_data = reinterpret_cast<real_t *>(input.get_data());
    auto result_data = reinterpret_cast<complex_t *>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

template <typename Functor>
bn::ndarray execute_r2c_half(Functor &&f, bn::ndarray &input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    Py_intptr_t shape[1] = {get_fft_size(size)};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<std::complex<real_t>>());

    auto* input_data = reinterpret_cast<real_t *>(input.get_data());
    auto result_data = reinterpret_cast<complex_t *>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

template <typename Functor>
bn::ndarray execute_c2r(Functor &&f, bn::ndarray &input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    Py_intptr_t shape[1] = {get_ifft_size(size)};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());

    auto* input_data = reinterpret_cast<complex_t *>(input.get_data());
    auto result_data = reinterpret_cast<real_t *>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

template <typename Functor>
bn::ndarray execute_c2c(Functor &&f, bn::ndarray &input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<std::complex<real_t>>());

    auto* input_data = reinterpret_cast<complex_t *>(input.get_data());
    auto* result_data = reinterpret_cast<complex_t *>(result.get_data());
    f(input_data, size, result_data);
    return result;
}

bn::ndarray conv_python(bn::ndarray &left, bn::ndarray &right) {
    return execute(conv, left, right);
}

bn::ndarray correlation_python(bn::ndarray &left, bn::ndarray &right) {
    return execute(xcorr, left, right);
}

bn::ndarray cepstrum_python(bn::ndarray &ceps) {
    return execute(cepstrum, ceps);
}

bn::ndarray dct_python(bn::ndarray &data) {
    return execute(dct, data);
}

bn::ndarray idct_python(bn::ndarray &data) {
    return execute(idct, data);
}

bn::ndarray hartley_python(bn::ndarray &data) {
    return execute(hartley, data);
}

bn::ndarray hilbert_python(bn::ndarray &data) {
    return execute_r2c_full(hilbert, data);
}

bn::ndarray fft_python(bn::ndarray &data) {
    return execute_r2c_half(fft, data);
}

bn::ndarray ifft_python(bn::ndarray &data) {
    return execute_c2r(ifft, data);
}

bn::ndarray cfft_python(bn::ndarray &data) {
    return execute_c2c(complex_fft, data);
}

bn::ndarray cifft_python(bn::ndarray &data) {
    return execute_c2c(complex_ifft, data);
}

void add_spectral_package() {

    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".spectral");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("spectral") = nested_module;
    bp::scope parent = nested_module;

    bp::def("conv", conv_python);
    bp::def("xcorr", correlation_python);
    bp::def("cepstrum", cepstrum_python);
    bp::def("dct", dct_python);
    bp::def("idct", idct_python);
    bp::def("hilbert", hilbert_python);
    bp::def("hartley", hartley_python);
    bp::def("rfft", fft_python);
    bp::def("irfft", ifft_python);
    bp::def("fft", cfft_python);
    bp::def("ifft", cifft_python);
}
