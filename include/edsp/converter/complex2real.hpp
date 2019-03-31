/* 
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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

 * File: complex2real.hpp
 * Date: 04/10/18
 * Author: Mohammed Boujemaoui Boulaghmoudi
 */

#ifndef EDSP_COMPLEX2REAL_HPP
#define EDSP_COMPLEX2REAL_HPP

#include <edsp/meta/iterator.hpp>
#include <algorithm>
#include <complex>

namespace edsp { inline namespace converter {

    /**
     * @brief Converts a range of complex numbers in two ranges storing the real and imaginary parts.
     * @param first Input iterator defining the beginning of the range.
     * @param last Input iterator defining the ending of the range.
     * @param d_first1 Output iterator defining the beginning of the real part.
     * @param d_first2 Output iterator defining the beginning of the imaginary part.
     */
    template <typename InputIt, typename OutputIt>
    constexpr void complex2real(InputIt first, InputIt last, OutputIt d_first1, OutputIt d_first2) {
        for (; first != last; ++first, ++d_first1, ++d_first2) {
            *d_first1 = std::real(*first);
            *d_first2 = std::imag(*first);
        }
    }

}} // namespace edsp::converter

#endif //EDSP_COMPLEX2REAL_HPP
