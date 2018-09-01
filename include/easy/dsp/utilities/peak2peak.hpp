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
 * Filename: peak2peak.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EASYDSP_PEAK2PEAK_HPP
#define EASYDSP_PEAK2PEAK_HPP

#include <easy/meta/expects.hpp>
#include <cmath>
#include <algorithm>

namespace easy { namespace dsp {

    template <typename InputIterator, typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    constexpr value_type peak2peak(InputIterator first, InputIterator last) noexcept {
        const auto pair = std::minmax_element(first, last);
        return std::abs(pair.second) - std::abs(pair.first);
    }
}} // namespace easy::dsp

#endif // EASYDSP_RMS2PEAK_HPP
