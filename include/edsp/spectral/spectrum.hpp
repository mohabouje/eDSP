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
 * File: spectrum.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EDSP_SPECTROGRAM_HPP
#define EDSP_SPECTROGRAM_HPP

#include <edsp/spectral/dft.hpp>
#include <edsp/converter/mag2db.hpp>
#include <edsp/math/numeric.hpp>
#include <vector>

namespace edsp { inline namespace spectral {

    /**
     * @brief Computes the spectrum of the range [first, last) and stores the result in another range, beginning at d_first.
     *
     * The spectrum is an estimate of the spectral density of a signal.
     *
     * \f[
     *
     *  {\displaystyle S\left({\tfrac {k}{NT}}\right)=\left|\sum _{n}x_{N}[n]\cdot e^{-i2\pi {\frac {kn}{N}}}\right|^{2}}
     *
     * \f]
     *
     * where T, is the inverse of the sample rate \f$ f_s \f$.
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @param scale  Scale to be used in the output
     */
    template <typename InputIt, typename OutputIt,
              typename Allocator = std::allocator<std::complex<meta::value_type_t<OutputIt>>>>
    inline void spectrum(InputIt first, InputIt last, OutputIt d_first) {
        meta::expects(std::distance(first, last) > 0, "Not expecting empty input");
        using value_type = meta::value_type_t<InputIt>;
        const auto size  = std::distance(first, last);
        std::vector<std::complex<value_type>, Allocator> fft_data_(make_fft_size(size));
        dft(first, last, std::begin(fft_data_));
        std::transform(std::cbegin(fft_data_), std::cend(fft_data_), d_first,
                       [](const auto val) { return math::square(std::abs(val)); });
    }

}} // namespace edsp::spectral

#endif // EDSP_SPECTROGRAM_HPP
