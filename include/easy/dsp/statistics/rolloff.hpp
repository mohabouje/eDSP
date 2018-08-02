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
 * Filename: rolloff.hpp
 * Author: Mohammed Boujemaoui
 * Date: 17/6/2018
 */
#ifndef EASYDSP_STATISTICAL_ROLLOFF_HPP
#define EASYDSP_STATISTICAL_ROLLOFF_HPP

#include <algorithm>
#include <numeric>

namespace easy { namespace dsp { namespace statistics {

    template <typename InputIterator, typename PercentageType,
              typename std::enable_if<std::is_floating_point<PercentageType>::value>::type>
    inline InputIterator rolloff(InputIterator first, InputIterator last, PercentageType percentage = 0.85) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        const PercentageType limit =
            percentage * static_cast<PercentageType>(std::accumulate(first, last, static_cast<value_type>(0)));
        auto accumulated = static_cast<PercentageType>(0);
        for (; first != last; ++first) {
            accumulated += *first;
            if (accumulated >= limit) {
                return first;
            }
        }
        return last;
    }

}}} // namespace easy::feature::statistical

#endif // EASYDSP_STATISTICAL_ROLLOFF_HPP
