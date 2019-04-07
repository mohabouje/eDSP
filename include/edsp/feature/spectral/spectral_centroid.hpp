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
 * File: spectral_centroid.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_SPECTRAL_CENTROID_HPP
#define EDSP_SPECTRAL_CENTROID_HPP

#include <edsp/feature/statistics/centroid.hpp>

namespace edsp { namespace feature { inline namespace spectral {

    /**
     * @brief Computes the spectral centroid of the of the magnitude spectrum represented by the elements in the range [first, last)
     *
     * The spectral centroid is the barycenter (center of mass) of the spectrum. It is calculated as the weighted mean
     * of the frequencies present in the signal, determined using a Fourier transform, with their magnitudes as the weights:[2]
     * \f[
     * {\displaystyle \mathrm {Centroid} ={\frac {\sum _{n=0}^{N-1}f(n)x(n)}{\sum _{n=0}^{N-1}x(n)}}}
     * \đ]
     *
     * @param first Forward iterator defining the begin of the magnitude spectrum.
     * @param last Forward iterator defining the end of the magnitude spectrum.
     * @param first2 Forward iterator defining the begin of the center frequencies range.
     * @return Estimated spectral centroid.
     * @see statistics::centroid
     */
    template <typename ForwardIt>
    constexpr auto spectral_centroid(ForwardIt first, ForwardIt last, ForwardIt first2) {
        return statistics::weighted_centroid(first, last, first2);
    }

}}} // namespace edsp::feature::spectral

#endif //EDSP_SPECTRAL_CENTROID_HPP
