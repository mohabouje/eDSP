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
* Filename: statistics.cpp
* Author: Mohammed Boujemaoui
* Date: 27/03/19
*/

#include "statistics_python.hpp"
#include <statistics.h>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace bp = boost::python;
namespace bn = boost::python::numpy;

template <class Functor, typename... Arg>
inline auto execute(Functor&& f, bn::ndarray& input, Arg... arg) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    auto in = reinterpret_cast<real_t*>(input.get_data());
    return f(in, size, arg...);
} 

real_t centroid_python(bn::ndarray& input) {
    return execute(centroid, input);
}

real_t entropy_python(bn::ndarray& input)  {
    return execute(entropy, input);
}

real_t flatness_python(bn::ndarray& input)  {
    return execute(flatness, input);
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

real_t standard_deviation_python(bn::ndarray& input)  {
    return execute(standard_deviation, input);
}

real_t norm_python(bn::ndarray& input)  {
    return execute(norm, input);
}



void add_statistics_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".statistics");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("statistics") = nested_module;
    bp::scope parent = nested_module;

    bp::def("centroid", centroid_python);
    bp::def("entropy", entropy_python);
    bp::def("flatness", flatness_python);
    bp::def("kurtosis", kurtosis_python);
    bp::def("skewness", skewness_python);
    bp::def("moment", moment_python);
    bp::def("geometric_mean", geometric_mean_python);
    bp::def("generalized_mean", generalized_mean_python);
    bp::def("harmonic_mean", harmonic_mean_python);
    bp::def("max", max);
    bp::def("max_abs", max_abs);
    bp::def("min", min);
    bp::def("min_abs", min_abs);
    bp::def("peak", peak);
    bp::def("peak_abs", peak_abs);
    bp::def("mean", mean);
    bp::def("median", median);
    bp::def("variance", variance);
    bp::def("standard_deviation", standard_deviation);
    bp::def("norm", norm);
}
