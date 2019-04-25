/*
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along width
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * File: moving_rms_filter.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EDSP_MOVING_RMS_FILTER_HPP
#define EDSP_MOVING_RMS_FILTER_HPP

#include <edsp/types/ring_buffer.hpp>
#include <cmath>

namespace edsp { namespace filter {

    /**
     * @class moving_rms
     * @brief This class implement a cumulative moving rms (rolling rms or running rms) filter.
     *
     * Given a series of numbers and a fixed subset size, the first element of the moving rms is obtained by taking
     * the root-mean-square of the initial fixed subset of the number series. Then the subset is modified by "shifting forward";
     * that is, excluding the first number of the series and including the next value in the subset.
     *
     * The filter implement a basic cumulative unweighted rms of the previous N data, where N is the length of the
     * moving window.
     *
     * \f[
     *  \lambda_i = \sqrt{ \frac{x_{n}^2 + x_{n-1}^2 + \cdots + x_{i-(N-2)}^2 + x_{i-(N-1)}^2}{N}}
     * \f]
     *
     * @tparam T  Type of element.
     * @tparam Allocator  Allocator type, defaults to std::allocator<T>.
     */
    template <typename T, typename Allocator = std::allocator<T>>
    class moving_rms {
    public:
        using size_type  = std::size_t;
        using value_type = T;

        /**
        *  @brief Creates a %moving_rms with a window of length N.
        *  @param N Length of the moving average window.
        */
        explicit moving_rms(size_type N);

        /**
        *  @brief Returns the size of the moving window.
        *  @returns Number of elements in the moving window.
        */
        size_type size() const;

        /**
        *  @brief Resizes the moving window to the specified number of elements.
        *  @param N Number of elements the moving window should contain.
        */
        void resize(size_type N);

        /**
        * @brief Reset the moving window to the original state.
        */
        void reset();

        /**
        * @brief Applies a moving average filter to the elements in the range [first, last) and stores the result
        * in another range, beginning at d_first.
        *
        * @param first Input iterator defining the beginning of the input range.
        * @param last Input iterator defining the ending of the input range.
        * @param d_first Output iterator defining the beginning of the destination range.
        */
        template <typename InputIt, typename OutputIt>
        void filter(InputIt first, InputIt last, OutputIt d_first);

        /**
         * @brief Applies a moving average filter to the single element
         * @return The output of the filter.
         */
        value_type operator()(value_type tick);

    private:
        edsp::ring_buffer<T, Allocator> window_;
        T accumulated_{0};
    };

    template <typename T, typename Allocator>
    moving_rms<T, Allocator>::moving_rms(size_type N) : window_(N, T()) {}

    template <typename T, typename Allocator>
    typename moving_rms<T, Allocator>::size_type moving_rms<T, Allocator>::size() const {
        return window_.capacity();
    }

    template <typename T, typename Allocator>
    void moving_rms<T, Allocator>::reset() {
        window_.clear();
    }

    template <typename T, typename Allocator>
    template <typename InputIt, typename OutputIt>
    void moving_rms<T, Allocator>::filter(InputIt first, InputIt last, OutputIt d_first) {
        std::transform(first, last, d_first, std::ref(*this));
    }

    template <typename T, typename Allocator>
    void moving_rms<T, Allocator>::resize(size_type N) {
        window_.resize(N);
    }

    template <typename T, typename Allocator>
    typename moving_rms<T, Allocator>::value_type moving_rms<T, Allocator>::operator()(value_type tick) {
        const auto sqr = tick * tick;
        accumulated_ -= window_.front();
        accumulated_ += sqr;
        window_.push_back(sqr);
        return std::sqrt(accumulated_ / static_cast<T>(window_.size()));
    }

}} // namespace edsp::filter

#endif // EDSP_MOVING_RMS_FILTER_HPP
