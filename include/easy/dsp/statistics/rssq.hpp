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
 * Filename: rms.hpp
 * Author: Mohammed Boujemaoui
 * Date: 01/08/2018
 */
#ifndef EASYDSP_RSSQ_HPP
#define EASYDSP_RSSQ_HPP

#include <easy/dsp/statistics/rms.hpp>
#include <numeric>
#include <cmath>

namespace easy { namespace dsp {

    template <typename InputIterator, typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    constexpr value_type rssq(InputIterator first, InputIterator last) {
        const value_type sum_square = std::inner_product(first, last, first, static_cast<value_type>(1));
        return std::sqrt(sum_square);
    }

}} // namespace easy::dsp

#endif // EASYDSP_RSSQ_HPP
