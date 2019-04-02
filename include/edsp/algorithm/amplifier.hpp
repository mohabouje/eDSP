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
 * File: amplifier.hpp
 * Date: 09/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_AMPLIFIER_HPP
#define EDSP_AMPLIFIER_HPP

#include <edsp/meta/iterator.hpp>
#include <algorithm>

namespace edsp { inline namespace algorithm {

    /**
     * @brief Amplifies or attenuates the elements in the range [first, last) and stores the result in another range, beginning at d_first.
     *
     * This function increases the amplitude of the input signal defined in the range [first, last). The output signal is a
     * proportionally amplitude signal dependent of the scale factor (\f$ \alpha \f$):
     *
     * \f[
     *      y(n) = \alpha x(n)
     * \f]
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @param factor Scale factor (\f$ \alpha \f$).
     */
    template <typename InputIt, typename OutputIt, typename Numeric>
    constexpr void amplifier(InputIt first, InputIt last, OutputIt d_first, Numeric factor) {
        std::transform(
            first, last, d_first,
            [=](const meta::value_type_t<InputIt> val) -> meta::value_type_t<OutputIt> { return factor * val; });
    }

    /**
     * @brief Amplifies the signal in the range [first, last) and stores the result in another range, beginning at d_first.
     *
     * This function increases the amplitude of the input signal defined in the range [first, last). The output signal is a
     * proportionally amplitude signal dependent of the scale factor (\f$ \alpha \f$):
     *
     * \f[
     *      y(n) = \alpha x(n)
     * \f]
     *
     * The output signal is then clipped to avoid exceding the threshold defined in the range [min, max].
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @param factor Scale factor (\f$ \alpha \f$).
     * @param min Minimum threshold value.
     * @param max Maximum threshold value.
     */
    template <typename InputIt, typename OutputIt, typename Numeric>
    constexpr void amplifier(InputIt first, InputIt last, OutputIt d_first, Numeric factor, Numeric min, Numeric max) {
        std::transform(first, last, d_first,
                       [=](const meta::value_type_t<InputIt> val) -> meta::value_type_t<OutputIt> {
                           const auto scaled = factor * val;
                           return (scaled < min) ? min : (scaled > max) ? max : scaled;
                       });
    }

}} // namespace edsp::algorithm

#endif // EDSP_AMPLIFIER_HPP
