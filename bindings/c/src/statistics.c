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
* Filename: statistics.c
* Author: Mohammed Boujemaoui
* Date: 26/03/19
*/

#include "cedsp/statistics.h"
#include <edsp/statistics.hpp>
#include <iostream>


real_t harmonic_mean(const real_t* data, int size) {
    return edsp::statistics::harmonic_mean(data, data + size);
}

real_t generalized_mean(const real_t* data, int size, int beta) {
    return edsp::statistics::generalized_mean(data, data + size, beta);
}

real_t geometric_mean(const real_t* data, int size) {
    return edsp::statistics::geometric_mean(data, data + size);
}

real_t kurtosis(const real_t* data, int size) {
    return edsp::statistics::kurtosis(data, data + size);
}

real_t max(const real_t* data, int size) {
    return edsp::statistics::max(data, data + size);
}

real_t min(const real_t* data, int size) {
    return edsp::statistics::min(data, data + size);
}

real_t max_abs(const real_t* data, int size) {
    return edsp::statistics::maxabs(data, data + size);
}

real_t min_abs(const real_t* data, int size) {
    return edsp::statistics::minabs(data, data + size);
}

real_t mean(const real_t* data, int size) {
    return edsp::statistics::mean(data, data + size);
}

real_t median(const real_t* data, int size) {
    return edsp::statistics::median(data, data + size);
}

real_t moment(const real_t* data, int size, int n) {
    switch (n) {
        case 1:
            return edsp::statistics::moment<1>(data, data + size);
        case 2:
            return edsp::statistics::moment<2>(data, data + size);
        case 3:
            return edsp::statistics::moment<3>(data, data + size);
        case 4:
            return edsp::statistics::moment<4>(data, data + size);
        case 5:
            return edsp::statistics::moment<5>(data, data + size);
        case 6:
            return edsp::statistics::moment<6>(data, data + size);
        case 7:
            return edsp::statistics::moment<7>(data, data + size);
        case 8:
            return edsp::statistics::moment<8>(data, data + size);
        default:
            std::cerr << "Maximum moment: " << 8 << std::endl;
            return 0;
    }
}

real_t norm(const real_t* data, int size) {
    return edsp::statistics::norm(data, data + size);
}

Peak peak(const real_t* data, int size) {
    const auto peak = edsp::statistics::peak(data, data + size);
    return Peak{static_cast<int>(peak.first), peak.second};
}

Peak peak_abs(const real_t* data, int size) {
    const auto peak = edsp::statistics::peak(data, data + size);
    return Peak{static_cast<int>(peak.first), peak.second};
}

real_t skewness(const real_t* data, int size) {
    return edsp::statistics::skewness(data, data + size);
}

real_t variance(const real_t* data, int size) {
    return edsp::statistics::variance(data, data + size);
}

real_t standard_deviation(const real_t* data, int size) {
    return edsp::statistics::standard_deviation(data, data + size);
}
