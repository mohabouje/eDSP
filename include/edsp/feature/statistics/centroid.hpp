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
 * File: centroid.hpp
 * Author: Mohammed Boujemaoui
 * Date: 17/6/2018
 */
#ifndef EDSP_STATISTICAL_CENTROID_HPP
#define EDSP_STATISTICAL_CENTROID_HPP

#include <edsp/meta/iterator.hpp>

namespace edsp { namespace feature { inline namespace statistics {

    /**
     * @brief Computes the centroid value of the range [first, last)
     *
     * It is calculated as the division of the weighted mean of the the signal and the average of the magnitudes.
     * \f[
     *      y = \frac{\sum_{n=0}^{N-1}nx(n)}{\sum_{n=0}^{N-1}x(n)}
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The centroid value of the input range.
     * @see mean
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> centroid(ForwardIt first, ForwardIt last) {
        using input_t       = meta::value_type_t<ForwardIt>;
        auto weighted_sum   = static_cast<input_t>(0);
        auto unweighted_sum = static_cast<input_t>(0);
        for (input_t i = 0; first != last; ++first, ++i) {
            weighted_sum += i * (*first);
            unweighted_sum += *first;
        }
        return weighted_sum / unweighted_sum;
    }

    /**
     * @brief Computes the centroid value of the range [first1, last1)
     *
     * It is calculated as the division of the weighted mean of the the signal and the average of the magnitudes.
     * \f[
     *      y = \frac{\sum_{n=0}^{N-1}f(n)x(n)}{\sum_{n=0}^{N-1}x(n)}
     * \f]
     *
     * @param first1 Forward iterator defining the begin of the range to examine.
     * @param last1 Forward iterator defining the end of the range to examine.
     * @param first2 Forward iterator defining the beginning of the range representing the weights, \f$f(i)\f$.
     * @returns The centroid value of the input range.
     * @see mean
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> weighted_centroid(ForwardIt first1, ForwardIt last1, ForwardIt first2) {
        using input_t       = meta::value_type_t<ForwardIt>;
        auto weighted_sum   = static_cast<input_t>(0);
        auto unweighted_sum = static_cast<input_t>(0);
        for (; first1 != last1; ++first1, ++first2) {
            weighted_sum += (*first2) * (*first1);
            unweighted_sum += *first1;
        }
        return weighted_sum / unweighted_sum;
    }

}}} // namespace edsp::feature::statistics

#endif // EDSP_STATISTICAL_CENTROID_HPP
