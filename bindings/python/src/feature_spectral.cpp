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

#include "feature.hpp"
#include "boost_numpy_dependencies.hpp"

#include <cedsp/types.h>
#include <edsp/feature/spectral/spectral_centroid.hpp>
#include <edsp/feature/spectral/spectral_crest.hpp>
#include <edsp/feature/spectral/spectral_decrease.hpp>
#include <edsp/feature/spectral/spectral_entropy.hpp>
#include <edsp/feature/spectral/spectral_flatness.hpp>
#include <edsp/feature/spectral/spectral_flux.hpp>
#include <edsp/feature/spectral/spectral_irregularity.hpp>
#include <edsp/feature/spectral/spectral_kurtosis.hpp>
#include <edsp/feature/spectral/spectral_rolloff.hpp>
#include <edsp/feature/spectral/spectral_skewness.hpp>
#include <edsp/feature/spectral/spectral_slope.hpp>
#include <edsp/feature/spectral/spectral_spread.hpp>
#include <edsp/feature/spectral/spectral_variation.hpp>

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
auto execute(Functor&& f, bn::ndarray& first, bn::ndarray& second) {
    if (first.get_nd() != 1 and second.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }
    const auto size   = first.shape(0);
    auto* first_data  = reinterpret_cast<real_t*>(first.get_data());
    auto* second_data = reinterpret_cast<real_t*>(second.get_data());
    return f(first_data, first_data + size, second_data);
}

auto spectral_crest_python(bn::ndarray& spectrum) {
    using callback = decltype(edsp::feature::spectral::spectral_crest<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_crest<real_t*>, spectrum);
}

auto spectral_kurtosis_python(bn::ndarray& spectrum) {
    using callback = decltype(edsp::feature::spectral::spectral_kurtosis<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_kurtosis<real_t*>, spectrum);
}

auto spectral_skewness_python(bn::ndarray& spectrum) {
    using callback = decltype(edsp::feature::spectral::spectral_skewness<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_skewness<real_t*>, spectrum);
}

auto spectral_entropy_python(bn::ndarray& spectrum) {
    using callback = decltype(edsp::feature::spectral::spectral_entropy<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_entropy<real_t*>, spectrum);
}

auto spectral_rolloff_python(bn::ndarray& spectrum, real_t percentage) {
    using callback = decltype(edsp::feature::spectral::spectral_rolloff<real_t*, real_t>);
    return execute<callback>(edsp::feature::spectral::spectral_rolloff<real_t*, real_t>, spectrum, percentage);
}

auto spectral_flatness_python(bn::ndarray& spectrum) {
    using callback = decltype(edsp::feature::spectral::spectral_flatness<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_flatness<real_t*>, spectrum);
}

auto spectral_irregularity_python(bn::ndarray& spectrum) {
    using callback = decltype(edsp::feature::spectral::spectral_irregularity<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_irregularity<real_t*>, spectrum);
}

auto spectral_decrease_python(bn::ndarray& spectrum) {
    using callback = decltype(edsp::feature::spectral::spectral_decrease<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_decrease<real_t*>, spectrum);
}

auto spectral_centroid_python(bn::ndarray& spectrum, bn::ndarray& weights) {
    using callback = decltype(edsp::feature::spectral::spectral_centroid<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_centroid<real_t*>, spectrum, weights);
}

auto spectral_spread_python(bn::ndarray& spectrum, bn::ndarray& weights) {
    using callback = decltype(edsp::feature::spectral::spectral_spread<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_spread<real_t*>, spectrum, weights);
}

auto spectral_variation_python(bn::ndarray& first, bn::ndarray& second) {
    using callback = decltype(edsp::feature::spectral::spectral_variation<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_variation<real_t*>, first, second);
}

auto spectral_flux_python(bn::ndarray& first, bn::ndarray& second) {
    using callback = decltype(edsp::feature::spectral::spectral_flux<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_flux<real_t*>, first, second);
}

auto spectral_slope_python(bn::ndarray& first, bn::ndarray& second) {
    using callback = decltype(edsp::feature::spectral::spectral_slope<real_t*>);
    return execute<callback>(edsp::feature::spectral::spectral_slope<real_t*>, first, second);
}

void add_feature_spectral_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".spectral");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("spectral") = nested_module;
    bp::scope parent             = nested_module;

    bp::def("spectral_centroid", spectral_centroid_python);
    bp::def("spectral_crest", spectral_crest_python);
    bp::def("spectral_decrease", spectral_decrease_python);
    bp::def("spectral_entropy", spectral_entropy_python);
    bp::def("spectral_flatness", spectral_flatness_python);
    bp::def("spectral_flux", spectral_flux_python);
    bp::def("spectral_irregularity", spectral_irregularity_python);
    bp::def("spectral_kurtosis", spectral_kurtosis_python);
    bp::def("spectral_rolloff", spectral_rolloff_python);
    bp::def("spectral_skewness", spectral_skewness_python);
    bp::def("spectral_slope", spectral_slope_python);
    bp::def("spectral_spread", spectral_spread_python);
    bp::def("spectral_variation", spectral_variation_python);
}