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
     * @param d_first Output iterator defining the begin of the output range.
     */
    template <typename InputIt, typename OutputIt>
    constexpr void amdf(InputIt first, InputIt last, OutputIt d_first) {
        using value_type = typename std::iterator_traits<OutputIt>::value_type;
        value_type accumulated = 0;
        for (++first; first != last;) {
            accumulated += math::sign(*first) != math::sign(*(first - 1));
        }
        return accumulated / static_cast<value_type>(std::distance(first, last));
    }


}}}

#endif //EDSP_AZCR_HPP
