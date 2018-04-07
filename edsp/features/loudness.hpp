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
#ifndef EDSP_LOUDNESS_H
#define EDSP_LOUDNESS_H


#include <numeric>
#include <cmath>
#include "feature.hpp"
EDSP_BEGIN_NAMESPACE

class Loudness : public Feature {
public:
    explicit Loudness(_In_ value_type factor);
    Loudness();
    ~Loudness() EDSP_OVERRIDE;

    EDSP_INLINE void set_factor(_In_ value_type factor) EDSP_NOEXCEPT;

    EDSP_INLINE value_type factor() EDSP_NOEXCEPT;
private:
    EDSP_INLINE void extract(_In_ const value_type *input, _In_ size_type size, _Out_ value_type *output) EDSP_OVERRIDE;
    value_type _factor = 0.67;
};

void Loudness::extract(_In_ const Feature::value_type *input, _In_ Feature::size_type size, _Out_ Feature::value_type *output) {
    *output = std::inner_product(input, input + size, input, static_cast<value_type>(0));
    std::pow(*output, _factor);
}

Loudness::Loudness() = default;

Loudness::~Loudness() = default;

Loudness::Loudness(_In_ Feature::value_type _factor) : _factor(_factor) {}

void Loudness::set_factor(_In_ Feature::value_type factor) EDSP_NOEXCEPT {
    _factor = factor;
}

Feature::value_type Loudness::factor() EDSP_NOEXCEPT {
    return _factor;
}

EDSP_END_NAMESPACE
#endif //EDSP_LOUDNESS_H
