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
 * File: moment.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-06-13
 */
#ifndef EDSP_STATISTICAL_MOMENT_H
#define EDSP_STATISTICAL_MOMENT_H

#include <edsp/statistics/mean.hpp>
#include <edsp/meta/iterator.hpp>
#include <numeric>

namespace edsp { namespace statistics {

    namespace internal {

        // TODO: update this internal
        // From: https://gist.github.com/ofZach/4014022
        template <int N, class T>
        constexpr T nthPower(T x) {
            T ret = x;
            for (int i = 1; i < N; ++i) {
                ret *= x;
            }
            return ret;
        }

        template <class T, int N>
        struct SumDiffNthPower {
            explicit SumDiffNthPower(T x) : mean_(x) {}
            constexpr T operator()(T sum, T current) {
                return sum + nthPower<N>(current - mean_);
            }
            T mean_;
        };

        template <class T, int N, class Iter_T>
        T nthMoment(Iter_T first, Iter_T last, T mean) {
            const auto cnt = std::distance(first, last);
            return std::accumulate(first, last, T(), SumDiffNthPower<T, N>(mean)) /
                   static_cast<meta::value_type_t<Iter_T>>(cnt);
        }

    } // namespace internal

    /**
     * @brief Computes the n-th moment of the range [first, last)
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @tparam N Order of the moment.
     * @returns The n-th moment of the input range.
     */
    template <std::size_t N, typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> moment(ForwardIt first, ForwardIt last) {
        using input_t = meta::value_type_t<ForwardIt>;
        const auto m  = mean(first, last);
        return internal::nthMoment<input_t, N>(first, last, m);
    }

    /**
    * @brief Computes the nth moment of the range [first, last) considering the precomputed average.
    *
    * @param first Forward iterator defining the begin of the range to examine.
    * @param last Forward iterator defining the end of the range to examine.
    * @param mean Average of the range [first, last)
    * @tparam N Order of the moment.
    * @returns The n-th moment of the input range.
    * @see mean
    */
    template <std::size_t N, typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> moment(ForwardIt first, ForwardIt last,
                                                   const meta::value_type_t<ForwardIt> mean) {
        using input_t = meta::value_type_t<ForwardIt>;
        return internal::nthMoment<input_t, N>(first, last, mean);
    }

}} // namespace edsp::statistics

#endif // EDSP_STATISTICAL_MOMMENT_H
