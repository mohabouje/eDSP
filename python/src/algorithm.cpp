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

#include <algorithm.h>
#include <edsp/algorithm.hpp>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#define BOOST_EDSP_LIBRARY "boost_numpy"
#include <boost/config/auto_link.hpp>

namespace bp = boost::python;
namespace bn = boost::python::numpy;
using namespace edsp::algorithm;


template <typename Functor, typename... Args>
void execute_inplace(Functor&& f, bn::ndarray& input, Args... arg) {

    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    auto in = reinterpret_cast<real_t*>(input.get_data());
    f(in, size, in, arg...);
}

template <typename Functor, typename... Args>
void execute(Functor&& f, bn::ndarray& input, Args... arg) {

    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    auto in = reinterpret_cast<real_t*>(input.get_data());
    f(in, size, arg...);
}

void amplifier_python(bn::ndarray& input, real_t factor) {
    execute_inplace(array_amplify, input, factor);
}

void amplifier_clip_python(bn::ndarray& input, real_t factor, real_t min, real_t max) {
    execute_inplace(array_amplify_clip, input, factor, min, max);
}

void ceil_python(bn::ndarray& input) {
    execute_inplace(array_ceil, input);
}

void floor_python(bn::ndarray& input) {
    execute_inplace(array_floor, input);
}

void round_python(bn::ndarray& input) {
    execute_inplace(array_round, input);
}

void clip_python(bn::ndarray& input) {
    execute_inplace(array_ceil, input);
}

void trunc_python(bn::ndarray& input) {
    execute_inplace(array_trunc, input);
}

void rectify_python(bn::ndarray& input) {
    execute_inplace(array_rectify, input);
}

void normalize_python(bn::ndarray& input) {
    execute_inplace(array_normalize, input);
}

bn::ndarray linspace_python(long size, real_t x1, real_t x2) {
    Py_intptr_t shape[1] = {size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());
    execute(array_linspace, result, x1, x2);
    return result;
}

bn::ndarray logspace_python(long size, real_t x1, real_t x2) {
    Py_intptr_t shape[1] = {size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());
    execute(array_logspace, result, x1, x2);
    return result;
}


void add_algorithm_package() {

    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".algorithm");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("algorithm") = nested_module;
    bp::scope parent = nested_module;

    bp::def("amplifier", amplifier_python);
    bp::def("amplifier_clip", amplifier_clip_python);
    bp::def("ceil", ceil_python);
    bp::def("floor", floor_python);
    bp::def("round", round_python);
    bp::def("clip", clip_python);
    bp::def("trunc", trunc_python);
    bp::def("rectify", rectify_python);
    bp::def("logspace", logspace_python);
    bp::def("linspace", linspace_python);
    bp::def("normalize", normalize_python);
}
