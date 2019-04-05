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
 * File: duration.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_DURATION_HPP
#define EDSP_DURATION_HPP

#include <edsp/statistics/max.hpp>

namespace edsp { namespace feature { inline namespace temporal {

    /**
     * @brief Computes the duration of the envelop elements in the range [first, last)
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param sample_rate Sampling frequency in Hz.
     * @returns The estimated duration in seconds.
     */
    template <typename ForwardIt, typename Numeric>
    constexpr auto duration(ForwardIt first, ForwardIt last, Numeric sample_rate) {
        using value_type = typename std::iterator_traits<ForwardIt>::value_type;
        return static_cast<value_type>(std::distance(first, last)) / sample_rate;
    }

    /**
     * @brief Computes the effective duration of the envelop elements in the range [first, last)
     *
     * The effective duration is a measure of the time the signal is perceptually meaningful.
     * It is approximated by the time the energy envelope is above a given threshold.
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param sample_rate Sampling frequency in Hz.
     * @param threshold Numeric value in the range [0, 1] representing the active threshold.
     * @returns The estimated duration in seconds.
     */
    template <typename ForwardIt, typename Numeric>
    constexpr auto effective_duration(ForwardIt first, ForwardIt last, Numeric sample_rate, Numeric threshold) {
        using value_type   = typename std::iterator_traits<ForwardIt>::value_type;
        const auto limit   = threshold * edsp::statistics::maxabs(first, last);
        const auto functor = [limit](const auto sample) { return std::abs(sample) > limit; };
        const auto samples = std::count_if(first, last, functor);
        return static_cast<value_type>(samples) / static_cast<value_type>(sample_rate);
    }
}}} // namespace edsp::feature::temporal

#endif //EDSP_DURATION_HPP
