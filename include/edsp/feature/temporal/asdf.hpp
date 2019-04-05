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
 * File: asdf.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_ASDF_HPP
#define EDSP_ASDF_HPP

#include <iterator>
#include <edsp/math/numeric.hpp>

namespace edsp { namespace feature { inline namespace temporal {

    /**
        * @brief Computes the ASDF (Average Square Difference Function) of the contiguous elements in the range [first, last)
        * and stores the result in another range, beginning at d_first.
        *
        * The definition of ASDF is:
        *
        * \f[
        *
        * Q_x[k,n_0] \triangleq \frac{1}{N} \sum\limits_{n=0}^{N-1} \big( x[n+n_0] - x[n+n_0+k] \big)^2
        *
        * \f]
        *
        * There is a relation between the ASDF function and the ACF function:
        *
        * \f[
        *
        * \begin{align}
        * x[k] & \triangleq \frac{1}{N} \sum x[n] x[n+k] \\
        * & =  \overline{x^2[n]} - \tfrac{1}{2} Q_x[k] \\
        * & =  R_x[0] - \tfrac{1}{2} Q_x[k] \\
        * \end{align}
        *
        * \f]
        *
        * @param first Input iterator defining the begin of the range to examine.
        * @param last Input iterator defining the end of the range to examine.
        * @param d_first Output iterator defining the begin of the output range.
        * @see acf, amdf
        */
    template <typename InputIt, typename OutputIt>
    constexpr void asdf(InputIt first, InputIt last, OutputIt d_first) {
        using value_type = typename std::iterator_traits<OutputIt>::value_type;
        const auto N     = std::distance(first, last);
        auto* array      = &(*first);
        for (auto i = 0; i < N; ++i, ++d_first) {
            *d_first = static_cast<value_type>(0);
            for (auto j = 0; j < (N - i); ++j) {
                *d_first += math::square(array[j] - array[j + i]);
            }
            *d_first /= static_cast<value_type>(N);
        }
    }
}}}    // namespace edsp::feature::temporal
#endif //EDSP_ASDF_HPP
