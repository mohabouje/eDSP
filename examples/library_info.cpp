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
#include <edsp/core/library_info.hpp>

#include <iostream>

int main() {
    eInfo() << "Welcome to eDSP";
    eInfo() << "Version Number:" << edsp::library_info::version();
    eInfo() << "Build Date:" << edsp::library_info::build_date();
    eInfo() << "Build Time:" << edsp::library_info::build_time();
    eInfo() << "Running On:" << edsp::system_info::os();
    eInfo() << "Architecture:" << edsp::system_info::processor();
    eInfo() << "Compiler:" << edsp::system_info::compiler();
    eInfo() << "FFT library: " << edsp::library_info::fft_library();
    eInfo() << "Codec library: " << edsp::library_info::codec_library();
    return 0;
}
