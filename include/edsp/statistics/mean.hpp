/*
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
 * You should have received a copy of the GNU General Public License along width
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * File: mean.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EDSP_STATISTICAL_MEAN_H
#define EDSP_STATISTICAL_MEAN_H

#include <edsp/meta/iterator.hpp>
#include <numeric>
#include <algorithm>

namespace edsp { namespace statistics {

    /**
     * @brief Computes the average or mean value of the range [first, last)
     *
     * The average is defined as:
     * \f[
     *      \mu = \frac{1}{N}\sum_{n=0}^{N-1}x(n)
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The average of the input range.
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> mean(ForwardIt first, ForwardIt last) {
        using input_t  = meta::value_type_t<ForwardIt>;
        const auto acc = std::accumulate(first, last, static_cast<input_t>(0));
        return acc / static_cast<input_t>(std::distance(first, last));
    }
}} // namespace edsp::statistics

#endif // EDSP_STATISTICAL_MEAN_H
