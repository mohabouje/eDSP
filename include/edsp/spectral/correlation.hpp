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
 * File: correlation.hpp
 * Date: 10/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_AUTOCORRELATION_HPP
#define EDSP_AUTOCORRELATION_HPP

#include <edsp/spectral/fft_engine.hpp>
#include <vector>

namespace edsp { inline namespace spectral {

    /**
    * @brief The ScaleOpt enum defines the normalization option of the correlation function.
    */
    enum class CorrelationScale {
        None,    /*!< Raw, unscaled cross-correlation. */
        Biased,  /*!< Biased estimate of the cross-correlation. */
        Unbiased /*!< Unbiased estimate of the cross-correlation. */
    };

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
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @param scale Scale factor to use.
     */
    template <typename InputIt, typename OutputIt, typename RAllocator = std::allocator<meta::value_type_t<InputIt>>,
              typename CAllocator = std::allocator<std::complex<meta::value_type_t<OutputIt>>>>
    inline void xcorr(InputIt first, InputIt last, OutputIt d_first, CorrelationScale scale = CorrelationScale::None) {
        meta::expects(std::distance(first, last) > 0, "Not expecting empty input");
        using value_type = meta::value_type_t<InputIt>;
        const auto size  = std::distance(first, last);
        const auto nfft  = 2 * size;
        fft_engine<value_type> fft_(nfft);
        fft_engine<value_type> ifft_(nfft);

        std::vector<value_type, RAllocator> temp_input(nfft, static_cast<value_type>(0)), temp_output(nfft);
        std::copy(first, last, std::begin(temp_input));

        std::vector<std::complex<value_type>, CAllocator> fft_data_(make_fft_size(nfft));
        fft_.dft(meta::data(temp_input), meta::data(fft_data_));

        std::transform(
            std::cbegin(fft_data_), std::cend(fft_data_), std::begin(fft_data_),
            [](const std::complex<value_type>& val) -> std::complex<value_type> { return val * std::conj(val); });

        ifft_.idft(meta::data(fft_data_), meta::data(temp_output));
        const auto factor = static_cast<value_type>(nfft * (scale == CorrelationScale::Biased ? nfft : 1));
        std::transform(std::cbegin(temp_output), std::cbegin(temp_output) + size, d_first,
                       [factor](value_type val) { return val / factor; });
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
     * @param first1 Input iterator defining the beginning of the first input range.
     * @param last1 Input iterator defining the ending of the first input range.
     * @param first2 Input iterator defining the beginning of the second input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @param scale Scale factor to use.
     */
    template <typename InputIt, typename OutputIt, typename RAllocator = std::allocator<meta::value_type_t<InputIt>>,
              typename CAllocator = std::allocator<std::complex<meta::value_type_t<OutputIt>>>>
    inline void xcorr(InputIt first1, InputIt last1, InputIt first2, OutputIt d_first,
                      CorrelationScale scale = CorrelationScale::None) {
        meta::expects(std::distance(first1, last1) > 0, "Not expecting empty input");
        using value_type = meta::value_type_t<InputIt>;
        const auto size  = std::distance(first1, last1);
        const auto nfft  = 2 * size;
        fft_engine<value_type> fft_(nfft);
        fft_engine<value_type> ifft_(nfft);

        std::vector<value_type, RAllocator> temp_input1(nfft, static_cast<value_type>(0)),
            temp_input2(nfft, static_cast<value_type>(0)), temp_output(nfft);
        std::copy(first1, last1, std::begin(temp_input1));
        std::copy(first2, meta::advance(first2, size), std::begin(temp_input2));

        std::vector<std::complex<value_type>, CAllocator> fft_data1(make_fft_size(nfft));
        std::vector<std::complex<value_type>, CAllocator> fft_data2(make_fft_size(nfft));

        fft_.dft(meta::data(temp_input1), meta::data(fft_data1));
        fft_.dft(meta::data(temp_input2), meta::data(fft_data2));

        std::transform(std::cbegin(fft_data1), std::cend(fft_data1), std::cbegin(fft_data2), std::begin(fft_data1),
                       [](const std::complex<value_type>& left, const std::complex<value_type>& right)
                           -> std::complex<value_type> { return left * std::conj(right); });

        ifft_.idft(meta::data(fft_data1), meta::data(temp_output));
        const auto factor = static_cast<value_type>(nfft * (scale == CorrelationScale::Biased ? nfft : 1));
        std::transform(std::cbegin(temp_output), std::cbegin(temp_output) + size, d_first,
                       [factor](value_type val) { return val / factor; });
    }

}}     // namespace edsp::spectral
#endif // EDSP_AUTOCORRELATION_HPP
