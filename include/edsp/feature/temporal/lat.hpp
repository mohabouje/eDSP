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
 * File: lat.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_LAT_HPP
#define EDSP_LAT_HPP

#include <algorithm>
#include <functional>
#include <cmath>

namespace edsp { namespace feature { inline namespace temporal {

    /**
     * @brief Estimates the logarithmic attack time of an envelope signal.
     *
     * The log-attack time is the logarithmic (decimal base) of the time duration between the time
     * the signal to the time it reaches its stable part:
     *
     * \f[
     *
     *  lat = \log10 \left( t_{stop} - t_{start} \right)
     *
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param sample_rate Sampling frequency in Hz.
     * @param start_threshold Numeric value between [0, 1] representing the percentage of the amplitude signal representing
     * the start of the attack time.
     * @param stop_threshold Numeric value between [0, 1] representing the percentage of the amplitude signal representing
     * the limit of the attack time.
     * @return Estimated attack time in seconds.
     */
    template <typename ForwardIt, typename Numeric>
    constexpr auto lat(ForwardIt first, ForwardIt last, Numeric sample_rate, Numeric start_threshold,
                       Numeric stop_threshold) {
        using value_type               = typename std::iterator_traits<ForwardIt>::value_type;
        const auto max_value           = *std::max_element(first, last);
        const auto cutoff_start_attack = max_value * start_threshold;
        const auto cutoff_stop_attack  = max_value * stop_threshold;
        const auto start_iter          = std::find_if(
            first, last, std::bind(std::greater_equal<value_type>(), std::placeholders::_1, cutoff_start_attack));
        const auto stop_iter = std::find_if(
            first, last, std::bind(std::less_equal<value_type>(), std::placeholders::_1, cutoff_stop_attack));
        const auto start_attack = std::distance(first, start_iter);
        const auto stop_attack  = std::distance(first, stop_iter);
        const auto attack_time =
            static_cast<value_type>(stop_attack - start_attack) / static_cast<value_type>(sample_rate);
        constexpr auto threshold = static_cast<value_type>(10e-5);
        return (attack_time > threshold) ? static_cast<value_type>(std::log10(attack_time)) : -5;
    }
}}} // namespace edsp::feature::temporal

#endif //EDSP_LAT_HPP
