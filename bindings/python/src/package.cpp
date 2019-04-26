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
* Filename: package.cpp
* Author: Mohammed Boujemaoui
* Date: 27/03/19
*/

#include "algorithm.hpp"
#include "windowing.hpp"
#include "statistics.hpp"
#include "spectral.hpp"
#include "converter.hpp"
#include "core.hpp"
#include "string.hpp"
#include "oscillator.hpp"
#include "auditory.hpp"
#include "feature.hpp"
#include "filter.hpp"
#include "io.hpp"
#include "boost_numpy_dependencies.hpp"

BOOST_PYTHON_MODULE(MODULE_NAME) {
    bn::initialize();
    add_core_package();
    add_algorithm_package();
    add_windowing_package();
    add_statistics_package();
    add_spectral_package();
    add_converter_package();
    add_string_package();
    add_oscillator_package();
    add_auditory_package();
    add_feature_temporal_package();
    add_feature_spectral_package();
    add_feature_statistics_package();
    add_filter_package();
    add_io_package();
}
