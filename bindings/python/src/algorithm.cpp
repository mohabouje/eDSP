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
* Filename: algorithm.cpp
* Author: Mohammed Boujemaoui
* Date: 27/03/19
*/

#include "algorithm.hpp"
#include "boost_numpy_dependencies.hpp"
#include <cedsp/algorithm.h>
#include <edsp/algorithm.hpp>

template <typename Functor, typename... Args>
bn::ndarray execute_inplace(Functor&& f, bn::ndarray& input, Args... arg) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto in              = reinterpret_cast<real_t*>(input.get_data());
    auto out             = reinterpret_cast<real_t*>(result.get_data());
    f(in, size, out, arg...);
    return result;
}

template <typename Functor, typename... Args>
auto execute(Functor&& f, bn::ndarray& input, Args... arg) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    auto in         = reinterpret_cast<real_t*>(input.get_data());
    return f(in, size, arg...);
}

template <typename Functor, typename... Args>
bn::ndarray execute(Functor&& f, long size, Args... arg) {
    Py_intptr_t shape[1] = {size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto* data           = reinterpret_cast<real_t*>(result.get_data());
    f(data, size, arg...);
    return result;
}

bn::ndarray scale_python(bn::ndarray& input, real_t factor) {
    return execute_inplace(array_scale, input, factor);
}

bn::ndarray scale_clip_python(bn::ndarray& input, real_t factor, real_t min, real_t max) {
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

bn::ndarray abs_python(bn::ndarray& input) {
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

auto binary_search_python(bn::ndarray& input, real_t value) {
    return execute(binary_search, input, value);
}

auto linear_search_python(bn::ndarray& input, real_t value) {
    return execute(linear_search, input, value);
}

auto index_of_python(bn::ndarray& input, real_t value) {
    return execute(index_of, input, value);
}

bool equal_python(bn::ndarray& first, bn::ndarray& second) {
    if (first.get_nd() != 1 || second.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size  = first.shape(0);
    const auto size2 = second.shape(0);
    if (size != size2) {
        return false;
    }

    auto* first_in  = reinterpret_cast<real_t*>(first.get_data());
    auto* second_in = reinterpret_cast<real_t*>(second.get_data());
    return equal(first_in, size, second_in);
}

bn::ndarray concatenate_python(bn::ndarray& first, bn::ndarray& second) {
    if (first.get_nd() != 1 || second.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto first_size  = first.shape(0);
    const auto second_size = second.shape(0);
    Py_intptr_t shape[1]   = {first_size + second_size};
    auto result            = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto* first_in         = reinterpret_cast<real_t*>(first.get_data());
    auto* second_in        = reinterpret_cast<real_t*>(second.get_data());
    auto* result_data      = reinterpret_cast<real_t*>(result.get_data());

    array_concatenate(first_in, first_size, second_in, second_size, result_data);
    return result;
}

bn::ndarray padder_python(bn::ndarray& input, long size) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto input_size = input.shape(0);
    Py_intptr_t shape[1]  = {size};
    auto result           = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto* in              = reinterpret_cast<real_t*>(input.get_data());
    auto* result_data     = reinterpret_cast<real_t*>(result.get_data());

    array_padder(in, input_size, result_data, size);
    return result;
}

void add_algorithm_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".algorithm");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("algorithm") = nested_module;
    bp::scope parent              = nested_module;

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
    bp::def("linear_search", linear_search_python);
    bp::def("binary_search", binary_search_python);
    bp::def("index_of", index_of_python);
    bp::def("equal", equal_python);
}
