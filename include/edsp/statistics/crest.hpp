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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * File: crest.hpp
 * Author: Mohammed Boujemaoui
 * Date: 14/6/2018
 */
#ifndef EDSP_STATISTICAL_CREST_HPP
#define EDSP_STATISTICAL_CREST_HPP

#include <edsp/statistics/mean.hpp>

namespace edsp { namespace statistics {

    /**
     * @brief Computes the crest value of the range [first, last)
     *
     * It is calculated as the division of mean of the the signal and the maximum value of the magnitudes.
     * \f[
     *      y = \frac{ \frac{1}{N} \sum_{n=0}^{N-1}x(n)}{max \left( x \right)}
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The crest value of the input range.
     * @see mean
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> crest(ForwardIt first, ForwardIt last) {
        const auto computed_mean = statistics::mean(first, last);
        const auto computed_max  = *std::max_element(first, last);
        return computed_max / computed_mean;
    }

}} // namespace edsp::statistics

#endif // EDSP_STATISTICAL_CREST_HPP
