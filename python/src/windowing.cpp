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
* Filename: windowing..cpp
* Author: Mohammed Boujemaoui
* Date: 27/03/19
*/

#include "windowing_python.hpp"
#include <windowing.h>
#include <boost/python/numpy.hpp>
#include <boost/python.hpp>

namespace bp = boost::python;
namespace bn = boost::python::numpy;

template <typename Functor>
bn::ndarray generate_window(long size, Functor&& f) {
    Py_intptr_t shape[1] = {size};
    auto result = bn::zeros(1, shape, bn::dtype::get_builtin<real_t>());
    auto data = reinterpret_cast<real_t*>(result.get_data());
    f(data, size);
    return result;
}

bn::ndarray generate_hamming(long size) {
    return generate_window(size, hamming);
}

bn::ndarray generate_hanning(long size) {
    return generate_window(size, hanning);
}

bn::ndarray generate_bartlett(long size) {
    return generate_window(size, bartlett);
}

bn::ndarray generate_blackman(long size) {
    return generate_window(size, blackman);
}

bn::ndarray generate_blackman_harris(long size) {
    return generate_window(size, blackman_harris);
}

bn::ndarray generate_blackman_nutall(long size) {
    return generate_window(size, blackman_nutall);
}

bn::ndarray generate_boxcar(long size) {
    return generate_window(size, boxcar);
}

bn::ndarray generate_flattop(long size) {
    return generate_window(size, flattop);
}

bn::ndarray generate_welch(long size) {
    return generate_window(size, welch);
}

bn::ndarray generate_triangular(long size) {
    return generate_window(size, triangular);
}

void add_windowing_package() {

    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".windowing");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("windowing") = nested_module;
    bp::scope parent = nested_module;


    bp::def("bartlett", generate_bartlett);
    bp::def("blackman", generate_blackman);
    bp::def("blackman_harris", generate_blackman_harris);
    bp::def("blackman_nutall", generate_blackman_nutall);
    bp::def("boxcar", generate_boxcar);
    bp::def("flattop", generate_flattop);
    bp::def("hamming", generate_hamming);
    bp::def("hanning", generate_hanning);
    bp::def("triangular", generate_triangular);
    bp::def("welch", generate_welch);
}
