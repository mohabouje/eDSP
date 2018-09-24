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
 * Filename: median.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EASYDSP_STATISTICAL_MEDIANT_HPP
#define EASYDSP_STATISTICAL_MEDIANT_HPP

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <easy/meta/iterator.hpp>
#include <numeric>

namespace easy { namespace dsp { namespace statistics {

    /**
     * @brief Computes the median of the range [first, last)
     *
     * The median of a finite list of numbers can be found by arranging all the numbers from smallest to greatest.
     * If there is an odd number of numbers, the middle one is picked. If there is an even number of observations,
     * then there is no single middle value; the median is then usually defined to be the mean of the two middle values
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The median of the input range.
     */
    template <typename ForwardIt>
    constexpr value_type_t<ForwardIt> median(ForwardIt first, ForwardIt last) {
        using namespace boost::accumulators;
        using input_t = value_type_t<ForwardIt>;
        accumulator_set<input_t, features<tag::median>> acc;
        acc = std::for_each(first, last, acc);
        return boost::accumulators::median(acc);
    }

}}} // namespace easy::dsp::statistics

#endif //EASYDSP_STATISTICAL_MEDIANT_HPP
