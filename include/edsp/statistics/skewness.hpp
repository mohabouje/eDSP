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
 * File: skewness.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EDSP_STATISTICAL_SKEWNESS_H
#define EDSP_STATISTICAL_SKEWNESS_H

#include <edsp/statistics/moment.hpp>
#include <edsp/meta/iterator.hpp>
#include <cmath>

namespace edsp { namespace statistics {

    /**
     * @brief Computes the skewness of the range [first, last)
     *
     * The skewness is the third standardized moment, defined as:
     * \f[
     *     {\displaystyle K [X]
     *      =E \left[\left({\frac {X-\mu }{\sigma }}\right)^{3}\right]={\frac {\mu _{3}}{\sigma ^{3}}}
     *      ={\frac {E [(X-\mu )^{3}]}{(E[(X-\mu )^{2}])^{2}}},}
     * \f]
     * where \f$ \mu_3 \f$ is the fourth central moment and \f$ \sigma \f$ is the standard deviation.
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The skewness of the input range.
     * @see moment, standard_deviation
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> skewness(ForwardIt first, ForwardIt last) {
        const auto m  = mean(first, last);
        const auto m3 = moment<3>(first, last, m);
        const auto m2 = moment<2>(first, last, m);
        return m3 / (m2 * std::sqrt(m2));
    }
}} // namespace edsp::statistics

#endif // EDSP_STATISTICAL_SKEWNESS_H
