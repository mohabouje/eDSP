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
 * Filename: zeros.hpp
 * Author: Mohammed Boujemaoui
 * Date: 02/08/2018
 */
#ifndef EASYDSP_UTILITIES_ZEROS_H
#define EASYDSP_UTILITIES_ZEROS_H

#include <numeric>
#include <cmath>
#include <iterator>

namespace easy { namespace dsp {

    template <typename InputIterator>
    constexpr void zeros(InputIterator first, InputIterator last) {
        std::fill(first, last, static_cast<typename std::iterator_traits<InputIterator>::value_type>(0));
    }

}} // namespace easy::feature::statistical

#endif // EASYDSP_UTILITIES_ZEROS_H

