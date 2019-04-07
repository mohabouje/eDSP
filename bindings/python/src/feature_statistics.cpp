/**
 * Copyright (C) 2019 mboujemaoui
 * 
 * This file is part of eDSP.
 * 
 * eDSP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * eDSP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with eDSP.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "boost_numpy_dependencies.hpp"
#include "feature.hpp"

#include <cedsp/types.h>
#include <edsp/feature/statistics/centroid.hpp>
#include <edsp/feature/statistics/crest.hpp>
#include <edsp/feature/statistics/decrease.hpp>
#include <edsp/feature/statistics/entropy.hpp>
#include <edsp/feature/statistics/flatness.hpp>
#include <edsp/feature/statistics/flux.hpp>
#include <edsp/feature/statistics/rolloff.hpp>
#include <edsp/feature/statistics/slope.hpp>
#include <edsp/feature/statistics/spread.hpp>
#include <edsp/feature/statistics/variation.hpp>

template <class Functor, typename... Args>
auto execute(Functor&& f, bn::ndarray& input, Args... arg) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }
    const auto size = input.shape(0);
    auto* data      = reinterpret_cast<real_t*>(input.get_data());
    return f(data, data + size, arg...);
}

template <class Functor>
auto execute_two_inputs(Functor&& f, bn::ndarray& first, bn::ndarray& second) {
    if (first.get_nd() != 1 and second.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }
    const auto size   = first.shape(0);
    auto* first_data  = reinterpret_cast<real_t*>(first.get_data());
    auto* second_data = reinterpret_cast<real_t*>(second.get_data());
    return f(first_data, first_data + size, second_data);
}

auto crest_python(bn::ndarray& data) {
    using callback = decltype(edsp::feature::statistics::crest<real_t*>);
    return execute<callback>(edsp::feature::statistics::crest<real_t*>, data);
}

auto entropy_python(bn::ndarray& data) {
    using callback = decltype(edsp::feature::statistics::entropy<real_t*>);
    return execute<callback>(edsp::feature::statistics::entropy<real_t*>, data);
}

auto rolloff_python(bn::ndarray& data, real_t percentage) {
    using callback = decltype(edsp::feature::statistics::rolloff<real_t*, real_t>);
    return execute<callback>(edsp::feature::statistics::rolloff<real_t*, real_t>, data, percentage);
}

auto flatness_python(bn::ndarray& data) {
    using callback = decltype(edsp::feature::statistics::flatness<real_t*>);
    return execute<callback>(edsp::feature::statistics::flatness<real_t*>, data);
}

auto decrease_python(bn::ndarray& data) {
    using callback = decltype(edsp::feature::statistics::decrease<real_t*>);
    return execute<callback>(edsp::feature::statistics::decrease<real_t*>, data);
}

auto centroid_python(bn::ndarray& first) {
    using callback = decltype(edsp::feature::statistics::centroid<real_t*>);
    return execute<callback>(edsp::feature::statistics::centroid<real_t*>, first);
}

auto spread_python(bn::ndarray& first) {
    using callback = decltype(edsp::feature::statistics::spread<real_t*>);
    return execute<callback>(edsp::feature::statistics::spread<real_t*>, first);
}

auto weighted_centroid_python(bn::ndarray& first, bn::ndarray& second) {
    using callback = decltype(edsp::feature::statistics::weighted_centroid<real_t*>);
    return execute_two_inputs<callback>(edsp::feature::statistics::weighted_centroid<real_t*>, first, second);
}

auto weighted_spread_python(bn::ndarray& first, bn::ndarray& second) {
    using callback = decltype(edsp::feature::statistics::weighted_spread<real_t*>);
    return execute_two_inputs<callback>(edsp::feature::statistics::weighted_spread<real_t*>, first, second);
}

auto flux_python(bn::ndarray& first, bn::ndarray& second) {
    using callback = decltype(edsp::feature::statistics::flux<edsp::distances::euclidean, real_t*>);
    return execute_two_inputs<callback>(edsp::feature::statistics::flux<edsp::distances::euclidean, real_t*>, first,
                                        second);
}

auto slope_python(bn::ndarray& first, bn::ndarray& second) {
    using callback = decltype(edsp::feature::statistics::slope<real_t*>);
    return execute_two_inputs<callback>(edsp::feature::statistics::slope<real_t*>, first, second);
}

void add_feature_statistics_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".statistics");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("statistics") = nested_module;
    bp::scope parent               = nested_module;

    bp::def("centroid", centroid_python);
    bp::def("weighted_centroid", weighted_centroid_python);
    bp::def("crest", crest_python);
    bp::def("decrease", decrease_python);
    bp::def("entropy", entropy_python);
    bp::def("flatness", flatness_python);
    bp::def("flux", flux_python);
    bp::def("rolloff", rolloff_python);
    bp::def("slope", slope_python);
    bp::def("spread", spread_python);
    bp::def("weighted_spread", weighted_spread_python);
}