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
#ifndef EDSP_POWER_H
#define EDSP_POWER_H


#include <numeric>
#include "feature.hpp"
EDSP_BEGIN_NAMESPACE
/**
 *  @brief Extracts the power of a signal
 *
 * The power of a discrete-time signal is defined as:
 *
 *  \f[
 *     e = \frac{1}{N} \sum_{n = 0}^{N-1} \left| x(n) \right| ^ 2
 *  \f]
 */
class Power : public Feature {
public:
    Power();
protected:
    EDSP_INLINE void extract_implementation(_In_ const value_type *input, _In_ size_type size, _Out_ value_type *output) EDSP_OVERRIDE;
};

void Power::extract_implementation(_In_ const Feature::value_type *input, _In_ Feature::size_type size, _Out_
                                    Feature::value_type *output) {
    *output = std::inner_product(input, input + size, input, static_cast<value_type>(0));
    *output /= static_cast<value_type>(size);
}

Power::Power() = default;

EDSP_END_NAMESPACE
#endif //EDSP_POWER_H
