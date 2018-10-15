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
 * File: spectral_variation.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_SPECTRAL_VARIATION_HPP
#define EDSP_SPECTRAL_VARIATION_HPP

#include <edsp/feature/statistics/variation.hpp>

namespace edsp { namespace feature { inline namespace spectral {

    /**
     * @brief Computes the spectral variation of the of the magnitude spectrum represented by the elements in the range [first, last)
     * and the elements starting in d_first.
     *
     * The spectral variation is a representation of the similarity between two magnitude spectrums. It is a parameter
     * similar to the spectral flux:
     *
     * \f[
     *
     *  v = 1 - \frac{\sum_k X_1(k) X_2(K)  }{ \sqrt{ \sum_k X_1(k)} \sqrt{\sum_k X_2(k)}}
     *
     * \f]
     *
     * If the variation is close to 0, the spectrum are really similar. Otherwise,
     * if it is close to 1, they are highly dissimilar.
     *
     * @param first1 Forward iterator defining the begin of the first magnitude spectrum.
     * @param last1 Forward iterator defining the end of the first magnitude spectrum.
     * @param first2 Input iterator defining the beginning of the second magnitude spectrum.
     * @return The estimated spectral variation.
     * @see statistics::flux, statistics::variation
     */
    template <typename ForwardIt>
    constexpr auto spectral_variation(ForwardIt first1, ForwardIt last1, ForwardIt first2) {
        return statistics::variation(first1, last1, first2);
    }

}}} // namespace edsp::feature::spectral

#endif //EDSP_SPECTRAL_VARIATION_HPP
