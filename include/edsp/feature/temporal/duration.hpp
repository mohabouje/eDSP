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

#include <iterator>
#include <algorithm>
#include <functional>

namespace edsp { namespace feature { inline namespace temporal {

    /**
     * @brief Computes the duration of the elements in the range [first, last)
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param samplerate Sampling frequency in Hz.
     * @returns The estimated duration in seconds.
     */
    template <typename ForwardIt, typename Numeric>
    constexpr auto duration(ForwardIt first, ForwardIt last, Numeric samplerate) {
        using value_type = typename std::iterator_traits<ForwardIt>::value_type;
        return static_cast<value_type>(std::distance(first, last)) / samplerate;
    }

    /**
     * @brief Computes the effective duration of the elements in the range [first, last)
     *
     * The effective duration is a measure of the time the signal is perceptually meaningful.
     * It is approximated by the time the energy envelope is above a given threshold.
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param samplerate Sampling frequency in Hz.
     * @param threshold Numeric value in the range [0, 1] representing the active threshold.
     * @returns The estimated duration in seconds.
     */
    template <typename ForwardIt, typename Numeric>
    constexpr auto effective_duration(ForwardIt first, ForwardIt last, Numeric samplerate, Numeric threshold) {
        using value_type       = typename std::iterator_traits<ForwardIt>::value_type;
        const auto pair        = std::minmax_element(first, last);
        const value_type limit = threshold * std::max(std::abs(pair.first), std::abs(pair.second));
        const auto get_threshold =
            std::find_if(first, last, std::bind(std::greater_equal<value_type>(), std::placeholders::_1, limit));
        const auto let_threshold = std::find_if(
            get_threshold, last, std::bind(std::less_equal<value_type>(), std::placeholders::_1, limit));
        const auto samples = std::count_if(get_threshold, let_threshold);
        return static_cast<value_type>(samples) / static_cast<value_type>(samplerate);
    }
}}} // namespace edsp::feature::temporal

#endif //EDSP_DURATION_HPP
