/*
 * EasyDSP, Yet another header-only library for C++ meta-programming.
 * Copyright (C) 2018 Mohammed Boujemaoui
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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: windowing_binding.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-29
 */
#ifndef PYTHON_BINDING_WINDOWING_H
#define PYTHON_BINDING_WINGOWING_H

#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/iterator.hpp>

#include <easy/dsp/windowing/flat_top.hpp>
#include <easy/dsp/windowing/blackman.hpp>
#include <easy/dsp/windowing/hanning.hpp>
#include <easy/dsp/windowing/hamming.hpp>
#include <easy/dsp/windowing/rectangular.hpp>
#include <easy/dsp/windowing/bartlett.hpp>
#include <easy/dsp/windowing/triangular.hpp>
#include <easy/dsp/windowing/windowing.hpp>
#include <easy/dsp/windowing/window_impl.hpp>
#include <easy/meta/unused.hpp>
#include <cstdint>
#include <vector>

using namespace boost::python;
using namespace easy::dsp::windowing;

template <class Window>
void window_setitem(Window& v, typename Window::size_type index, typename Window::value_type value) {
    if (index >= 0 && index < v.size()) {
        v[index] = value;
    } else {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        throw_error_already_set();
    }
}

template <class Window>
typename Window::value_type window_getitem(const Window& v, typename Window::size_type index) {
    if (index >= 0 && index < v.size()) {
        return v[index];
    } else {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        throw_error_already_set();
    }
}

template <class Window>
void window_delitem(Window& v, typename Window::size_type index) {
    easy::meta::unused(v);
    easy::meta::unused(index);
    PyErr_SetString(PyExc_IndexError, "operation not allowed");
    throw_error_already_set();
}

template <class Window>
boost::python::list window_apply(Window& w, boost::python::list data) {
    using value_type     = typename Window::value_type;
    using size_type      = typename Window::size_type;
    const size_type size = static_cast<size_type>(boost::python::len(data));
    std::vector<value_type> converted, windowed;
    converted.reserve(size), windowed.reserve(size);
    for (size_type i = 0; i < size; ++i) {
        converted.push_back(boost::python::extract<value_type>(data[i]));
    }

    w.compute(std::cbegin(converted), std::cend(converted), std::back_inserter(windowed));
    boost::python::list output;
    for (auto element : windowed) {
        output.append(element);
    }

    return output;
}

template <typename W>
void declare_window(const char* name) {
    using value_type = typename W::value_type;
    using size_type  = typename W::size_type;
    class_<W>(name, init<size_type>())
        .def("__iter__", iterator<W>())
        .def("__len__", &W::size)
        .def("__getitem__", &window_getitem<W>)
        .def("__setitem__", &window_setitem<W>)
        .def("__delitem__", &window_delitem<W>)
        .def("set_size", &W::set_size)
        .def("get_size", &W::size)
        .def("apply", &window_apply<W>);
}

class Windowing {
public:
    static boost::python::list apply(const char* window_name, boost::python::list data) {
        const std::size_t size = static_cast<std::size_t>(boost::python::len(data));
        if (strcmp(window_name, "Bartlett") == 0) {
            auto w = Bartlett<double>(size);
            return window_apply(w, data);
        } else if (strcmp(window_name, "Blackman") == 0) {
            auto w = Blackman<double>(size);
            return window_apply(w, data);
        } else if (strcmp(window_name, "Hamming") == 0) {
            auto w = Hamming<double>(size);
            return window_apply(w, data);
        } else if (strcmp(window_name, "Hanning") == 0) {
            auto w = Hanning<double>(size);
            return window_apply(w, data);
        } else if (strcmp(window_name, "Rectangular") == 0) {
            auto w = Rectangular<double>(size);
            return window_apply(w, data);
        } else if (strcmp(window_name, "Triangular") == 0) {
            auto w = Triangular<double>(size);
            return window_apply(w, data);
        } else if (strcmp(window_name, "FlatTop") == 0) {
            auto w = FlatTop<double>(size);
            return window_apply(w, data);
        } else {
            PyErr_SetString(PyExc_IndexError, "window does not exist");
            throw_error_already_set();
        }
        return boost::python::list{};
    }
};

<<<<<<< HEAD:python/windowing_binding.hpp
#endif


=======
BOOST_PYTHON_MODULE(PYTHON_MODULE_NAME) {
    scope windowing = class_<Windowing>("Windowing").def("apply", &Windowing::apply).staticmethod("apply");

    declare_window<Bartlett<double>>("Bartlett");
    declare_window<Blackman<double>>("Blackman");
    declare_window<Hamming<double>>("Hamming");
    declare_window<Hanning<double>>("Hanning");
    declare_window<Rectangular<double>>("Rectangular");
    declare_window<FlatTop<double>>("FlatTop");
    declare_window<Triangular<double>>("Triangular");
}
>>>>>>> master:python/windowing_binding.cpp
