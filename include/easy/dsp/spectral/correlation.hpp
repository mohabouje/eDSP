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
 * Filename: correlation.hpp
 * Created at: 10/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_AUTOCORRELATION_HPP
#define EASYDSP_AUTOCORRELATION_HPP

#include <easy/dsp/spectral/internal/fftw_impl.hpp>
#include <easy/meta/expects.hpp>
#include <easy/meta/advance.hpp>
#include <easy/meta/iterator.hpp>
#include <vector>
#include <algorithm>

namespace easy { namespace dsp { inline namespace spectral {


    /**
     * @brief Computes the autocorrelation of the range [first, last) and stores the result in another range, beginning at d_first.
     *
     * The result of xcorr can be interpreted as an estimate of the correlation between two random sequences or as the deterministic
     * correlation between two deterministic signals.
     *
     * \f[
     *
     *  R_{xx}(k) = \sum_{n=-\infty}^{\infty} x(n)x(n-k)
     *
     * \f]
     *
     * @param first Input iterator defining the beginnning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output irerator defining the beginning of the destination range.
     * @param scale Scale factor to use.
     */
    template <typename InputIt, typename OutputIt, typename Allocator = std::allocator<std::complex<value_type_t<OutputIt>>>>
    inline void xcorr(InputIt first, InputIt last, OutputIt d_first, CorrelationScale scale = CorrelationScale::None) {
        meta::expects(std::distance(first, last) > 0, "Not expecting empty input");
        using value_type = value_type_t<InputIt>;
        fftw_plan<value_type> fft_{};
        fftw_plan<value_type> ifft_{};
        const auto size = std::distance(first, last);
        std::vector<std::complex<value_type>, Allocator> fft_data_(make_fft_size(size), std::complex<value_type>(0, 0));
        fft_.dft(fftw_cast(&(*first)), fftw_cast(meta::data(fft_data_)), size);

        std::transform(std::cbegin(fft_data_), std::cend(fft_data_), std::begin(fft_data_),
                     [](const std::complex<value_type>& val) -> std::complex<value_type> {
                         const auto tmp = std::abs(val);
                         return {tmp * tmp, 0};
        });

        ifft_.idft(fftw_cast(meta::data(fft_data_)), fftw_cast(&(*d_first)), size);
        const auto factor = static_cast<value_type>(size * (scale == CorrelationScale::Biased ? size : 1));
        std::transform(d_first, meta::advance(d_first, size), d_first, [factor](value_type val) { return val / factor; });
    }

    /**
     * @brief Computes the correlation between the range [first1, last1) and the [first2, last2), and stores the result in another range,
     * beginning at d_first.
     *
     * The result of xcorr can be interpreted as an estimate of the correlation between two random sequences or as the deterministic
     * correlation between two deterministic signals.
     *
     * \f[
     *
     *  R_{x_1 x_2}(k) = \sum_{n=-\infty}^{\infty} x_1(n)x_2(n-k)
     *
     * \f]
     *
     * @param first1 Input iterator defining the beginnning of the first input range.
     * @param last1 Input iterator defining the ending of the first input range.
     * @param first2 Input iterator defining the beginnning of the second input range.
     * @param d_first Output irerator defining the beginning of the destination range.
     * @param scale Scale factor to use.
     */
    template <typename InputIt, typename OutputIt, typename Allocator = std::allocator<std::complex<value_type_t<OutputIt>>>>
    inline void xcorr(InputIt first1, InputIt last1, InputIt first2, OutputIt d_first, CorrelationScale scale = CorrelationScale::None) {
        meta::expects(std::distance(first1, last1) > 0, "Not expecting empty input");
        using value_type = value_type_t<InputIt>;
        fftw_plan<value_type> fft_{};
        fftw_plan<value_type> ifft_{};
        const auto size = std::distance(first1, last1);
        std::vector<std::complex<value_type>, Allocator> left_data_(make_fft_size(size), std::complex<value_type>(0, 0));
        std::vector<std::complex<value_type>, Allocator> right_data_(make_fft_size(size), std::complex<value_type>(0, 0));

        fft_.dft(fftw_cast(&(*first1)), fftw_cast(meta::data(left_data_)), size);
        fft_.dft(fftw_cast(&(*first2)), fftw_cast(meta::data(right_data_)), size);

        std::transform(std::cbegin(left_data_), std::cend(left_data_), std::cbegin(right_data_), std::begin(left_data_),
                     [](const std::complex<value_type>& left, const std::complex<value_type>& right) -> std::complex<value_type> {
                         return left * std::conj(right);;
        });

        ifft_.idft(fftw_cast(meta::data(left_data_)), fftw_cast(&(*d_first)), size);
        const auto factor = static_cast<value_type>(size * (scale == CorrelationScale::Biased ? size : 1));
        std::transform(d_first, meta::advance(d_first, size), d_first, [factor](value_type val) { return val / factor; });
    }

}}}     // namespace easy::dsp
#endif // EASYDSP_AUTOCORRELATION_HPP
