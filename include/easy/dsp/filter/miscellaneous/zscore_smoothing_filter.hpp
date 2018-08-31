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
 * Filename: smoothed_zscore_filter.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EASYDSP_SMOOTHED_ZSCORE_FILTER_HPP
#define EASYDSP_SMOOTHED_ZSCORE_FILTER_HPP

#include <easy/meta/expects.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/rolling_variance.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <boost/circular_buffer.hpp>

namespace easy { namespace dsp { namespace filter {

    template <typename T>
    class ZScoreSmoothingFilter {
    public:
        using size_type  = std::size_t;
        using value_type = T;

        inline explicit ZScoreSmoothingFilter(size_type window_size, value_type threshold, value_type influence) :
            window_size_(window_size),
            threshold_(threshold),
            influence_(influence),
            previous_(0),
            rolling_mean_(boost::accumulators::tag::rolling_window::window_size = window_size),
            rolling_variance_(boost::accumulators::tag::rolling_window::window_size = window_size) {}

        inline size_type windowSize() const {
            return window_size_;
        }

        inline void setWindowSize(size_type window_size) {
            meta::expects(window_size > 0, "Window size should be a positive number");
            window_size_ = window_size;
            reset();
        }

        inline value_type threshold() const noexcept {
            return threshold_;
        }

        inline void setThreshold(value_type threshold) noexcept {
            threshold_ = threshold;
        }

        inline value_type influence() const noexcept {
            return influence_;
        }

        inline void setInfluence(value_type influence) {
            meta::expects(influence >= 0 && influence <= 1, "Expected a influence in the range [0, 1]");
            influence_ = influence;
        }

        inline void reset() {
            previous_        = 0;
            rollin_mean_     = maf(boost::accumulators::tag::rolling_window::window_size = window_size_);
            rollin_variance_ = mvf(boost::accumulators::tag::rolling_window::window_size = window_size_);
        }

        template <typename BiIterator>
        inline void apply(BiIterator first, BiIterator last);

        template <typename InputIterator, typename OutputIterator>
        inline void apply(InputIterator first, InputIterator last, OutputIterator out);

        inline value_type operator()(value_type tick) {
            const auto mean_window           = boost::accumulators::rolling_mean(rolling_mean_);
            const auto std_window            = std::sqrt(boost::accumulators::rolling_variance(rolling_variance_));
            const auto output                = (std::abs(tick - mean_window) > threshold_ * std_window)
                                    ? output = influence_ * tick + (1 - influence_) * previous_
                                    : tick;
            previous_ = tick;
            rolling_mean_(tick);
            rolling_variance_(tick);
            return output;
        }

    private:
        using maf =
            boost::accumulators::accumulator_set<value_type,
                                                 boost::accumulators::stats<boost::accumulators::tag::rolling_mean>>;
        using mvf = boost::accumulators::accumulator_set<
            value_type, boost::accumulators::stats<boost::accumulators::tag::rolling_variance>>;

        using buf = boost::circular_buffer<value_type>;
        size_type window_size_;
        value_type threshold_;
        value_type influence_;
        value_type previous_;
        maf rolling_mean_{};
        mvf rolling_variance_{};
    };

}}} // namespace easy::dsp::filter

#endif // EASYDSP_SMOOTHED_ZSCORE_FILTER_HPP
