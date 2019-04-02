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
* Filename: string.cpp
* Author: Mohammed Boujemaoui
* Date: 01/04/19
*/

#include "string.hpp"
#include "boost_numpy_dependencies.hpp"
#include <edsp/string/trim.hpp>
#include <edsp/string/join.hpp>
#include <edsp/string/to_lower.hpp>
#include <edsp/string/to_upper.hpp>
#include <edsp/string/split.hpp>

std::string trim_python(const std::string& data) {
    auto tmp = data;
    edsp::string::trim(tmp);
    return tmp;
}

std::string ltrim_python(const std::string& data) {
    auto tmp = data;
    edsp::string::ltrim(tmp);
    return tmp;
}

std::string rtrim_python(const std::string& data) {
    auto tmp = data;
    edsp::string::rtrim(tmp);
    return tmp;
}

std::string join_python(const boost::python::list &strings, const char delimiter) {
    const auto size = bp::len(strings);
    std::vector<std::string> tmp;
    tmp.reserve(size);

    for (auto i = 0; i < size; ++i) {
        tmp.push_back(bp::extract<std::string>(strings[i]));
    }

    std::string solution;
    edsp::string::join(std::cbegin(tmp), std::cend(tmp), solution, delimiter);
    return solution;
}

std::string to_lower_python(const std::string& data) {
    std::string tmp;
    tmp.reserve(data.size());
    edsp::string::tolower(std::cbegin(data), std::cend(data), std::back_inserter(tmp));
    return tmp;
}

std::string to_upper_python(const std::string& data) {
    std::string tmp;
    tmp.reserve(data.size());
    edsp::string::toupper(std::cbegin(data), std::cend(data), std::back_inserter(tmp));
    return tmp;
}

boost::python::list split_python(const std::string &str, const char delimiter) {
    std::vector<std::string> tmp;
    edsp::string::split(str, std::back_inserter(tmp), delimiter);

    boost::python::list result;
    for (const auto& element : tmp) {
        result.append(element);
    }
    return result;
}

void add_string_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".string");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("string") = nested_module;
    bp::scope parent               = nested_module;

    bp::def("trim", trim_python);
    bp::def("rtrim", rtrim_python);
    bp::def("ltrim", ltrim_python);
    bp::def("join", join_python);
    bp::def("split", split_python);
    bp::def("to_upper", to_upper_python);
    bp::def("to_lower", to_lower_python);
}

