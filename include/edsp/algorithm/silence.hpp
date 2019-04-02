/*
* eDSP, A cross-platform Digital Signal Processing library written in modern C++.
* Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
* Filename: silence.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_SILENCER_HPP
#define EDSP_SILENCER_HPP

#include <edsp/feature/temporal/power.hpp>

namespace edsp { inline namespace algorithm {

    /**
     * @brief Checks if the elements in the range [first, last) are a silenced frame.
     *
     * A silenced frame is a frame with an instant power up to a threshold.
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param threshold Threshold .
     */
    template <typename InputIt, typename OutputIt, typename Numeric>
    constexpr bool silence(InputIt first, InputIt last, Numeric threshold) {
        return feature::temporal::power(first, last) < threshold;
    }

}} // namespace edsp::algorithm

#endif //EDSP_SILENCER_HPP
