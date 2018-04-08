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
#ifndef EDSP_FEATURES_ZERO_CROSSING_RATE_H
#define EDSP_FEATURES_ZERO_CROSSING_RATE_H

#include "feature.hpp"
#include "math/math.h"

#include <numeric>
#include <cmath>

EDSP_BEGIN_NAMESPACE
/**
 * @brief Extract the zero crossing rate of a signal
 *
 * The ZCR is the rate of sign-changes along a signal. This feature is heavily used in both speech
 * recognition and music information retrieval.
 *
 * ZCR is defined formally as:
 * \f[
 *      {\displaystyle zcr={\frac {1}{T-1}}\sum _{t=1}^{T-1}\mathbb {1} _{\mathbb {R} _{<0}}(s_{t}s_{t-1})}
 * \f]
 */
class ZeroCrossingRate : public Feature {
    EDSP_DECLARE_ALL_IMPLICITS(ZeroCrossingRate)
public:
    ZeroCrossingRate();
    ~ZeroCrossingRate() EDSP_OVERRIDE;
protected:
    EDSP_INLINE void extract_implementation(_In_ const value_type *input, _In_ size_type size, _Out_
                                            value_type *output) EDSP_OVERRIDE;
};

ZeroCrossingRate::ZeroCrossingRate() = default;

ZeroCrossingRate::~ZeroCrossingRate() = default;

void ZeroCrossingRate::extract_implementation(_In_ const Feature::value_type *input, _In_ Feature::size_type size, _Out_
                                    Feature::value_type *output) {
    *output = 0;
    for (auto iter = input, last = input + size - 1; iter != last; ++iter) {
        *output += (math::sign(*(iter + 1)) != math::sign(*iter)) ? 1 : 0;
    }
    *output /= static_cast<value_type>(size);
}

EDSP_END_NAMESPACE
#endif //EDSP_FEATURES_ZERO_CROSSING_RATE_H
