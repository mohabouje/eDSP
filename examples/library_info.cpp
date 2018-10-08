/*
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi
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
 * File: library_info.cpp
 * Author: Mohammed Boujemaoui
 * Date: 05/10/2018
 */

#include <edsp/core/logger.hpp>
#include <edsp/core/system.hpp>

int main() {
    edsp::logger::set_default_level(edsp::logger::trace);
    edsp::logger::set_default_path("./example.txt");
    edsp::logger::set_default_name("example");

    eTrace() << "Trace message!";
    eWarning() << "Warning message!";
    eCritical() << "Critical message!";
    eInfo() << "Information message!";
    eDebug() << "Debug message!";
    eError() << "Error message!";
    eInfo() << "This text should be in red!";


    edsp::logger log = edsp::logger("example");
    log << "Other example of what you can do" << 123123 << 839 << "oh!";

    return 0;
}
