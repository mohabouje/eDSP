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

#include <easy/meta/iterator.hpp>
#include <numeric>
#include <cmath>

namespace easy { namespace dsp { namespace statistics {

    /**
     * @brief The EntropyBase enum defines the base of the logarithm used to compute the entropy.
     */
    enum EntropyBase {
        Bits, /*!< Base 2 */
        Nats, /*!< Base e */
        Bans  /*!< Base 10 */
    };

    /**
     * @brief Computes the entropy of the probability mass function given in the range [first, last)
     *
     * Given a normalized probability mass function \f$ p(n) \f$, the entropy can explicitly be written as:
     *
     * \f[
     *      h =  \sum_{n=0}^{N-1} p(n) \log2 \left( p(n) \right)
     * \f]
     *
     * @param first Forward iterator defining the begin of the probability mass function.
     * @param last Forward iterator defining the end of the probability mass function.
     * @returns The entropy of the probability mass function.
     */
    template <typename ForwardIt>
    constexpr value_type_t<ForwardIt> entropy(ForwardIt first, ForwardIt last) {
        using input_t        = value_type_t<ForwardIt>;
        const auto predicate = [](const input_t accumulated, const input_t current) {
            return (accumulated + std::log2(current) * current);
        };
        return std::accumulate(first, last, static_cast<input_t>(0), predicate);
    }

}}} // namespace easy::dsp::statistics

#endif // EASYDSP_STATISTICAL_ENTROPY_HPP
