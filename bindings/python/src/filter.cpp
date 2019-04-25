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

#include "filter.hpp"
#include "boost_numpy_dependencies.hpp"
#include <cedsp/types.h>
#include <edsp/filter.hpp>

template <typename Class>
auto wrapper_filter(Class& obj, bn::ndarray& input) {
    if (input.get_nd() != 1) {
        throw std::invalid_argument("Expected one-dimensional arrays");
    }
    const auto size      = input.shape(0);
    Py_intptr_t shape[1] = {size};
    auto result          = bn::empty(1, shape, bn::dtype::get_builtin<real_t>());
    auto data            = reinterpret_cast<real_t*>(input.get_data());
    auto output          = reinterpret_cast<real_t*>(result.get_data());
    obj.filter(data, data + size, output);
    return result;
}

auto wrapper_median_filter(edsp::filter::moving_median<real_t>& obj, bn::ndarray& input) {
    return wrapper_filter(obj, input);
}

auto wrapper_average_filter(edsp::filter::moving_average<real_t>& obj, bn::ndarray& input) {
    return wrapper_filter(obj, input);
}

auto wrapper_rms_filter(edsp::filter::moving_rms<real_t>& obj, bn::ndarray& input) {
    return wrapper_filter(obj, input);
}

void add_filter_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".filter");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("filter") = nested_module;
    bp::scope parent           = nested_module;

    bp::class_<edsp::filter::moving_median<real_t>, boost::noncopyable>("MovingMedianFilter", bp::init<real_t>())
        .def("size", &edsp::filter::moving_median<real_t>::size)
        .def("resize", &edsp::filter::moving_median<real_t>::resize)
        .def("reset", &edsp::filter::moving_median<real_t>::reset)
        .def("__call__", &edsp::filter::moving_median<real_t>::operator())
        .def("filter", wrapper_median_filter);

    bp::class_<edsp::filter::moving_average<real_t>, boost::noncopyable>("MovingAverageFilter", bp::init<real_t>())
        .def("size", &edsp::filter::moving_average<real_t>::size)
        .def("resize", &edsp::filter::moving_average<real_t>::resize)
        .def("reset", &edsp::filter::moving_average<real_t>::reset)
        .def("__call__", &edsp::filter::moving_average<real_t>::operator())
        .def("filter", wrapper_average_filter);

    bp::class_<edsp::filter::moving_rms<real_t>, boost::noncopyable>("MovingRmsFilter", bp::init<real_t>())
        .def("size", &edsp::filter::moving_rms<real_t>::size)
        .def("resize", &edsp::filter::moving_rms<real_t>::resize)
        .def("reset", &edsp::filter::moving_rms<real_t>::reset)
        .def("__call__", &edsp::filter::moving_rms<real_t>::operator())
        .def("filter", wrapper_rms_filter);
}