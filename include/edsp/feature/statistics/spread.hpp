/**
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (c) 2018 All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * File: spread.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 15/10/18
 */

#ifndef EDSP_SPREAD_HPP
#define EDSP_SPREAD_HPP

#include <edsp/feature/statistics/centroid.hpp>
#include <cmath>

namespace edsp { namespace feature { inline namespace statistics {

    /**
     * @brief Computes the spread coefficient of the of the the elements in the range [first, last)
     *
     * The spectral spread describes the average deviation of the rate-map around its centroid:
     *
     * \f[
     *
     *  ss = \frac{\sum_{n = 0}^{N-1}((f(n) - sc)^2 X(n)}{\sum_{n = 0}^{N-1}X(n)}
     *
     * \f]
     *
     * where sc is the spectral centroid.
     *
     * @param first1 Forward iterator defining the begin of the magnitude spectrum.
     * @param last2 Forward iterator defining the end of the magnitude spectrum.
     * @brief The estimated spread coefficient
     */
    template <typename ForwardIt>
    constexpr auto spread(ForwardIt first1, ForwardIt last1) {
        using value_type    = typename std::iterator_traits<ForwardIt>::value_type;
        const auto centroid = statistics::centroid(first1, last1);
        auto weighted_sum   = static_cast<value_type>(0);
        auto unweighted_sum = static_cast<value_type>(0);
        for (value_type i = 0; first1 != last1; ++first1, ++i) {
            const auto diff = i - centroid;
            weighted_sum += (diff * diff) * (*first1);
            unweighted_sum += *first1;
        }
        return static_cast<value_type>(std::sqrt(weighted_sum / unweighted_sum));
    }

    /**
     * @param first1 Forward iterator defining the begin of the range to examine.
     * @param last1 Forward iterator defining the end of the range to examine.
     * @param first2 Forward iterator defining the beginning of the range representing the weights, \f$f(i)\f$.
     * @returns The spread value of the input range.
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> weighted_spread(ForwardIt first1, ForwardIt last1, ForwardIt first2) {
        using value_type    = typename std::iterator_traits<ForwardIt>::value_type;
        const auto centroid = statistics::weighted_centroid(first1, last1, first2);
        auto weighted_sum   = static_cast<value_type>(0);
        auto unweighted_sum = static_cast<value_type>(0);
        for (; first1 != last1; ++first1, ++first2) {
            const auto diff = *first2 - centroid;
            weighted_sum += (diff * diff) * (*first1);
            unweighted_sum += *first1;
        }
        return static_cast<value_type>(std::sqrt(weighted_sum / unweighted_sum));
    }

}}} // namespace edsp::feature::statistics

#endif //EDSP_SPREAD_HPP
