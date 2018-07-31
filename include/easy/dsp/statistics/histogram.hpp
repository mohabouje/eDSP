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
 * Filename: histogram.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EASYDSP_FISHER_HISTOGRAM_HPP
#define EASYDSP_FISHER_HISTOGRAM_HPP

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/density.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <vector>

namespace easy { namespace dsp { namespace statistics {

    template <typename T, typename Allocator = std::allocator<std::pair<T,T>>>
    struct Histogram {
        using size_type = std::size_t;
        using value_type = T;
        inline Histogram(size_type num_bins, size_type cache_size) :
            num_bins_(num_bins),
            cache_size_(cache_size)
        { }

        template<typename InputIterator, typename OutputIterator>
        inline void compute(InputIterator first, InputIterator last, OutputIterator out) {
            acc accumulator_(boost::accumulators::tag::density::num_bins = num_bins_,
                             boost::accumulators::tag::density::cache_size = cache_size_);
            std::for_each(first, last, std::bind<void>( std::ref(accumulator_), std::placeholders::_1));
            const histogram_type histogram = boost::accumulators::density(accumulator_);
            std::copy(std::cbegin(histogram), std::cend(histogram), out);
        }

    private:
        using density = boost::accumulators::tag::density;
        using feature = boost::accumulators::features<density>;
        using acc = boost::accumulators::accumulator_set<T, feature>;
        using histogram_type = boost::iterator_range<typename std::vector<std::pair<T, T>, Allocator>::iterator>;
        size_type num_bins_;
        size_type cache_size_;
    };


}}}

#endif // EASYDSP_FISHER_HISTOGRAM_HPP
