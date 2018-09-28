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
 * Filename: convolution.hpp
 * Created at: 10/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_CONVOLUTION_HPP
#define EASYDSP_CONVOLUTION_HPP

#include <easy/dsp/spectral/internal/fftw_impl.hpp>
#include <easy/meta/iterator.hpp>
#include <easy/meta/expects.hpp>
#include <easy/meta/advance.hpp>
#include <algorithm>
#include <vector>

namespace easy { namespace dsp { inline namespace spectral {

    /**
     * @brief Computes the convolution between the range [first1, last1) and the range [first2, last2), and stores the result in another range,
     * beginning at d_first.
     *
     * The result of conv can be interpreted as an estimate of how the shape of one range is modified by the other. It is defined as:
     *
     * \f[
     *
     *  {\displaystyle (f*g)[n]=\sum _{m=-M}^{M}f[n-m]g[m].}
     *
     * \f]
     *
     * @param first1 Input iterator defining the beginnning of the first input range.
     * @param last1 Input iterator defining the ending of the first input range.
     * @param first2 Input iterator defining the beginnning of the second input range.
     * @param d_first Output irerator defining the beginning of the destination range.
     */
    template <typename InputIt, typename OutputIt, typename Allocator = std::allocator<std::complex<value_type_t<OutputIt>>>>
    inline void conv(InputIt first1, InputIt last1, InputIt first2, OutputIt d_first) {
        meta::expects(std::distance(first1, last1) > 0, "Not expecting empty input");
        using value_type = value_type_t<InputIt>;
        fftw_plan<value_type> fft_{};
        fftw_plan<value_type> ifft_{};
        const auto size = std::distance(first1, last1);
        std::vector<std::complex<value_type>, Allocator> left_data_(make_fft_size(size), std::complex<value_type>(0, 0));
        std::vector<std::complex<value_type>, Allocator> right_data_(make_fft_size(size), std::complex<value_type>(0, 0));

        fft_.dft(fftw_cast(&(*first1)), fftw_cast(meta::data(left_data_)), size);
        fft_.dft(fftw_cast(&(*first2)), fftw_cast(meta::data(right_data_)), size);

        std::transform(std::cbegin(left_data_), std::cend(left_data_), std::cbegin(right_data_),
                       std::begin(left_data_), std::multiplies<>());

        ifft_.idft(fftw_cast(meta::data(left_data_)), fftw_cast(&(*d_first)), size);
        ifft_.idft_scale(fftw_cast(&(*d_first)), size);
    }

}}} // namespace easy::dsp

#endif // EASYDSP_CONVOLUTION_HPP
