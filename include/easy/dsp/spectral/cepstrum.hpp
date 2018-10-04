/*
* EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: cepstrum.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_CEPSTRUM_HPP
#define EASYDSP_CEPSTRUM_HPP

#include <easy/dsp/spectral/internal/fftw_impl.hpp>
#include <vector>

namespace easy { namespace dsp { inline namespace spectral {

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
    template <typename InputIt, typename OutputIt,
              typename Allocator = std::allocator<std::complex<meta::value_type_t<OutputIt>>>>
    inline void cepstrum(InputIt first, InputIt last, OutputIt d_first) {
        meta::expects(std::distance(first, last) > 0, "Not expecting empty input");
        using value_type = meta::value_type_t<InputIt>;
        fftw_plan<value_type> fft_{};
        fftw_plan<value_type> ifft_{};
        const auto size = std::distance(first, last);
        std::vector<std::complex<value_type>, Allocator> fft_data_(make_fft_size(size), std::complex<value_type>(0, 0));
        fft_.dft(fftw_cast(&(*first)), fftw_cast(meta::data(fft_data_)), size);

        std::transform(std::cbegin(fft_data_), std::cend(fft_data_), std::begin(fft_data_),
                       [](std::complex<value_type> value) -> std::complex<value_type> {
                           return std::complex<value_type>(2 * std::log(std::abs(value)), 0);
                       });

        ifft_.idft(fftw_cast(meta::data(fft_data_)), fftw_cast(&(*d_first)), size);
        ifft_.idft_scale(fftw_cast(&(*d_first)), size);
    }

}}} // namespace easy::dsp::spectral

#endif // EASYDSP_CEPSTRUM_HPP
