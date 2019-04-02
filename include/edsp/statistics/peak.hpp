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
 * File: peak.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-10-01
 */
#ifndef EDSP_STATISTICAL_PEAK_HPP
#define EDSP_STATISTICAL_PEAK_HPP

#include <edsp/meta/iterator.hpp>
#include <algorithm>

namespace edsp { namespace statistics {

    /**
     * @brief Computes the peak value of the range [first, last)
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns Pair representing the index position and the value of the peak.
     */
    template <typename ForwardIt>
    constexpr auto peak(ForwardIt first, ForwardIt last)
        -> std::pair<typename meta::diff_type_t<ForwardIt>, typename meta::value_type_t<ForwardIt>> {
        const auto iter = std::max_element(first, last);
        return {std::distance(first, iter), *iter};
    }

    /**
     * @brief Computes the absolute peak value of the range [first, last)
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns Pair representing the index position and the value of the peak.
     */
    template <typename ForwardIt>
    constexpr auto peakabs(ForwardIt first, ForwardIt last)
        -> std::pair<typename meta::diff_type_t<ForwardIt>, typename meta::value_type_t<ForwardIt>> {
        using input_t   = meta::value_type_t<ForwardIt>;
        const auto comp = [](const input_t left, const input_t right) { return std::abs(left) < std::abs(right); };
        const auto iter = std::max_element(first, last, comp);
        return {std::distance(first, iter), *iter};
    }

}} // namespace edsp::statistics

#endif // EDSP_STATISTICAL_PEAK_HPP
