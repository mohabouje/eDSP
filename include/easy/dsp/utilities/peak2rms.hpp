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
 * Filename: peak2rms.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EASYDSP_PEAK2RMS_HPP
#define EASYDSP_PEAK2RMS_HPP

#include "easy/dsp/math/rms.hpp"
#include <easy/meta/expects.hpp>
#include <cmath>
#include <algorithm>

namespace easy { namespace dsp {

    template <typename InputIterator,
              typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    constexpr value_type peak2rms(InputIterator first, InputIterator last) noexcept {
        const auto pair = std::minmax_element(first, last);
        const auto max_abs = std::max(std::abs(pair.first), std::abs(pair.second));
        return max_abs / dsp::rms(first, last);
    }
}}

#endif // EASYDSP_PEAK2RMS_HPP
