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
#ifndef EASYDSP_HARTLEY_HPP
#define EASYDSP_HARTLEY_HPP

#include <easy/dsp/transform/internal/fftw_impl.hpp>
#include <easy/dsp/math/complex.hpp>
#include <easy/meta/data.hpp>

namespace easy { namespace dsp {

    template <typename InputIterator, typename OutputIterator,
              typename value_type = typename std::iterator_traits<InputIterator>::value_type,
              typename Allocator  = std::allocator<std::complex<value_type>>>
    inline void hartley(InputIterator first, InputIterator last, OutputIterator out) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        const auto nfft  = static_cast<typename fftw_plan<value_type>::size_type>(std::distance(first, last));
        std::vector<std::complex<value_type>> complex_data(nfft / 2 + 1);
        fftw_plan<value_type> plan;
        plan.dft(fftw_cast(&(*first)), fftw_cast(meta::data(complex_data)), nfft);
        std::transform(
            std::cbegin(complex_data), std::cend(complex_data), out,
            [](const std::complex<value_type>& value) -> value_type { return meta::real(value) - meta::imag(value); });
    }

    template <typename Container>
    inline void hartley(const Container& input, Container& output) {
        hartley(std::cbegin(input), std::cend(input), std::begin(output));
    }

}} // namespace easy::dsp

#endif // EASYDSP_HARTLEY_HPP
