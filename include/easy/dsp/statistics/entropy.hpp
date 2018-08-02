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
 * Filename: entropy.hpp
 * Author: Mohammed Boujemaoui
 * Date: 17/6/2018
 */
#ifndef EASYDSP_STATISTICAL_ENTROPY_HPP
#define EASYDSP_STATISTICAL_ENTROPY_HPP

#include <cmath>
#include <numeric>

namespace easy { namespace dsp { namespace statistics {
    template <typename InputIterator, typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    inline value_type entropy(InputIterator first, InputIterator last) {
        const auto sum       = std::accumulate(first, last, static_cast<value_type>(0));
        const auto predicate = [sum](const value_type accumulated, const value_type current) {
            const auto normalized = current / sum;
            return (accumulated + std::log2(normalized) * normalized);
        };
        return std::accumulate(first, last, static_cast<value_type>(0), predicate);
    }

}}} // namespace easy::feature::statistical

#endif // EASYDSP_STATISTICAL_ENTROPY_HPP
