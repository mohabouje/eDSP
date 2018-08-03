/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi
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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: moving_median_filter.hpp
 * Author: Mohammed Boujemaoui
 * Date: 14/6/2018
 */
#ifndef EASYDSP_FILTER_MOVING_MEDIAN_FILTER_H
#define EASYDSP_FILTER_MOVING_MEDIAN_FILTER_H

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/circular_buffer.hpp>
#include <vector>

namespace easy { namespace dsp { namespace filter {

    template <typename T,
              typename Allocator = std::allocator<T>>
    class MovingMedianFilter {
    public:
        using size_type  = std::size_t;
        using value_type = T;

        inline explicit MovingMedianFilter(size_type windowSize);
        inline size_type windowSize() const;
        inline void setWindowSize(size_type windowSize);
        inline void reset();

        template <typename BiIterator>
        inline void apply(BiIterator first, BiIterator last);

        template <typename InputIterator, typename OutputIterator>
        inline void apply(InputIterator first, InputIterator last, OutputIterator out);

        inline value_type operator()(value_type tick);

    private:
        using mmf =
            boost::accumulators::accumulator_set<value_type,
                                                 boost::accumulators::features<boost::accumulators::tag::median>>;
        using buf = boost::circular_buffer<value_type, Allocator>;
        buf buffer_{};
        mmf acc_{};
    };

    template <typename T>
    inline MovingMedianFilter<T>::MovingMedianFilter(size_type window_size) : buffer_(window_size), acc_() {}

    template <typename T>
    inline typename MovingMedianFilter<T>::size_type MovingMedianFilter<T>::windowSize() const {
        return buffer_.capacity();
    }

    template <typename T>
    inline void MovingMedianFilter<T>::setWindowSize(size_type window_size) {
        buffer_ = buf(window_size);
    }

    template <typename T>
    inline void MovingMedianFilter<T>::reset() {
        buffer_.clear();
    }

    template <typename T>
    inline typename MovingMedianFilter<T>::value_type MovingMedianFilter<T>::operator()(value_type tick) {
        buffer_.push_back(tick);
        acc_ = std::for_each(std::cbegin(buffer_), std::cend(buffer_), acc_);
        return boost::accumulators::median(acc_);
    }

    template <typename T>
    template <typename BiIterator>
    inline void MovingMedianFilter<T>::apply(BiIterator first, BiIterator last) {
        apply(first, last, first);
    }

    template <typename T>
    template <typename InputIterator, typename OutputIterator>
    inline void MovingMedianFilter<T>::apply(InputIterator first, InputIterator last, OutputIterator out) {
        static_assert(std::is_same<typename std::iterator_traits<InputIterator>::value_type, value_type>::value &&
                          std::is_same<typename std::iterator_traits<OutputIterator>::value_type, value_type>::value,
                      "Iterator does not math the value type. No implicit conversion is allowed");
        std::transform(first, last, out, std::ref(*this));
    }

}}} // namespace easy::dsp::filter

#endif // EASYDSP_FILTER_MOVING_MEDIAN_FILTER_H
