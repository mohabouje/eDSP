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
 * Date: 14/6/2018
 */
#ifndef EASYDSP_STATISTICAL_RMS_H
#define EASYDSP_STATISTICAL_RMS_H

#include <numeric>
#include <cmath>
#include <iterator>

namespace easy { namespace dsp { namespace statistics {

    template <typename InputIterator, typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    inline value_type rms(InputIterator first, InputIterator last) {
        const value_type accumulated = std::inner_product(first, last, static_cast<value_type>(0));
        return std::sqrt(accumulated / static_cast<value_type>(std::distance(first, last)));
    }
}}} // namespace easy::feature::statistical

#endif // EASYDSP_STATISTICAL_RMS_H
