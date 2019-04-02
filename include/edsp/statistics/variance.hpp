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
 * File: variance.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EDSP_STATISTICAL_VARIANCE_H
#define EDSP_STATISTICAL_VARIANCE_H

#include <edsp/statistics/moment.hpp>
#include <edsp/meta/iterator.hpp>
#include <cmath>

namespace edsp { namespace statistics {

    /**
     * @brief Computes the variance of the range [first, last)
     *
     * The variance is defined as:
     * \f[
     *     v =\sum _{i=1}^{n}p_{i}\cdot (x_{i}-\mu )^{2}
     * \f]
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The variance of the input range.
     * @see standard_deviation
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> variance(ForwardIt first, ForwardIt last) {
        return moment<2>(first, last);
    }

    /**
     * @brief Computes the standard deviation of the range [first, last)
     *
     * The standard deviation is defined as the square root of the variance:
     * \f[
     *     \sigma = \sqrt(v)
     * \f]
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The variance of the input range.
     * @see variance
     */
    template <typename ForwardIt>
    inline meta::value_type_t<ForwardIt> standard_deviation(ForwardIt first, ForwardIt last) {
        return std::sqrt(variance(first, last));
    }

}} // namespace edsp::statistics

#endif // EDSP_STATISTICAL_VARIANCE_H
