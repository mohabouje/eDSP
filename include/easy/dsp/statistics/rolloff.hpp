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

    template <typename InputIterator, typename Float,
              typename std::enable_if<std::is_floating_point<Float>::value>::type>
    inline Float rolloff(InputIterator first, InputIterator last, Float percentage = 0.85) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        const auto limit = percentage * static_cast<Float>(std::accumulate(first, last, static_cast<value_type>(0)));
        for (auto accumulated = static_cast<Float>(0); first != last; ++first) {
            accumulated += *first;
            if (accumulated >= limit) {
                return first;
            }
        }
        return last;
    }

}}} // namespace easy::dsp::statistics

#endif // EASYDSP_STATISTICAL_ROLLOFF_HPP
