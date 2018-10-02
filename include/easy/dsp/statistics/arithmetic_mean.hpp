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
 * Filename: arithmetic_mean.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EASYDSP_STATISTICAL_MEAN_H
#define EASYDSP_STATISTICAL_MEAN_H

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <easy/meta/iterator.hpp>

namespace easy { namespace dsp { namespace statistics {

    /**
     * @brief Computes the average or mean value of the range [first, last)
     *
     * The average is defined as:
     * \f[
     *      \mu = \frac{1}{N}\sum_{n=0}^{N-1}x(n)
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The average of the input range.
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> mean(ForwardIt first, ForwardIt last) {
        using namespace boost::accumulators;
        accumulator_set<meta::value_type_t<ForwardIt>, features<tag::mean>> acc;
        acc = std::for_each(first, last, acc);
        return boost::accumulators::mean(acc);
    }
}}} // namespace easy::dsp::statistics

#endif // EASYDSP_STATISTICAL_MEAN_H
