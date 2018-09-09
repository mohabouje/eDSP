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
 * Filename: hartley.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EASYDSP_HILBERT_HPP
#define EASYDSP_HILBERT_HPP

#include <easy/dsp/transform/internal/fftw_impl.hpp>
#include <easy/dsp/math/complex.hpp>
#include <easy/dsp/utilities/real2complex.hpp>
#include <easy/meta/data.hpp>
#include <easy/meta/advance.hpp>
#include <algorithm>
#include <vector>
#include <complex>

namespace easy { namespace dsp {

    // TODO: review https://stackoverflow.com/questions/39030463/computing-analytical-signal-using-fft-in-c
    template <typename InputIterator, typename OutputIterator>
    inline void hilbert(InputIterator first, InputIterator last, OutputIterator out) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        const auto nfft  = static_cast<typename fftw_plan<value_type>::size_type>(std::distance(first, last));

        std::vector<std::complex<value_type>> input_data(nfft);
        std::vector<std::complex<value_type>> complex_data(nfft);
        easy::dsp::real2complex(first, last, std::begin(input_data));

        fftw_plan<value_type> fft;
        fft.dft(fftw_cast(meta::data(input_data)), fftw_cast(meta::data(complex_data)), nfft);

        const auto limit_1 = math::is_even(nfft) ? nfft / 2 : (nfft + 1) / 2;
        const auto limit_2 = math::is_even(nfft) ? limit_1 + 1 : limit_1;
        for (auto i = 1; i < limit_1; ++i) {
            complex_data[i] *= 2;
        }

        for (auto i = limit_2; i < nfft; ++i) {
            complex_data[i] = std::complex<value_type>(0, 0);
        }

        fftw_plan<value_type> ifft;
        ifft.idft(fftw_cast(meta::data(complex_data)), fftw_cast(&(*out)), nfft);
        ifft.idft_scale(fftw_cast(&(*out)), nfft);
    }

    template <typename Container>
    inline void hilbert(const Container& input, Container& output) {
        hilbert(std::cbegin(input), std::cend(input), std::begin(output));
    }

}} // namespace easy::dsp

#endif // EASYDSP_HIRTLEY_HPP
