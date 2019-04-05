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
 * File: leq.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_LEQ_HPP
#define EDSP_LEQ_HPP

#include <edsp/filter/moving_average_filter.hpp>
#include <edsp/feature/temporal/energy.hpp>
#include <edsp/converter/pow2db.hpp>

namespace edsp { namespace feature { inline namespace temporal {

    /**
     * @brief This algorithms computes the Equivalent sound level (Leq)  of the range [first, last)
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The Equivalent sound level (Leq)  of the input range.
     */
    template <typename ForwardIt>
    constexpr auto leq(ForwardIt first, ForwardIt last) {
        const auto e = power(first, last);
        return converter::pow2db(e);
    }

    /**
     * @class leq
     * @brief This class estimates the Equivalent Continuous Sound Level over consecutive frames
     *
     * Leq is the preferred method to describe sound levels that vary over time, resulting in a single decibel
     * value which takes into account the total sound energy over the period of time of interest
     */
    template <typename T>
    struct continuous_leq {
        using size_type  = std::size_t;
        using value_type = T;

        /**
         * @brief Creates a leq estimator.
         * @param number_frames Number of frames over time of interest to compute the equivalent sound level.
         */
        explicit continuous_leq(size_type number_frames) : filter(number_frames) {}

        /**
         * @brief Default destructor.
         */
        ~continuous_leq() = default;

        /**
         * @brief Estimates the equivalent sound level over time of the frame represented by the elements in the
         * range [first, last).
         *
         * @note Frames can have different lengths but it is preferable to keep consistency between consecutive frames.
         * @param first Forward iterator defining the begin of the range to examine.
         * @param last Forward iterator defining the end of the range to examine.
         * @return The estimated equivalent sound level in dB.
         */
        template <typename ForwardIt>
        value_type extract(ForwardIt first, ForwardIt last) {
            return filter(leq(first, last));
        }

    private:
        filter::moving_average<T> filter;
    };

}}} // namespace edsp::feature::temporal

#endif //EDSP_LEQ_HPP
