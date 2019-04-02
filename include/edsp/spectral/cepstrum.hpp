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
 * File: cepstrum.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EDSP_CEPSTRUM_HPP
#define EDSP_CEPSTRUM_HPP

#include <edsp/spectral/fft_engine.hpp>
#include <vector>

namespace edsp { inline namespace spectral {

    /**
     * @brief Computes the cepstrum of the range [first, last) and stores the result in another range, beginning at d_first.
     *
     * The Cepstrum is the result of taking the inverse Fourier transform (IDFT) of the logarithm of the estimated spectrum of a signal:
     *
     * \f[
     * {\displaystyle C_K =\left|{\mathcal {F}}^{-1}\left\{\log \left(\left|{\mathcal {F}}\{f(t)\}\right|^{2}\right)\right\}\right|^{2}}
     * \f]
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename InputIt, typename OutputIt, typename RAllocator = std::allocator<meta::value_type_t<InputIt>>,
              typename CAllocator = std::allocator<std::complex<meta::value_type_t<OutputIt>>>>
    inline void cepstrum(InputIt first, InputIt last, OutputIt d_first) {
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

        std::transform(std::cbegin(fft_data_), std::cend(fft_data_), std::begin(fft_data_),
                       [](const std::complex<value_type>& val) -> std::complex<value_type> {
                           return std::complex<value_type>(std::log(std::abs(val)), 0);
                       });

        ifft_.idft(meta::data(fft_data_), meta::data(temp_output));
        ifft_.idft_scale(meta::data(temp_output));
        std::copy(std::cbegin(temp_output), std::cbegin(temp_output) + size, d_first);
    }

}} // namespace edsp::spectral

#endif // EDSP_CEPSTRUM_HPP
