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
 * Filename: decrease.hpp
 * Author: Mohammed Boujemaoui
 * Date: 17/6/2018
 */
#ifndef EASYDSP_STATISTICAL_DECREASE_HPP
#define EASYDSP_STATISTICAL_DECREASE_HPP

#include <iterator>

namespace easy { namespace dsp { namespace statistics {
    template <typename InputIterator, typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    constexpr value_type decrease(InputIterator first, InputIterator last) {
        const auto size           = std::distance(first, last);
        value_type weighted_sum   = static_cast<value_type>(0);
        value_type unweighted_sum = static_cast<value_type>(0);
        for (value_type i = 0, initial = *first; first != last; ++first, ++i) {
            weighted_sum += (1 / i) * ((*first) - initial);
            unweighted_sum += *first;
        }
        return weighted_sum / unweighted_sum;
    }

}}} // namespace easy::feature::statistical

#endif // EASYDSP_STATISTICAL_DECREASE_HPP
