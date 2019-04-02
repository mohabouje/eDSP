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
* Filename: statistics.cpp
* Author: Mohammed Boujemaoui
* Date: 27/03/19
*/

#include "statistics.hpp"
#include "boost_numpy_dependencies.hpp"
#include <cedsp/statistics.h>

template <class Functor, typename... Arg>
inline auto execute(Functor&& f, bn::ndarray& input, Arg... arg) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    auto in         = reinterpret_cast<real_t*>(input.get_data());
    return f(in, size, arg...);
}

real_t kurtosis_python(bn::ndarray& input) {
    return execute(kurtosis, input);
}

real_t skewness_python(bn::ndarray& input) {
    return execute(skewness, input);
}

real_t moment_python(bn::ndarray& input, int n) {
    return execute(moment, input, n);
}

real_t geometric_mean_python(bn::ndarray& input) {
    return execute(geometric_mean, input);
}

real_t generalized_mean_python(bn::ndarray& input, int beta) {
    return execute(generalized_mean, input, beta);
}

real_t harmonic_mean_python(bn::ndarray& input) {
    return execute(harmonic_mean, input);
}

real_t max_python(bn::ndarray& input) {
    return execute(max, input);
}

real_t min_python(bn::ndarray& input) {
    return execute(min, input);
}

bp::tuple peak_python(bn::ndarray& input) {
    const auto elem = execute(peak, input);
    return bp::make_tuple(elem.index, elem.value);
}

real_t max_abs_python(bn::ndarray& input) {
    return execute(max_abs, input);
}

real_t min_abs_python(bn::ndarray& input) {
    return execute(min_abs, input);
}

bp::tuple peak_abs_python(bn::ndarray& input) {
    const auto elem = execute(peak_abs, input);
    return bp::make_tuple(elem.index, elem.value);
}

real_t mean_python(bn::ndarray& input) {
    return execute(mean, input);
}

real_t median_python(bn::ndarray& input) {
    return execute(median, input);
}

real_t variance_python(bn::ndarray& input) {
    return execute(variance, input);
}

real_t standard_deviation_python(bn::ndarray& input) {
    return execute(standard_deviation, input);
}

real_t norm_python(bn::ndarray& input) {
    return execute(norm, input);
}

void add_statistics_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".statistics");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("statistics") = nested_module;
    bp::scope parent               = nested_module;

    bp::def("kurtosis", kurtosis_python);
    bp::def("skewness", skewness_python);
    bp::def("moment", moment_python);
    bp::def("geometric_mean", geometric_mean_python);
    bp::def("generalized_mean", generalized_mean_python);
    bp::def("harmonic_mean", harmonic_mean_python);
    bp::def("max", max_python);
    bp::def("max_abs", max_abs_python);
    bp::def("min", min_python);
    bp::def("min_abs", min_abs_python);
    bp::def("peak", peak_python);
    bp::def("peak_abs", peak_abs_python);
    bp::def("mean", mean_python);
    bp::def("median", median_python);
    bp::def("variance", variance_python);
    bp::def("standard_deviation", standard_deviation_python);
    bp::def("norm", norm_python);
}
