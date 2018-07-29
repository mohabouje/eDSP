/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi
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
 * Filename: amplifier.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_amplifier_HPP
#define EASYDSP_amplifier_HPP

#include <algorithm>

namespace easy { namespace dsp {

    template <typename InputIterator, typename OutputIterator,
              typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    constexpr void amplifier(InputIterator first, InputIterator last, OutputIterator out, value_type factor) {
        std::transform(first, last, out, [factor](const double val) { return factor * val; });
    };

    template <typename InputIterator, typename OutputIterator,
              typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    constexpr void amplifier(InputIterator first, InputIterator last, OutputIterator out, value_type factor,
                               value_type min, value_type max) {
        std::transform(first, last, out, [factor, min, max](const double val) {
            const auto scaled = factor * val;
            return (scaled < min) ? min : (scaled > max) ? max : scaled;
        });
    };

    template <typename BiIterator, typename value_type = typename std::iterator_traits<BiIterator>::value_type>
    constexpr void amplifier(BiIterator first, BiIterator last, value_type factor) {
        amplifier(first, last, first, factor);
    };

    template <typename BiIterator, typename value_type = typename std::iterator_traits<BiIterator>::value_type>
    constexpr void amplifier(BiIterator first, BiIterator last, value_type factor, value_type min, value_type max) {
        amplifier(first, last, first, factor, min, max);
    };

    template <typename Container, typename value_type = typename Container::value_type>
    constexpr void amplifier(Container& container, value_type factor) {
        amplifier(std::begin(container), std::end(container), factor);
    };

    template <typename Container, typename value_type = typename Container::value_type>
    constexpr void amplifier(Container& container, value_type factor, value_type min, value_type max) {
        amplifier(std::begin(container), std::end(container), factor, min, max);
    };
}} // namespace easy::dsp

#endif // EASYDSP_amplifier_HPP
