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
 * Filename: moving_rms_filter.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EASYDSP_MOVING_RMS_FILTER_HPP
#define EASYDSP_MOVING_RMS_FILTER_HPP

#include <easy/meta/math.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>

namespace easy { namespace dsp { namespace filter {

    template <typename T>
    class MovingRMSFilter {
    public:
        using size_type  = std::size_t;
        using value_type = T;

        explicit MovingRMSFilter(size_type windowSize);
        inline size_type windowSize() const;
        inline void setWindowSize(size_type windowSize);
        inline void reset();

        template <typename BiIterator>
        inline void apply(BiIterator first, BiIterator last);

        template <typename InputIterator, typename OutputIterator>
        inline void apply(InputIterator first, InputIterator last, OutputIterator out);

        inline value_type operator()(value_type tick);

    private:
        using maf =
            boost::accumulators::accumulator_set<value_type,
                                                 boost::accumulators::stats<boost::accumulators::tag::rolling_mean>>;
        size_type window_size_{3};
        maf acc_{boost::accumulators::tag::rolling_window::window_size = window_size_};
    };

    template <typename T>
    inline MovingRMSFilter<T>::MovingRMSFilter(size_type window_size) :
        window_size_(window_size),
        acc_(boost::accumulators::tag::rolling_window::window_size = window_size) {}

    template <typename T>
    inline typename MovingRMSFilter<T>::size_type MovingRMSFilter<T>::windowSize() const {
        return window_size_;
    }

    template <typename T>
    inline void MovingRMSFilter<T>::setWindowSize(size_type window_size) {
        window_size_ = window_size;
        reset();
    }

    template <typename T>
    inline void MovingRMSFilter<T>::reset() {
        acc_ = maf(boost::accumulators::tag::rolling_window::window_size = window_size_);
    }

    template <typename T>
    inline typename MovingRMSFilter<T>::value_type MovingRMSFilter<T>::operator()(value_type tick) {
        acc_(meta::square(tick));
        return std::sqrt(boost::accumulators::rolling_mean(acc_));
    }

    template <typename T>
    template <typename BiIterator>
    inline void MovingRMSFilter<T>::apply(BiIterator first, BiIterator last) {
        apply(first, last, first);
    }

    template <typename T>
    template <typename InputIterator, typename OutputIterator>
    inline void MovingRMSFilter<T>::apply(InputIterator first, InputIterator last, OutputIterator out) {
        static_assert(std::is_same<typename std::iterator_traits<InputIterator>::value_type, value_type>::value &&
                          std::is_same<typename std::iterator_traits<OutputIterator>::value_type, value_type>::value,
                      "Iterator does not math the value type. No implicit conversion is allowed");
        std::transform(first, last, out, std::ref(*this));
    }

}}} // namespace easy::dsp::filter

#endif // EASYDSP_MOVING_RMS_FILTER_HPP
