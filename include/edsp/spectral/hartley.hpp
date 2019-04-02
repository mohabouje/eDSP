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
 * Date: 09/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_HARTLEY_HPP
#define EDSP_HARTLEY_HPP

#include <edsp/spectral/fft_engine.hpp>

namespace edsp { inline namespace spectral {

    /**
     * @brief Computes the Discrete-Hartley-Transform of the range [first, last)
     * and stores the result in another range, beginning at d_first.
     *
     * The DHT transforms  a sequence of \f$ N \f$ real numbers \f$ x_n \f$ into another sequence of real numbers \f$ H_k \f$:
     *
     * \f[
        {\displaystyle H_{k}=\sum _{n=0}^{N-1}x_{n}\operatorname {cas} \left({\frac {2\pi }{N}}nk\right)=\sum _{n=0}^{N-1}x_{n}
        \left[\cos \left({\frac {2\pi }{N}}nk\right)+\sin \left({\frac {2\pi }{N}}nk\right)\right]\quad \quad k=0,\dots ,N-1}
     * \f]
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @see complex_idft
     */
    template <typename InputIt, typename OutputIt>
    inline void hartley(InputIt first, InputIt last, OutputIt d_first) {
        using value_type = meta::value_type_t<InputIt>;
        const auto nfft  = static_cast<typename fft_engine<value_type>::size_type>(std::distance(first, last));
        fft_engine<value_type> plan(nfft);
        plan.dht(&(*first), &(*d_first));
    }

}} // namespace edsp::spectral

#endif // EDSP_HARTLEY_HPP
