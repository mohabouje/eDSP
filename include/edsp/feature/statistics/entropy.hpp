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
 * File: entropy.hpp
 * Author: Mohammed Boujemaoui
 * Date: 17/6/2018
 */
#ifndef EDSP_STATISTICAL_ENTROPY_HPP
#define EDSP_STATISTICAL_ENTROPY_HPP

#include <edsp/meta/iterator.hpp>
#include <numeric>
#include <cmath>

namespace edsp { namespace feature { inline namespace statistics {

    /**
     * @brief Computes the normalized entropy of the probability mass function given in the range [first, last).
     *
     * Given a normalized probability mass function \f$ p(n) \f$, the entropy can explicitly be written as:
     *
     * \f[
     *      H = - \sum_{n=0}^{N-1} p(n) \log_2 \left( p(n) \right)
     * \f]
     *
     * Normalizing:
     *
     * \f[
     *      H_n = - \frac{H}{log2(N)}
     * \f]
     *
     * @param first Forward iterator defining the begin of the probability mass function.
     * @param last Forward iterator defining the end of the probability mass function.
     * @returns The entropy of the probability mass function.
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> entropy(ForwardIt first, ForwardIt last) {
        using input_t        = meta::value_type_t<ForwardIt>;
        const auto predicate = [](const input_t accumulated, const input_t current) {
            return (accumulated + std::log2(current) * current);
        };
        const auto size = static_cast<input_t>(std::distance(first, last));
        const auto acc  = std::accumulate(first, last, static_cast<input_t>(0), predicate);
        return -acc / std::log2(size);
    }

}}} // namespace edsp::feature::statistics

#endif // EDSP_STATISTICAL_ENTROPY_HPP
