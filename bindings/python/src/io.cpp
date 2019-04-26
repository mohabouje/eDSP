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

#include "io.hpp"
#include "boost_numpy_dependencies.hpp"
#include <cedsp/types.h>
#include <edsp/io/metadata.hpp>

void add_io_package() {
    std::string nested_name = bp::extract<std::string>(bp::scope().attr("__name__") + ".io");
    bp::object nested_module(bp::handle<>(bp::borrowed(PyImport_AddModule(nested_name.c_str()))));
    bp::scope().attr("io") = nested_module;
    bp::scope parent       = nested_module;

    bp::class_<edsp::io::metadata>("MetaDataReader", bp::init<const std::string&>())
        .def("title", &edsp::io::metadata::title)
        .def("genre", &edsp::io::metadata::genre)
        .def("year", &edsp::io::metadata::year)
        .def("album", &edsp::io::metadata::album)
        .def("artist", &edsp::io::metadata::artist)
        .def("track", &edsp::io::metadata::track);
}