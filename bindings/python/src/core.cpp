/**
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
* Filename: core.cpp
* Author: Mohammed Boujemaoui
* Date: 2019-03-31
*/

#include "core.hpp"
#include "boost_numpy_dependencies.hpp"
#include <cedsp/core.h>

bp::tuple get_environment_python(const char* tag) {
    int error = 0;
    const char* data = get_environment(tag, &error);
    return bp::make_tuple(std::string(data), error);
}

void add_core_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".core");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("core") = nested_module;
    bp::scope parent             = nested_module;

    bp::def("get_minor_version", get_minor_version);
    bp::def("get_major_version", get_major_version);
    bp::def("get_patch_version", get_patch_version);
    bp::def("get_version", get_version);
    bp::def("get_build_date", get_build_date);
    bp::def("get_build_time", get_build_time);
    bp::def("get_fft_library", get_fft_library);
    bp::def("get_codec_library", get_codec_library);
    bp::def("get_resample_library", get_resample_library);
    bp::def("get_environment", get_environment_python);
    bp::def("set_environment", set_environment);
    bp::def("exist_environment", exist_environment);
}