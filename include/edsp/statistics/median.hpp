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
 * File: median.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EDSP_STATISTICAL_MEDIANT_HPP
#define EDSP_STATISTICAL_MEDIANT_HPP

#include <edsp/meta/iterator.hpp>
#include <edsp/meta/unused.hpp>
#include <algorithm>
#include <numeric>

namespace edsp { namespace statistics {

    /**
     * @brief Computes the median of the range [first, last)
     *
     * The median of a finite list of numbers can be found by arranging all the numbers from smallest to greatest.
     * If there is an odd number of numbers, the middle one is picked. If there is an even number of observations,
     * then there is no single middle value; the median is then usually defined to be the mean of the two middle values
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The median of the input range.
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> median(ForwardIt first, ForwardIt last) {
        // TODO: implement the median: do not use sorting algorithm.
        meta::unused(first);
        meta::unused(last);
        return 0;
    }

}} // namespace edsp::statistics

#endif //EDSP_STATISTICAL_MEDIANT_HPP
