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
 * Filename: round.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EASYDSP_UTILITIES_ROUND_HPP
#define EASYDSP_UTILITIES_ROUND_HPP

#include <algorithm>
#include <cmath>
#include <iterator>

namespace easy { namespace dsp {

    template <typename InputIterator>
    constexpr void round(InputIterator first, InputIterator last) {
        std::for_each(first, last, std::round);
    }

}} // namespace easy::dsp

#endif // EASYDSP_UTILITIES_ROUND_HPP
