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
* Filename: windowing.cpp
* Author: Mohammed Boujemaoui
* Date: 27/03/19
*/

#include "windowing.hpp"
#include "boost_numpy_dependencies.hpp"
#include <cedsp/windowing.h>

template <typename Functor>
bn::ndarray generate_window(long size, Functor&& f) {
    Py_intptr_t shape[1] = {size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto data            = reinterpret_cast<real_t*>(result.get_data());
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

bn::ndarray generate_rectangular(long size) {
    return generate_window(size, rectangular);
}

void add_windowing_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".windowing");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("windowing") = nested_module;
    bp::scope parent              = nested_module;

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
    bp::def("rectangular", generate_rectangular);
}
