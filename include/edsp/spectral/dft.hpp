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
 * File: dft.hpp
 * Date: 09/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_DFT_HPP
#define EDSP_DFT_HPP

#include <edsp/spectral/fft_engine.hpp>

namespace edsp { inline namespace spectral {

    /**
     * @brief Computes the complex-to-complex Discrete-Fourier-Transform of the range [first, last)
     * and stores the result in another range, beginning at d_first.
     *
     * The DFT transforms  a sequence of \f$ N \f$ complex numbers \f$ x_n \f$ into another sequence of complex numbers \f$ X_k \f$:
     *
     * \f[
     * {\displaystyle {\begin{aligned}X_{k}&=\sum _{n=0}^{N-1}x_{n}\cdot e^{-{\frac {2\pi i}{N}}kn}\\&=\sum _{n=0}^{N-1}x_{n}\cdot [\cos(2\pi kn/N)-i\cdot \sin(2\pi kn/N)],\end{aligned}}}
     * \f]
     *
     * @tparam T Underlying type to perform the arithmetic operations (float, double or long double).
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @see complex_idft
     */
    template <typename InputIt, typename OutputIt>
    inline void cdft(InputIt first, InputIt last, OutputIt d_first) {
        using complex_t    = meta::value_type_t<InputIt>;
        using underlying_t = typename complex_t::value_type;
        const auto nfft    = std::distance(first, last);
        fft_engine<underlying_t> plan((typename fft_engine<underlying_t>::size_type) nfft);
        plan.dft(&(*first), &(*d_first));
    }

    /**
     * @brief Computes the complex-to-complex Inverse-Discrete-Fourier-Transform of the range [first, last)
     * and stores the result in another range, beginning at d_first.
     *
     * The IDFT transforms  a sequence of \f$ N \f$ complex numbers \f$ X_k \f$ into another sequence of complex numbers \f$ x_n \f$:
     *
     * \f[
     * {\displaystyle x_{n}={\frac {1}{N}}\sum _{k=0}^{N-1}X_{k}e^{{\frac {2\pi i}{N}}kn}\quad \quad n=0,\dots ,N-1.}
     * \f]
     * @tparam T Underlying type to perform the arithmetic operations (float, double or long double).
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @see complex_dft
     */
    template <typename InputIt, typename OutputIt>
    inline void cidft(InputIt first, InputIt last, OutputIt d_first) {
        using complex_t    = meta::value_type_t<InputIt>;
        using underlying_t = typename complex_t::value_type;
        const auto nfft    = std::distance(first, last);
        fft_engine<underlying_t> plan((typename fft_engine<underlying_t>::size_type) nfft);
        plan.idft(&(*first), &(*d_first));
        plan.idft_scale(&(*d_first));
    }

    /**
     * @brief Computes the real-to-complex Discrete-Fourier-Transform of the range [first, last) and stores the result in another range,
     *  beginning at d_first.
     *
     * When the input data are purely real number, the DFT output satisfies the “Hermitian” redundancy:
     * \f$ F(i) \f$ is the conjugate of  \f$ F(N - i) \f$, where \f$ N \f$ is the size of the DFT. To benefit from this property (speed and space advantages), the input and output arrays are of different sizes and types: the input is \f$ N \f$ real numbers,
     * while the output is \f$ \frac{N}{2} + 1 \f$ complex numbers (the non-redundant outputs) where the division is rounded down.
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @see make_fft_size
     */
    template <typename InputIt, typename OutputIt>
    void dft(InputIt first, InputIt last, OutputIt d_first) {
        using value_type = typename std::iterator_traits<InputIt>::value_type;
        const auto nfft  = std::distance(first, last);
        fft_engine<value_type> plan((typename fft_engine<value_type>::size_type) nfft);
        plan.dft(&(*first), &(*d_first));
    }

    /**
     * @brief Computes the complex-to-real Inverse-Discrete-Fourier-Transform of the complex range [first, last) and stores the result in another range,
     *  beginning at d_first.
     *
     * When the input data are purely real number, the DFT output satisfies the “Hermitian” redundancy:
     * \f$ F(i) \f$ is the conjugate of  \f$ F(N - i) \f$, where \f$ N \f$ is the size of the DFT. To benefit from this property (speed and space advantages), the input and output arrays are of different sizes and types: the input is \f$ N \f$ real numbers,
     * while the output is \f$ \frac{N}{2} + 1 \f$ complex numbers (the non-redundant outputs) where the division is rounded down.
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @see make_ifft_size
     */
    template <typename InputIt, typename OutputIt>
    void idft(InputIt first, InputIt last, OutputIt d_first) {
        using value_type = typename std::iterator_traits<OutputIt>::value_type;
        const auto nfft  = make_ifft_size(std::distance(first, last));
        fft_engine<value_type> plan((typename fft_engine<value_type>::size_type) nfft);
        plan.idft(&(*first), &(*d_first));
        plan.idft_scale(&(*d_first));
    }

}} // namespace edsp::spectral

#endif // EDSP_DFT_HPP
