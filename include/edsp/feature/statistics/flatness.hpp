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
 * File: flatness.hpp
 * Author: Mohammed Boujemaoui
 * Date: 14/6/2018
 */
#ifndef EDSP_STATISTICAL_FLATNESS_H
#define EDSP_STATISTICAL_FLATNESS_H

#include <edsp/statistics/mean.hpp>
#include <edsp/statistics/geometric_mean.hpp>

namespace edsp { namespace feature { inline namespace statistics {

    /**
     * @brief Computes the flatness value of the range [first, last)
     *
     * It is calculated as the division of geometric mean and the average of the magnitudes.
     * \f[
     *      y = \frac{\mu_g}{\mu}
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The flatness value of the input range.
     * @see mean, geometric_mean
     */
    template <typename ForwardIt>
    constexpr auto flatness(ForwardIt first, ForwardIt last) {
        const auto computed_gmean = edsp::statistics::geometric_mean(first, last);
        const auto computed_mean  = edsp::statistics::mean(first, last);
        return computed_gmean / computed_mean;
    }

}}} // namespace edsp::feature::statistics

#endif // EDSP_STATISTICAL_FLATNESS_H
