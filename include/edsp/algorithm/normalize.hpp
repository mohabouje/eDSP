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
 * File: normalizer.hpp
 * Date: 09/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_NORMALIZER_HPP
#define EDSP_NORMALIZER_HPP

#include <algorithm>
#include <edsp/feature/temporal/rms.hpp>
#include <edsp/statistics/max.hpp>
#include <edsp/meta/iterator.hpp>

namespace edsp { inline namespace algorithm {

    /**
     * @brief Normalizes the elements in the range [first, last) and stores the result in another range, beginning at d_first.
     *
     * The denominator is the maximum absolute value of the signal.
     * \f[
     *      y = \frac{x}{\frac{\sum_{n=1}^{N}x(n)}{N}}
     * \f]
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @see maxabs
     */
    template <typename InputIt, typename OutputIt>
    constexpr void normalize(InputIt first, InputIt last, OutputIt d_first) {
        const auto factor = statistics::maxabs(first, last);
        std::transform(first, last, d_first,
                       [factor](const meta::value_type_t<InputIt> value) -> meta::value_type_t<OutputIt> {
                           return static_cast<meta::value_type_t<OutputIt>>(value) / factor;
                       });
    }

    /**
     * @brief Normalizes the elements in the range [first, last) and stores the result in another range, beginning at d_first.
     *
     * The denominator is the RMS value of the signal.
     * \f[
     *   y = \frac{x}{\sqrt{\frac{\sum_{n=1}^{N}\left|x(n)^2\right|}{N}}}
     * \f]
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @see rms
     */
    template <typename InputIt, typename OutputIt>
    constexpr void normalize_rms(InputIt first, InputIt last, OutputIt d_first) {
        const auto factor = feature::rms(first, last);
        std::transform(first, last, d_first,
                       [factor](const meta::value_type_t<InputIt> value) -> meta::value_type_t<OutputIt> {
                           return static_cast<meta::value_type_t<OutputIt>>(value) / factor;
                       });
    }

}} // namespace edsp::algorithm

#endif // EDSP_NORMALIZER_HPP
