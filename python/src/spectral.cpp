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
#include <spectral.h>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace bp = boost::python;
namespace bn = boost::python::numpy;


template <typename Functor, typename... Args>
bn::ndarray execute(Functor&& f, bn::ndarray& left, bn::ndarray& right, Args... arg) {
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

bn::ndarray conv_python(bn::ndarray &left, bn::ndarray &right) {
    return execute(conv, left, right);
}

bn::ndarray correlation_python(bn::ndarray &left, bn::ndarray &right) {
    return execute(xcorr, left, right);
}

void add_spectral_package() {

    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".spectral");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("spectral") = nested_module;
    bp::scope parent = nested_module;

    bp::def("conv", conv_python);
    bp::def("xcorr", correlation_python);

}
