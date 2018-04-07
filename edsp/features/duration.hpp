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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef EDSP_DURATION_H
#define EDSP_DURATION_H

#include "feature.hpp"

EDSP_BEGIN_NAMESPACE

class Duration : public Feature {
public:
    explicit Duration(_In_ value_type sample_rate);
    Duration();
    ~Duration() EDSP_OVERRIDE;

    EDSP_INLINE void set_sample_rate(_In_ value_type sample_rate) EDSP_NOEXCEPT;

    EDSP_INLINE value_type sample_rate() EDSP_NOEXCEPT;
private:
    EDSP_INLINE void extract(_In_ const value_type *input, _In_ size_type size, _Out_ value_type *output) EDSP_OVERRIDE;
    value_type _sample_rate = 8000;
};

void Duration::extract(_In_ const Feature::value_type *input, _In_ Feature::size_type size, _Out_ Feature::value_type *output) {
    EDSP_UNUSED(input);
    *output = static_cast<value_type>(size) / _sample_rate;
}

Duration::Duration() = default;

Duration::~Duration() = default;

Duration::Duration(_In_ Feature::value_type sample_rate) : _sample_rate(sample_rate) {}

void Duration::set_sample_rate(_In_ Feature::value_type sample_rate) EDSP_NOEXCEPT {
    _sample_rate = sample_rate;
}

Feature::value_type Duration::sample_rate() EDSP_NOEXCEPT {
    return _sample_rate;
}

EDSP_END_NAMESPACE
#endif //EDSP_DURATION_H
