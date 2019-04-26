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

#include <cedsp/types.h>
#include <edsp/feature/temporal/snr.hpp>
#include <edsp/feature/temporal/rssq.hpp>
#include <edsp/feature/temporal/rms.hpp>
#include <edsp/feature/temporal/power.hpp>
#include <edsp/feature/temporal/leq.hpp>
#include <edsp/feature/temporal/energy.hpp>
#include <edsp/feature/temporal/duration.hpp>
#include <edsp/feature/temporal/azcr.hpp>
#include <edsp/feature/temporal/asdf.hpp>
#include <edsp/feature/temporal/amdf.hpp>

template <class Functor, typename... Args>
auto execute(Functor&& f, bn::ndarray& input, Args... arg) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size = input.shape(0);
    auto in         = reinterpret_cast<real_t*>(input.get_data());
    return f(in, in + size, arg...);
}

template <class Functor, typename... Args>
bn::ndarray execute_numpy(Functor&& f, bn::ndarray& input, Args... arg) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }

    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto* data           = reinterpret_cast<real_t*>(result.get_data());

    auto in = reinterpret_cast<real_t*>(input.get_data());
    f(in, in + size, data, arg...);
    return result;
}

real_t rssq_python(bn::ndarray& input) {
    using callback_type = decltype(edsp::feature::rssq<real_t*>);
    return execute<callback_type>(edsp::feature::rssq<real_t*>, input);
}

real_t rms_python(bn::ndarray& input) {
    using callback_type = decltype(edsp::feature::temporal::rms<real_t*>);
    return execute<callback_type>(edsp::feature::temporal::rms<real_t*>, input);
}

real_t power_python(bn::ndarray& input) {
    using callback_type = decltype(edsp::feature::temporal::power<real_t*>);
    return execute<callback_type>(edsp::feature::temporal::power<real_t*>, input);
}

real_t energy_python(bn::ndarray& input) {
    using callback_type = decltype(edsp::feature::temporal::energy<real_t*>);
    return execute<callback_type>(edsp::feature::temporal::energy<real_t*>, input);
}

real_t duration_python(bn::ndarray& input, real_t sample_rate) {
    using callback_type = decltype(edsp::feature::temporal::duration<real_t*, real_t>);
    return execute<callback_type>(edsp::feature::temporal::duration<real_t*, real_t>, input, sample_rate);
}

real_t effective_duration_python(bn::ndarray& input, real_t sample_rate, real_t threshold) {
    using callback_type = decltype(edsp::feature::temporal::effective_duration<real_t*, real_t>);
    return execute<callback_type>(edsp::feature::temporal::effective_duration<real_t*, real_t>, input, sample_rate,
                                  threshold);
}

real_t leq_python(bn::ndarray& input) {
    using callback_type = decltype(edsp::feature::temporal::leq<real_t*>);
    return execute<callback_type>(edsp::feature::temporal::leq<real_t*>, input);
}

real_t azcr_python(bn::ndarray& input) {
    using callback_type = decltype(edsp::feature::temporal::azcr<real_t*>);
    return execute<callback_type>(edsp::feature::temporal::azcr<real_t*>, input);
}

bn::ndarray amdf_python(bn::ndarray& input) {
    using callback_type = decltype(edsp::feature::temporal::amdf<real_t*, real_t*>);
    return execute_numpy<callback_type>(edsp::feature::temporal::amdf<real_t*, real_t*>, input);
}

bn::ndarray asdf_python(bn::ndarray& input) {
    using callback_type = decltype(edsp::feature::temporal::asdf<real_t*, real_t*>);
    return execute_numpy<callback_type>(edsp::feature::temporal::asdf<real_t*, real_t*>, input);
}

void add_feature_temporal_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".temporal");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("temporal") = nested_module;
    bp::scope parent             = nested_module;

    bp::def("duration", duration_python);
    bp::def("effective_duration", effective_duration_python);
    bp::def("amdf", amdf_python);
    bp::def("asdf", asdf_python);
    bp::def("azcr", azcr_python);
    bp::def("energy", energy_python);
    bp::def("power", power_python);
    bp::def("rms", rms_python);
    bp::def("rssq", rssq_python);
    bp::def("leq", leq_python);
}