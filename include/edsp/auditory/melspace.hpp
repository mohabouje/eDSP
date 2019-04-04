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
* Filename: melspace.hpp
* Author: Mohammed Boujemaoui
* Date: 18/10/18
*/

#ifndef EDSP_MELSPACE_HPP
#define EDSP_MELSPACE_HPP

#include <edsp/auditory/converter/hertz2mel.hpp>
#include <edsp/algorithm/linspace.hpp>
#include <algorithm>

namespace edsp { namespace auditory {

    /**
     * @brief This function computes an array of N frequencies uniformly spaced between [x1,x2] on an Mel
     * scale and stores the result in another range, beginning at d_first.
     *
     * @param min Minimum frequency.
     * @param max Maximum frequency..
     * @param N Number of frequencies to generate.
     * @param d_first The beginning of the destination range
     */
    template <typename OutputIt, typename Numeric>
    constexpr void melspace(OutputIt first, OutputIt last, Numeric min, Numeric max) {
        const auto N = std::distance(first, last);
        algorithm::linspace(first, min, max, N);
        std::transform(first, last, first, [](const auto data) { return converter::hertz2mel(data); });
    }

}} // namespace edsp::auditory

#endif //EDSP_MELSPACE_HPP
