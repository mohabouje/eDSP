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
 * Filename: moment.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EASYDSP_STATISTICAL_MOMENT_H
#define EASYDSP_STATISTICAL_MOMENT_H

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <easy/meta/iterator.hpp>
#include <numeric>

namespace easy { namespace dsp { namespace statistics {

    /**
     * @brief Computes the n-th moment of the range [first, last)
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @tparam N Order of the moment.
     * @returns The kurtosis of the input range.
     */
    template <std::size_t N, typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> moment(ForwardIt first, ForwardIt last) {
        using namespace boost::accumulators;
        using input_t = meta::value_type_t<ForwardIt>;
        accumulator_set<input_t, features<tag::moment<N>>> acc;
        acc = std::for_each(first, last, acc);
        return boost::accumulators::moment<N>(acc);
    }

}}} // namespace easy::dsp::statistics

#endif // EASYDSP_STATISTICAL_MOMMENT_H
