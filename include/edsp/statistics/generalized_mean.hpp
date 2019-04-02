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
 * File: generalized_mean.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EDSP_STATISTICAL_GENERALIZED_MEAN_H
#define EDSP_STATISTICAL_GENERALIZED_MEAN_H

#include <edsp/math/numeric.hpp>
#include <edsp/meta/iterator.hpp>
#include <numeric>

namespace edsp { namespace statistics {

    /**
     * @brief Computes the generalized mean of the range [first, last)
     *
     * The generalized mean or power mean with exponent \f$ \beta \f$ is defined as:
     * \f[
     *      \mu_{\beta} = \left( \frac{1}{N}\sum_{n=0}^{N-1}x(n)^{\beta} \right) ^{\frac{1}{\beta}}
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param beta Exponent (\f$ \beta \f$).
     * @returns The generalized mean of the input range.
     */
    template <typename ForwardIt, typename Integer>
    constexpr meta::value_type_t<ForwardIt> generalized_mean(ForwardIt first, ForwardIt last, Integer beta) {
        using input_t        = meta::value_type_t<ForwardIt>;
        const auto b         = static_cast<int>(beta);
        const auto predicate = [b](const input_t prev, const input_t current) {
            return static_cast<input_t>(prev + std::pow(current, b));
        };
        const input_t accumulated = std::accumulate(first, last, static_cast<input_t>(0), predicate);
        const input_t temp        = accumulated / static_cast<input_t>(std::distance(first, last));
        return std::pow(temp, math::inv(static_cast<input_t>(b)));
    }

}} // namespace edsp::statistics

#endif // EDSP_STATISTICAL_GENERALIZED_MEAN_H
