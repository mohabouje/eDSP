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
 * File: min.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EDSP_STATISTICAL_MIN_HPP
#define EDSP_STATISTICAL_MIN_HPP

#include <edsp/meta/iterator.hpp>
#include <algorithm>

namespace edsp { namespace statistics {

    /**
     * @brief Computes the minimum value of the range [first, last)
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The minimum value of the input range.
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> min(ForwardIt first, ForwardIt last) {
        return *std::min_element(first, last);
    }

    /**
     * @brief Computes the minimum absolute value of the range [first, last)
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The minimum value of the input range.
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> minabs(ForwardIt first, ForwardIt last) {
        using input_t   = meta::value_type_t<ForwardIt>;
        const auto comp = [](const input_t left, const input_t right) { return std::abs(left) < std::abs(right); };
        return std::abs(*std::min_element(first, last, comp));
    }

}} // namespace edsp::statistics

#endif // EDSP_STATISTICAL_MIN_HPP
