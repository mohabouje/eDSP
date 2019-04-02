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
 * File: cat.hpp
 * Author: Mohammed Boujemaoui
 * Date: 02/08/2018
 */
#ifndef EDSP_ALGORITHM_CAT_H
#define EDSP_ALGORITHM_CAT_H

#include <edsp/meta/advance.hpp>
#include <numeric>
#include <cmath>
#include <iterator>

namespace edsp { inline namespace algorithm {

    /**
     * @brief Concatenates the elements defined in the range [firs1, last1) and [first2, last2),
     * and stores the result in another range, beginning at d_first.
     *
     * @param first1 Forward iterator defining the begin of the first range.
     * @param last1 Forward iterator defining the end of the first range.
     * @param first2 Forward iterator defining the begin of the second range.
     * @param last2 Forward iterator defining the end of the second range.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename InputIt, typename OutputIt>
    constexpr void concatenate(InputIt first1, InputIt last1, InputIt first2, InputIt last2, OutputIt d_first) {
        std::copy(first1, last1, d_first);
        std::copy(first2, last2, meta::advance(d_first, std::distance(first1, last1)));
    }

}} // namespace edsp::algorithm

#endif // EDSP_ALGORITHM_CAT_H
