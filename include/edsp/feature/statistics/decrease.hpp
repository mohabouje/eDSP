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
 * File: decrease.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 15/10/18
 */

#ifndef EDSP_DECREASE_HPP
#define EDSP_DECREASE_HPP

#include <iterator>

namespace edsp { namespace feature { inline namespace statistics {

    /**
     * @brief Computes the decrease factor of the elements in the range [first, last)
     *
     * The decrease factor represents the amount of decreasing of the signal amplitude. It is defined as:
     * \f[
     *
     *  d = \frac{1}{ \sum_{n=1}^{N-1} x(n)} \sum_{n=1}^{N-1} \frac{x(n) - x(n-1)}{n}
     *
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param beta Exponent (\f$ \beta \f$).
     * @returns A numeric value representing the decrease of the signal.
     */
    template <typename ForwardIt>
    constexpr auto decrease(ForwardIt first, ForwardIt last) {
        using value_t       = typename std::iterator_traits<ForwardIt>::value_type;
        auto weighted_sum   = static_cast<value_t>(0);
        auto unweighted_sum = static_cast<value_t>(0);
        for (value_t i = 0, initial = *first; first != last; ++first, ++i) {
            weighted_sum += ((*first) - initial) / i;
            unweighted_sum += *first;
        }
        return weighted_sum / unweighted_sum;
    }

}}} // namespace edsp::feature::statistics

#endif //EDSP_DECREASE_HPP
