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
 * Filename: standard_deviation.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EASYDSP_STATISTICAL_STANDARD_DEVIATION_H
#define EASYDSP_STATISTICAL_STANDARD_DEVIATION_H

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <numeric>

namespace easy { namespace dsp { namespace statistics {
    template <typename InputIterator, typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    inline value_type standard_deviation(InputIterator first, InputIterator last) {
        using namespace boost::accumulators;
        accumulator_set<value_type, features<tag::variance>> acc;
        acc = std::for_each(first, last, acc);
        return std::sqrt(boost::accumulators::variance(acc));
    }

}}} // namespace easy::dsp::statistics

#endif // EASYDSP_STATISTICAL_STANDARD_DEVIATION_H
