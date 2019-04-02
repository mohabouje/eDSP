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
 * File: geometric_mean.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EDSP_STATISTICAL_GEOMETRIC_MEAN_H
#define EDSP_STATISTICAL_GEOMETRIC_MEAN_H

#include <edsp/math/numeric.hpp>
#include <edsp/meta/iterator.hpp>
#include <numeric>

namespace edsp { namespace statistics {

    /**
     * @brief Computes the geometric mean of the range [first, last)
     *
     * The geometric mean is defined as:
     * \f[
     *     {\displaystyle \left(\prod _{i=1}^{n}x_{i}\right)^{\frac {1}{n}}={\sqrt[{n}]{x_{1}x_{2}\cdots x_{n}}}}
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The geometric mean of the input range.
     */
    template <typename ForwardIt>
    constexpr auto geometric_mean(ForwardIt first, ForwardIt last) {
        using value_type     = meta::value_type_t<ForwardIt>;
        const auto predicate = [](const auto prev, const auto current) { return prev + std::log(current); };
        const auto acc       = std::accumulate(first, last, static_cast<value_type>(0), predicate);
        const auto sz        = static_cast<value_type>(std::distance(first, last));
        return std::exp(acc / sz);
    }
}} // namespace edsp::statistics

#endif // EDSP_STATISTICAL_GEOMETRIC_MEAN_H
