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
* Filename: flux.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_FLUX_HPP
#define EDSP_FLUX_HPP

#include <edsp/math/numeric.hpp>
#include <edsp/meta/advance.hpp>
#include <edsp/meta/iterator.hpp>

namespace edsp { namespace feature { inline namespace statistics {

    /**
     * @brief Computes the flux between the elements in the range [first1, last1) and the
     * elements starting at first2.
     *
     * The flux is a measure of the difference between two signals, it is frequently used to
     * estimates the differences in the power spectral between consecutive frames.
     *
     * @tparam d Type of distance to be compute between each point.
     * @param first1 Input iterator defining the beginning of the first input range.
     * @param last1 Input iterator defining the ending of the first input range.
     * @param first2 Input iterator defining the beginning of the second input range.
     * @return The estimated flux.
     * @see distances, distance
     * @cite Introduction to AUDIO ANALYSIS, THEODOROS GI,ANNAKOPOULOS AGGELOS PIKRAKIS
     */
    template <distances d, typename InputIt>
    constexpr meta::value_type_t<InputIt> flux(InputIt first1, InputIt last1, InputIt first2) {
        using value_type        = meta::value_type_t<InputIt>;
        const auto size         = std::distance(first1, last1);
        const auto current_sum  = std::accumulate(first1, last1, static_cast<value_type>(0));
        const auto previous_sum = std::accumulate(first1, meta::advance(first2, size), static_cast<value_type>(0));
        auto accumulated        = static_cast<value_type>(0);
        for (; first1 != last1; ++first1, ++first2) {
            accumulated += distance<d>(*first1 / current_sum, *first2 / previous_sum);
        }
        return accumulated;
    }

}}} // namespace edsp::feature::statistics

#endif //EDSP_FLUX_HPP
