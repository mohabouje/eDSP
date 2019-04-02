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
 * File: hartley.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EDSP_HILBERT_HPP
#define EDSP_HILBERT_HPP

#include <edsp/spectral/fft_engine.hpp>
#include <edsp/converter/real2complex.hpp>
#include <edsp/math/numeric.hpp>
#include <vector>

namespace edsp { inline namespace spectral {

    /**
     * @brief Computes the Discrete-Time analytic signal using Hilbert transform of the range [first, last)
     * and stores the result in another range, beginning at d_first.
     *
     * The Discrete-time analytic is the complex helical sequence obtained from a real data sequence.
     * The analytic signal \f$ A_k = A_r + iA_i \f$ has a real part, \f$ A_r \f$, which is the original data,
     * and an imaginary part, \f$ A_i \f$, which contains the Hilbert transform. The imaginary part is a version of the original real sequence with a 90° phase shift.
     *
     * The Hilbert transform is computed as follows:
     * \f[
     * {\displaystyle {\widehat {s}}(t)={\mathcal {H}}\{s\}(t)=(h*s)(t)={\frac {1}{\pi }}\int _{-\infty }^{\infty }{\frac {s(\tau )}{t-\tau }}\,d\tau .\,}
     * \f]
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @see complex_idft
     */
    template <typename InputIt, typename OutputIt,
              typename Allocator = std::allocator<std::complex<meta::value_type_t<InputIt>>>>
    inline void hilbert(InputIt first, InputIt last, OutputIt d_first) {
        // TODO: add the static assertion, the input should be a complex array
        using value_type = meta::value_type_t<InputIt>;
        const auto nfft  = static_cast<typename fft_engine<value_type>::size_type>(std::distance(first, last));

        std::vector<std::complex<value_type>, Allocator> input_data(nfft);
        std::vector<std::complex<value_type>, Allocator> complex_data(nfft);
        edsp::real2complex(first, last, std::begin(input_data));

        fft_engine<value_type> fft(nfft);
        fft.dft(meta::data(input_data), meta::data(complex_data));

        const auto limit_1 = math::is_even(nfft) ? nfft / 2 : (nfft + 1) / 2;
        const auto limit_2 = math::is_even(nfft) ? limit_1 + 1 : limit_1;
        for (auto i = 1ul; i < limit_1; ++i) {
            complex_data[i] *= 2;
        }

        for (auto i = limit_2; i < nfft; ++i) {
            complex_data[i] = std::complex<value_type>(0, 0);
        }

        fft_engine<value_type> ifft(nfft);
        ifft.idft(meta::data(complex_data), &(*d_first));
        ifft.idft_scale(&(*d_first));
    }

}} // namespace edsp::spectral

#endif // EDSP_HIRTLEY_HPP
