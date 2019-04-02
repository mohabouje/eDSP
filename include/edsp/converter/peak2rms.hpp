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
 * File: peak2rms.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EDSP_PEAK2RMS_HPP
#define EDSP_PEAK2RMS_HPP

#include <edsp/feature/temporal/rms.hpp>
#include <edsp/meta/iterator.hpp>
#include <algorithm>
#include <cmath>

namespace edsp { inline namespace converter {

    /**
     * @brief Maximum Peak-magnitude-to-RMS ratio in the range [first, last)
     *
     * Returns the ratio of the largest absolute value in the range [first, last) to
     * the root-mean-square (RMS) value of the range. The Peak-magnitude-to-RMS Level is:
     * \f[
     *      y =\frac{\left| x \right|_{\infty}}{\sqrt{\frac{1}{N}\sum_{n=0}^{N-1}\left|x\left(i\right)\right|^2}}
     * \f]
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns Peak-magnitude-to-RMS ratio.
     */
    template <typename ForwardIt>
    constexpr auto peak2rms(ForwardIt first, ForwardIt last) {
        const auto pair    = std::minmax_element(first, last);
        const auto max_abs = std::max(std::abs(*pair.first), std::abs(*pair.second));
        return max_abs / feature::temporal::rms(first, last);
    }
}} // namespace edsp::converter

#endif // EDSP_PEAK2RMS_HPP
