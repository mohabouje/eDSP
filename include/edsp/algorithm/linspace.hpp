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
 * File: linspace.hpp
 * Author: Mohammed Boujemaoui
 * Date: 02/08/2018
 */
#ifndef EDSP_ALGORITHM_LINSPACE_H
#define EDSP_ALGORITHM_LINSPACE_H

#include <iterator>
#include <cmath>

namespace edsp { inline namespace algorithm {

    /**
     * @brief Generate N linearly spaced values between the range [x1,x2] and stores the result in another range, beginning at d_first.
     *
     * @param x1 Defines the beginning of the interval over which linspace generates points.
     * @param x2 Defines the ending of the interval over which linspace generates points.
     * @param N Number of points to generate.
     * @param d_first The beginning of the destination range
     */
    template <typename OutputIt, typename Numeric, typename Integer>
    constexpr void linspace(OutputIt d_first, Numeric x1, Numeric x2, Integer N) {
        using value_type = typename std::iterator_traits<OutputIt>::value_type;
        const auto size  = static_cast<value_type>(std::trunc(N));

        auto _x1             = static_cast<value_type>(x1);
        auto _x2             = static_cast<value_type>(x2);
        const auto increment = (_x2 - _x1) / static_cast<value_type>(size - 1);
        for (auto i = 0; i < size; ++i, ++d_first, _x1 += increment) {
            *d_first = _x1;
        }
    }

}} // namespace edsp::algorithm

#endif // EDSP_ALGORITHM_LINSPACE_H
