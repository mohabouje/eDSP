/*
 * eDSP, A cross-platform DSP framework written in C++.
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
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "generators/singenerator.h"
#include "base/constants.h"
#include <cmath>
using namespace edsp;

SinGenerator::SinGenerator() = default;

SinGenerator::~SinGenerator() = default;

Generator::value_type SinGenerator::generate() EDSP_NOEXCEPT {
    const value_type result = std::sin(2 * Constants<value_type>::pi  * (frequency() * timestamp() + phase()));
    set_timestamp(timestamp() + 1. / samplerate());
    return result;
}
