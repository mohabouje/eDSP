/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: linspace.hpp
 * Author: Mohammed Boujemaoui
 * Date: 02/08/2018
 */
#ifndef EASYDSP_ALGORITHM_LINSPACE_H
#define EASYDSP_ALGORITHM_LINSPACE_H

#include <easy/meta/iterator.hpp>
#include <easy/meta/advance.hpp>
#include <numeric>
#include <cmath>

namespace easy { namespace dsp { inline namespace algorithm {

    /**
     * @brief Generate N linearly spaced values between the range [x1,x2] and stores the result in another range, beginning at d_first.
     *
     * @param x1 Defines the beginning of the interval over which linspace generates points.
     * @param x2 Defines the ending of the interval over which linspace generates points.
     * @param N Number of points to generate.
     * @param d_first The beginning of the destination range
     */
    template <typename OutputIt, typename Numeric>
    constexpr void linspace(OutputIt d_first, Numeric N, meta::value_type_t<OutputIt> x1,
                            meta::value_type_t<OutputIt> x2) {
        const auto size      = static_cast<meta::diff_type_t<OutputIt>>(std::trunc(N));
        const auto increment = (x2 - x1) / static_cast<meta::value_type_t<OutputIt>>(size - 1);
        for (auto i = 0; i < size; ++i, ++d_first) {
            *d_first = x1;
            x1 += increment;
        }
    }

}}} // namespace easy::dsp::algorithm

#endif // EASYDSP_ALGORITHM_LINSPACE_H
