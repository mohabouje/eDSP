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
 * File: spectral_slope.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_SPECTRAL_SLOPE_HPP
#define EDSP_SPECTRAL_SLOPE_HPP

#include <iterator>

namespace edsp { namespace feature { inline namespace spectral {


    /**
     * @brief Computes the spectral slope of the of the magnitude spectrum represented by the elements in the range [first, last)
     *
     * The spectral slope represents the amount of decreasing of the spectral amplitude. It is computed by linear
     * regression of the spectral amplitude:
     *
     * \f[
     *  G = a f + b
     * \f]
     *
     * where a is the parameter of interest. In this case is computed as follows:
     *
     * \f[
     *
     * a = \frac{1}{\sum_k a(k)}
     * \frac{N \sum_k a(k) f(k) - \sum_k a(k) * \sum_k f(k)}
     * {N \sum_k f^2(k) - \left( \sum_k f(k) \right)^2}
     *
     * \f]
     *
     * where f is a vector representing the different frequency bins.
     *
     * @param first1 Forward iterator defining the begin of the magnitude spectrum.
     * @param last1 Forward iterator defining the end of the magnitude spectrum.
     * @param first2 Forward iterator defining the begin of the center frequencies range.
     * @return Estimated spectral slope.
     */
    template <typename ForwardIt>
    constexpr auto spectral_slope(ForwardIt first1, ForwardIt last1, ForwardIt first2) {
        using value_type = typename std::iterator_traits<ForwardIt>::value_type ;
        auto m_sum  = static_cast<value_type>(0);
        auto f_sum  = static_cast<value_type>(0);
        auto ff_sum = static_cast<value_type>(0);
        auto mf_sum = static_cast<value_type >(0);
        for (; first1 != last1; ++first1, ++first2) {
            m_sum += *first1;
            f_sum += *first2;
            mf_sum += (*first1) * (*first2);
            ff_sum += (*first2) * (*first2);
        }
        const auto N = static_cast<value_type >(std::distance(first1, last1));
        return (1 / m_sum) * (N * mf_sum - f_sum * m_sum) / (N * ff_sum - (f_sum * f_sum));
    }

}}}

#endif //EDSP_SPECTRAL_SLOPE_HPP
