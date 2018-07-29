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
 * Filename: dft.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_DFT_HPP
#define EASYDSP_DFT_HPP

#include <algorithm>
#include "fftw_impl.hpp"

namespace easy { namespace dsp {

    template <typename T, typename InputIterator, typename OutputIterator>
    inline void complex_dft(InputIterator first, InputIterator last, OutputIterator out) {
        fftw_plan<T> plan;
        plan.dft(fftw_cast(&(*first)), fftw_cast(&(*out)),
                 static_cast<typename fftw_plan<T>::size_type>(std::distance(first, last)));
    };

    template <typename T, typename Container>
    inline void complex_dft(const Container& input, Container& output) {
        complex_dft<T>(std::cbegin(input), std::cend(input), std::begin(output));
    };

    template <typename T, typename InputIterator, typename OutputIterator>
    inline void complex_idft(InputIterator first, InputIterator last, OutputIterator out) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        const auto nfft  = static_cast<typename fftw_plan<T>::size_type>(std::distance(first, last));
        fftw_plan<T> plan;
        plan.idft(fftw_cast(&(*first)), fftw_cast(&(*out)), nfft);
        std::transform(out, out + nfft, out, [nfft](value_type value) -> value_type {
            return value / static_cast<value_type>(nfft);
            ;
        });
    };

    template <typename T, typename Container>
    inline void complex_idft(const Container& input, Container& output) {
        complex_idft<T>(std::cbegin(input), std::cend(input), std::begin(output));
    };

    template <typename InputIterator, typename OutputIterator>
    void dft(InputIterator first, InputIterator last, OutputIterator out) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        fftw_plan<value_type> plan;
        plan.dft(fftw_cast(&(*first)), fftw_cast(&(*out)),
                 static_cast<typename fftw_plan<value_type>::size_type>(std::distance(first, last)));
    };

    template <typename RealContainer, typename ComplexContainer>
    void dft(const RealContainer& input, ComplexContainer& output) {
        dft(std::cbegin(input), std::cend(input), std::begin(output));
    };

    template <typename InputIterator, typename OutputIterator>
    void idft(InputIterator first, InputIterator last, OutputIterator out) {
        using value_type = typename std::iterator_traits<OutputIterator>::value_type;
        fftw_plan<value_type> plan;
        const auto nfft = static_cast<typename fftw_plan<value_type>::size_type>(std::distance(first, last));
        plan.idft(fftw_cast(&(*out)), fftw_cast(&(*first)), nfft);
        std::transform(out, out + nfft, out, [nfft](value_type value) { return value / nfft; });
    };

    template <typename RealContainer, typename ComplexContainer>
    void idft(const ComplexContainer& input, RealContainer& output) {
        idft(std::cbegin(input), std::cend(input), std::begin(output));
    };

}} // namespace easy::dsp

#endif // EASYDSP_DFT_HPP
