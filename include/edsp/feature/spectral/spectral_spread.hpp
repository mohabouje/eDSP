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
 * File: spectral_spread.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_SPECTRAL_SPREAD_HPP
#define EDSP_SPECTRAL_SPREAD_HPP

#include <edsp/feature/statistics/spread.hpp>

namespace edsp { namespace feature { inline namespace spectral {

    /**
     * @brief Computes the spectral spread of the of the magnitude spectrum represented by the elements in the range [first, last)
     *
     * The spectral spread describes the average deviation of the rate-map around its centroid,
     * which is commonly associated with the bandwidth of the signal
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
     * @brief The estimated spectral spread
     * @see http://www.nyu.edu/classes/bello/MIR_files/timbre.pdf
     */
    template <typename ForwardIt>
    constexpr auto spectral_spread(ForwardIt first1, ForwardIt last1, ForwardIt first2) {
        return statistics::weighted_spread(first1, last1, first2);
    }

}}} // namespace edsp::feature::spectral

#endif //EDSP_SPECTRAL_SPREAD_HPP
