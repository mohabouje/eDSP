/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
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
 * Filename: decrease.hpp
 * Author: Mohammed Boujemaoui
 * Date: 17/6/2018
 */
#ifndef EASYDSP_STATISTICAL_DECREASE_HPP
#define EASYDSP_STATISTICAL_DECREASE_HPP

#include <easy/meta/iterator.hpp>
#include <easy/dsp/math/numeric.hpp>

namespace easy { namespace dsp { namespace statistics {
    /**
     * @brief Computes the decrease value of the range [first, last)
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The decrease value of the input range.
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> decrease(ForwardIt first, ForwardIt last) {
        using input_t       = meta::value_type_t<ForwardIt>;
        auto weighted_sum   = static_cast<input_t>(0);
        auto unweighted_sum = static_cast<input_t>(0);
        for (input_t i = 0, initial = *first; first != last; ++first, ++i) {
            weighted_sum += math::inv(i) * ((*first) - initial);
            unweighted_sum += *first;
        }
        return weighted_sum / unweighted_sum;
    }

}}} // namespace easy::dsp::statistics

#endif // EASYDSP_STATISTICAL_DECREASE_HPP
