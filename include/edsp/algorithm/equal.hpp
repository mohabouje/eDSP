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
 * File: equal.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/9/2018
 */
#ifndef EDSP_EQUAL_HPP
#define EDSP_EQUAL_HPP

#include <algorithm>

namespace edsp { inline namespace algorithm {

    /**
     * @brief Returns true if the range [first1, last1) is equal to the range [first2, last2), and false otherwise.
     *
     * @param first1 Forward iterator defining the begin of the first range.
     * @param last1 Forward iterator defining the end of the first range.
     * @param first2 Forward iterator defining the begin of the second range.
     * @param last2 Forward iterator defining the end of the second range.
     * @param p  	Binary predicate which returns ​true if the elements should be treated as equal.
     * @returns If the elements in the two ranges are equal, returns true. Otherwise returns false.
     */
    template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
    constexpr bool equal(ForwardIt1 first1, ForwardIt2 last1, ForwardIt2 first2, ForwardIt2 last2, BinaryPredicate p) {
        return std::equal(first1, last1, first2, last2, p);
    }

    /**
     * @brief Returns true if the range [first1, last1) is equal to the range [first2, last2), and false otherwise.
     *
     * @param first1 Forward iterator defining the begin of the first range.
     * @param last1 Forward iterator defining the end of the first range.
     * @param first2 Forward iterator defining the begin of the second range.
     * @param last2 Forward iterator defining the end of the second range.
     * @returns If the elements in the two ranges are equal, returns true. Otherwise returns false.
     */
    template <typename ForwardIt1, typename ForwardIt2>
    constexpr bool equal(ForwardIt1 first1, ForwardIt2 last1, ForwardIt2 first2, ForwardIt2 last2) {
        return std::equal(first1, last1, first2, last2);
    }

}} // namespace edsp::algorithm

#endif // EDSP_EQUAL_HPP
