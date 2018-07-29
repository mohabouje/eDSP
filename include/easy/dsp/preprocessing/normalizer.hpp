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
 * Filename: normalizer.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_NORMALIZER_HPP
#define EASYDSP_NORMALIZER_HPP


#include <algorithm>
#include <iterator>

namespace easy { namespace dsp {
    template <typename InputIterator, typename OutputIterator,
              typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    constexpr void normalizer(InputIterator first, InputIterator last, OutputIterator out) {
        const auto limits = std::minmax_element(first, last);
        const auto factor = std::max(std::abs(limits.first), std::abs(limits.second));
        std::transform(first, last, out, [factor](const double val) { return val / factor; });
    };

    template <typename BiIterator, typename value_type = typename std::iterator_traits<BiIterator>::value_type>
    constexpr void normalizer(BiIterator first, BiIterator last) {
        normalizer(first, last, first);
    };

    template <typename Container, typename value_type = typename Container::value_type>
    constexpr void normalizer(Container& container) {
        normalizer(std::begin(container), std::end(container));
    };

}} // namespace easy::dsp

#endif // EASYDSP_NORMALIZER_HPP
