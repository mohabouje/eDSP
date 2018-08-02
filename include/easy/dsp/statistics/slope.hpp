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
 * Filename: slope.hpp
 * Author: Mohammed Boujemaoui
 * Date: 17/6/2018
 */
#ifndef EASYDSP_STATISTICAL_SLOPE_HPP
#define EASYDSP_STATISTICAL_SLOPE_HPP

#include <iterator>
#include <easy/meta/math.hpp>

namespace easy { namespace dsp { namespace statistics {
    template <typename InputIterator, typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    inline value_type slope(InputIterator first, InputIterator last) {
        value_type weighted_sum     = static_cast<value_type>(0);
        value_type unweighted_sum   = static_cast<value_type>(0);
        value_type index_sum        = static_cast<value_type>(0);
        value_type square_index_sum = static_cast<value_type>(0);
        for (value_type i = 0; first != last; ++first, ++i) {
            weighted_sum += (i) * (*first);
            unweighted_sum += *first;
            index_sum += i;
            square_index_sum += meta::square(i);
        }
        const auto size = std::distance(first, last);
        return (size * weighted_sum - index_sum * unweighted_sum) / (size * square_index_sum - meta::square(index_sum));
    }
}}} // namespace easy::feature::statistical

#endif // EASYDSP_STATISTICAL_SLOPE_HPP
