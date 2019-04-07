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
 * File: azcr.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_AZCR_HPP
#define EDSP_AZCR_HPP

#include <edsp/math/numeric.hpp>
#include <iterator>

namespace edsp { namespace feature { inline namespace temporal {

    /**
     * @brief Computes the AZCR (Average Zero Crossing Rate) of the contiguous elements in the range [first, last)
     * and stores the result in another range, beginning at d_first.
     *
     * The definition of AZCR is:
     *
     * \f[
     *
     * {\displaystyle zcr={\frac {1}{T-1}}\sum _{t=1}^{T-1}\mathbb {1} _{\mathbb {R} _{<0}}(s_{t}s_{t-1})}
     *
     * \f]
     *
     * @param first Input iterator defining the begin of the range to examine.
     * @param last Input iterator defining the end of the range to examine.
     * @returns The average zero crossing rate.
     */
    template <typename InputIt>
    constexpr auto azcr(InputIt first, InputIt last) {
        using value_type = typename std::iterator_traits<InputIt>::value_type;
        const auto N     = std::distance(first, last);
        auto accumulated = static_cast<value_type>(0);
        for (first = std::next(first); first != last; ++first) {
            accumulated += static_cast<value_type>(math::sign(*first) != math::sign(*std::prev(first)));
        }
        return accumulated / static_cast<value_type>(N - 1);
    }

}}} // namespace edsp::feature::temporal

#endif //EDSP_AZCR_HPP
