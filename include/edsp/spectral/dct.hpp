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
 * File: dct.hpp
 * Date: 10/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_DCT_HPP
#define EDSP_DCT_HPP

#include <edsp/spectral/fft_engine.hpp>

namespace edsp { inline namespace spectral {

    /**
     * @brief Computes the Discrete-Cosine-Transform of the range [first, last) and stores the result in another range,
     * beginning at d_first.
     *
     * The DCT-II is computed as follows:
     * \f[
     * {\displaystyle X_{k}=\sum _{n=0}^{N-1}{x_{n}\cos \left[{\frac {\pi }{N}}\left(n+{\frac {1}{2}}\right)k\right]}}
     * \f]
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename InputIt, typename OutputIt>
    inline void dct(InputIt first, InputIt last, OutputIt d_first) {
        const auto nfft =
            static_cast<typename fft_engine<meta::value_type_t<InputIt>>::size_type>(std::distance(first, last));
        fft_engine<meta::value_type_t<InputIt>> plan(nfft);
        plan.dct(&(*first), &(*d_first));
    }

    /**
     * @brief Computes the Inverse-Discrete-Cosine-Transform of the range [first, last) and stores the result in another range,
     * beginning at d_first.
     *
     * The IDCT-II is computed as follows:
     *
     * \f[
     * {\displaystyle X_{k}={\frac {1}{2}}x_{0}+\sum _{n=1}^{N-1}{x_{n}\cos \left[{\frac {\pi }{N}}n\left(k+{\frac {1}{2}}\right)\right]}}
     * \f]
     *
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename InputIt, typename OutputIt>
    inline void idct(InputIt first, InputIt last, OutputIt d_first) {
        const auto nfft =
            static_cast<typename fft_engine<meta::value_type_t<InputIt>>::size_type>(std::distance(first, last));
        fft_engine<meta::value_type_t<InputIt>> plan(nfft);
        plan.idct(&(*first), &(*d_first));
        plan.idct_scale(&(*d_first));
    }

}} // namespace edsp::spectral

#endif // EDSP_DCT_HPP
