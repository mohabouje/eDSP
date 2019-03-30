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
* Filename: algorithm.cpp
* Author: Mohammed Boujemaoui
* Date: 27/03/19
*/

#include "algorithm.hpp"
#include "boost_numpy_dependencies.hpp"
#include <algorithm.h>



template <typename Functor, typename... Args>
bn::ndarray execute_inplace(Functor&& f, bn::ndarray& input, Args... arg) {

    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());
    auto in = reinterpret_cast<real_t*>(input.get_data());
    auto out = reinterpret_cast<real_t*>(result.get_data());
    f(in, size, out, arg...);
    return result;
}

template <typename Functor, typename... Args>
bn::ndarray execute(Functor&& f, long size, Args... arg) {
    Py_intptr_t shape[1] = {size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());
    auto* data = reinterpret_cast<real_t*>(result.get_data());
    f(data, size, arg...);
    return result;
}

bn::ndarray scale_python(bn::ndarray &input, real_t factor) {
    return execute_inplace(array_scale, input, factor);
}

bn::ndarray scale_clip_python(bn::ndarray &input, real_t factor, real_t min, real_t max) {
    return execute_inplace(array_scale_clip, input, factor, min, max);
}

bn::ndarray clip_python(bn::ndarray& input, real_t min, real_t max) {
    return execute_inplace(array_clip, input, min, max);
}

bn::ndarray ceil_python(bn::ndarray& input) {
    return execute_inplace(array_ceil, input);
}

bn::ndarray floor_python(bn::ndarray& input) {
    return execute_inplace(array_floor, input);
}

bn::ndarray round_python(bn::ndarray& input) {
    return execute_inplace(array_round, input);
}

bn::ndarray trunc_python(bn::ndarray& input) {
    return execute_inplace(array_trunc, input);
}

bn::ndarray abs_python(bn::ndarray &input) {
    return execute_inplace(array_abs, input);
}

bn::ndarray normalize_python(bn::ndarray& input) {
    return execute_inplace(array_normalize, input);
}

bn::ndarray linspace_python(real_t x1, real_t x2, long size) {
    return execute(array_linspace, size, x1, x2);
}

bn::ndarray logspace_python(real_t x1, real_t x2, long size) {
    return execute(array_logspace, size, x1, x2);
}

bn::ndarray concatenate_python(bn::ndarray& first, bn::ndarray& second) {
    if (first.get_nd() != 1 || second.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto first_size = first.shape(0);
    const auto second_size = second.shape(0);
    Py_intptr_t shape[1] = {first_size + second_size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());
    auto* first_in = reinterpret_cast<real_t*>(first.get_data());
    auto* second_in = reinterpret_cast<real_t*>(second.get_data());
    auto* result_data = reinterpret_cast<real_t*>(result.get_data());

    array_concatenate(first_in, first_size, second_in, second_size, result_data);
    return result;
}

bn::ndarray padder_python(bn::ndarray& input, long size) {
    if (input.get_nd() != 1 ) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto input_size = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());
    auto* in = reinterpret_cast<real_t*>(input.get_data());
    auto* result_data = reinterpret_cast<real_t*>(result.get_data());

    array_padder(in, input_size, result_data, size);
    return result;
}

void add_algorithm_package() {

    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".algorithm");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("algorithm") = nested_module;
    bp::scope parent = nested_module;

    bp::def("scale", scale_python);
    bp::def("scale_clip", scale_clip_python);
    bp::def("ceil", ceil_python);
    bp::def("floor", floor_python);
    bp::def("round", round_python);
    bp::def("clip", clip_python);
    bp::def("trunc", trunc_python);
    bp::def("abs", abs_python);
    bp::def("logspace", logspace_python);
    bp::def("linspace", linspace_python);
    bp::def("normalize", normalize_python);
    bp::def("concatenate", concatenate_python);
    bp::def("pad", padder_python);
}
