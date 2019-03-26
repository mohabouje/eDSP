/*
* edsp, Yet another framework for building deep RNN networks written in modern C++.
*
* The 2-Clause BSD License
*
* Copyright (c) 2019 Mohammed Boujemaoui Boulaghmoudi,
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Filename: statistics.c
* Author: Mohammed Boujemaoui
* Date: 26/03/19
*/

#include "statistics.h"

#include <iostream>
#include <edsp/statistics.hpp>

real_t centroid(const real_t *data, int size) {
    return edsp::statistics::centroid(data, data + size);
}

real_t centroid_weighted(const real_t *data, int size, const real_t *weights) {
    return edsp::statistics::centroid(data, data + size, weights);
}

real_t entropy(const real_t *data, int size) {
    return edsp::statistics::entropy(data, data + size);
}

real_t flatness(const real_t *data, int size) {
    return edsp::statistics::flatness(data, data + size);
}

real_t harmonic_mean(const real_t *data, int size) {
    return edsp::statistics::harmonic_mean(data, data + size);
}

real_t generalized_mean(const real_t *data, int size, int beta) {
    return edsp::statistics::generalized_mean(data, data + size, beta);
}

real_t geometric_mean(const real_t *data, int size) {
    return edsp::statistics::geometric_mean(data, data + size);
}

real_t kurtosis(const real_t *data, int size) {
    return edsp::statistics::kurtosis(data, data + size);
}

real_t max(const real_t *data, int size) {
    return edsp::statistics::max(data, data + size);
}

real_t min(const real_t *data, int size) {
    return edsp::statistics::min(data, data + size);
}

real_t max_abs(const real_t *data, int size) {
    return edsp::statistics::maxabs(data, data + size);
}

real_t min_abs(const real_t *data, int size) {
    return edsp::statistics::minabs(data, data + size);
}

real_t mean(const real_t *data, int size) {
    return edsp::statistics::mean(data, data + size);
}

real_t median(const real_t *data, int size) {
    return edsp::statistics::median(data, data + size);
}

real_t moment(const real_t *data, int size, int n) {
    switch (n) {
    case 1:
        return edsp::statistics::moment<1>(data, data + size);
    case 2:
        return edsp::statistics::moment<1>(data, data + size);
    case 3:
        return edsp::statistics::moment<1>(data, data + size);
    case 4:
        return edsp::statistics::moment<1>(data, data + size);
    case 5:
        return edsp::statistics::moment<1>(data, data + size);
    case 6:
        return edsp::statistics::moment<1>(data, data + size);
    case 7:
        return edsp::statistics::moment<1>(data, data + size);
    case 8:
        return edsp::statistics::moment<1>(data, data + size);
    default:
        std::cerr << "Maximum moment: " << 8 << std::endl;
        return 0;
    }
}

real_t norm(const real_t *data, int size) {
    return edsp::statistics::norm(data, data + size);
}

Peak peak(const real_t *data, int size) {
    const auto peak = edsp::statistics::peak(data, data + size);
    return Peak{static_cast<int>(peak.first), peak.second};
}

Peak peak_abs(const real_t *data, int size) {
    const auto peak = edsp::statistics::peak(data, data + size);
    return Peak{static_cast<int>(peak.first), peak.second};
}

real_t skewness(const real_t *data, int size) {
    return edsp::statistics::skewness(data, data + size);
}

real_t variance(const real_t *data, int size) {
    return edsp::statistics::variance(data, data + size);
}

real_t standard_deviation(const real_t *data, int size) {
    return edsp::statistics::standard_deviation(data, data + size);
}
