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
#ifndef EDSP_IS_SILENCE_H
#define EDSP_IS_SILENCE_H

#include "feature.hpp"

#include <numeric>
#include <cmath>

EDSP_BEGIN_NAMESPACE

/**
 * @brief Checks if a signal is silence given a pre defined threshold in dB.
 */
class IsSilence : public Feature {
public:
    /**
     * @brief Create a silence checker with the given threshold
     * @param threshold_dB Threshold in dB.
     */
    explicit IsSilence(value_type threshold_dB);

    ~IsSilence() EDSP_OVERRIDE;

    /**
     * @brief Set the threshold
     * @param threshold_linear Threshold in dB
     */
    EDSP_INLINE void set_threshold(_In_ value_type threshold_linear) EDSP_NOEXCEPT;

    /**
     * @brief Returns the threshold
     * @return Threshold in dB
     */
    EDSP_INLINE value_type threshold() EDSP_NOEXCEPT;
protected:
    EDSP_INLINE void extract_implementation(_In_ const value_type *input, _In_ size_type size, _Out_ value_type *output) EDSP_OVERRIDE;
    value_type _threshold_dB = -20;
};

void IsSilence::extract_implementation(_In_ const Feature::value_type *input, _In_ Feature::size_type size, _Out_
                                       Feature::value_type *output) {
    const value_type energy = std::inner_product(input, input + size, input, static_cast<value_type >(0));
    *output = (20 * std::log10(energy) <= _threshold_dB);
};

void IsSilence::set_threshold(_In_ Feature::value_type threshold_dB) EDSP_NOEXCEPT {
    _threshold_dB = threshold_dB;
}

Feature::value_type IsSilence::threshold() EDSP_NOEXCEPT {
    return _threshold_dB;
}

IsSilence::IsSilence(Feature::value_type threshold_dB) : _threshold_dB(threshold_dB) {

}

IsSilence::~IsSilence() {

}

EDSP_END_NAMESPACE
#endif //EDSP_IS_SILENCE_H
