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
 * Filename: clipper.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_CLIPPER_HPP
#define EASYDSP_CLIPPER_HPP

#include <algorithm>
#include <iterator>

namespace easy { namespace dsp {

    template <typename InputIterator, typename OutputIterator,
              typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    constexpr void clipper(InputIterator first, InputIterator last, OutputIterator out, value_type min,
                           value_type max) {
        std::transform(first, last, out,
                       [min, max](const double val) { return (val < min) ? min : (val > max) ? max : val; });
    };

    template <typename BiIterator, typename value_type = typename std::iterator_traits<BiIterator>::value_type>
    constexpr void clipper(BiIterator first, BiIterator last, value_type min, value_type max) {
        clipper(first, last, first, min, max);
    };

    template <typename Container, typename value_type = typename Container::value_type>
    constexpr void clipper(Container& container, value_type min, value_type max) {
        clipper(std::begin(container), std::end(container), min, max);
    };
}} // namespace easy::dsp

#endif // EASYDSP_CLIPPER_HPP
