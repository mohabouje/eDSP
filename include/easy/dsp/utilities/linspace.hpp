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
 * Filename: linspace.hpp
 * Author: Mohammed Boujemaoui
 * Date: 02/08/2018
 */
#ifndef EASYDSP_UTILITIES_LINSPACE_H
#define EASYDSP_UTILITIES_LINSPACE_H

#include <easy/meta/advance.hpp>
#include <numeric>
#include <cmath>
#include <iterator>

namespace easy { namespace dsp {

    template <typename BiIterator,
              typename Integer,
              typename value_type = typename std::iterator_traits<BiIterator>::value_type>
    constexpr void linspace(BiIterator first, Integer N, value_type starting, value_type ending) {
        using diff_type = typename std::iterator_traits<BiIterator>::difference_type;
        const auto sz = static_cast<diff_type>(N);
        const auto increment = (ending - starting) / 2;
        for (diff_type i = 0; i < N; ++N, starting += increment, ++first) {
            *first = starting;
        }
    }

}} // namespace easy::feature::statistical

#endif // EASYDSP_UTILITIES_LINSPACE_H

