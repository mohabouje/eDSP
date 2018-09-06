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
 * Filename: cat.hpp
 * Author: Mohammed Boujemaoui
 * Date: 02/08/2018
 */
#ifndef EASYDSP_UTILITIES_CAT_H
#define EASYDSP_UTILITIES_CAT_H

#include <easy/meta/advance.hpp>
#include <numeric>
#include <cmath>
#include <iterator>

namespace easy { namespace dsp {

    template <typename InputIterator, typename OutputIterator>
    constexpr void concatenate(InputIterator first, InputIterator last, InputIterator first2, InputIterator last2,
                               OutputIterator out) {
        std::copy(first, last, out);
        std::copy(first2, last2, meta::advance(out, std::distance(first, last)));
    }

}} // namespace easy::dsp

#endif // EASYDSP_UTILITIES_CAT_H
