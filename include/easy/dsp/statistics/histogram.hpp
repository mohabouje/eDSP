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

    /**
     * @brief %Histogram density estimator.
     *
     * The histogram density estimator returns a histogram of the sample distribution.
     * The positions and sizes of the bins are determined using a specifiable number of cached samples (cache_size).
     * The range between the minimum and the maximum of the cached samples is subdivided into a specifiable number
     *  of bins (num_bins) of same size.
     * @tparam T  Type of element.
     * @tparam Allocator  Allocator type, defaults to std::allocator<std::pair<T, T>>.
     */
    template <typename T, typename Allocator = std::allocator<std::pair<T, T>>>
    struct Histogram {
        using size_type      = std::size_t;
        using value_type     = T;

        /**
         * @brief Creates an %Histogram with the specified number of bins and cache size.
         * @param num_bins Number of bins.
         * @param cache_size Number of cached samples to determine the positions and sizes of the bins.
         */
        constexpr Histogram(size_type num_bins, size_type cache_size) : num_bins_(num_bins), cache_size_(cache_size) {}

        /**
         * @brief Computes the histogram of the range [first, last).
         *
         * Compute a range of std::pair, where each pair contains the position of the bin (lower bound)
         * and the samples count (normalized with the total number of samples).
         * @param first Input iterator defining the begin of the range to examine.
         * @param last Input iterator defining the end of the range to examine.
         * @param out Output iterator containing the pairs (bin/sample).
         */
        template <typename InIterator, typename OutIterator>
        constexpr void compute(InIterator first, InIterator last, OutIterator out) {
            acc accumulator_(boost::accumulators::tag::density::num_bins   = num_bins_,
                             boost::accumulators::tag::density::cache_size = cache_size_);
            std::for_each(first, last, std::bind<void>(std::ref(accumulator_), std::placeholders::_1));
            const histogram_type histogram = boost::accumulators::density(accumulator_);
            std::copy(std::cbegin(histogram), std::cend(histogram), out);
        }

    private:
        using density        = boost::accumulators::tag::density;
        using feature        = boost::accumulators::features<density>;
        using acc            = boost::accumulators::accumulator_set<T, feature>;
        using histogram_type = boost::iterator_range<typename std::vector<std::pair<T, T>, Allocator>::iterator>;
        size_type num_bins_;
        size_type cache_size_;
    };

    /**
     * @brief Computes the histogram of the range [first, last)
     *
     * @param first Input iterator defining the begin of the range to examine.
     * @param last Input iterator defining the end of the range to examine.
     * @param num_bins Number of bins.
     * @param cache_size Number of cached samples to determine the positions and sizes of the bins.
     * @param out Output iterator containing the pairs (bin/sample).
     * @see Histogram
     */
    template <typename InIterator, typename Integer, typename OutIterator>
    constexpr void histogram(InIterator first, InIterator last, Integer num_bins, Integer cache_size, OutIterator out) {
        auto histo = Histogram(num_bins, cache_size);
        histo.compute(first, last, out);
    }

}}} // namespace easy::dsp::statistics

#endif // EASYDSP_FISHER_HISTOGRAM_HPP
