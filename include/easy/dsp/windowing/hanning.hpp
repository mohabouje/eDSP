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
 * Filename: hanning.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_HANNING_HPP
#define EASYDSP_HANNING_HPP

#include <easy/dsp/math/math.hpp>
#include <easy/meta/iterator.hpp>
#include <cmath>

namespace easy { namespace dsp { namespace windowing {

    /**
     * @brief Computes a Hann window of length N and stores the result in the range, beginning at d_first.
     *
     * Hann windows are defined as:
     *
     * \f[
     *  {\displaystyle w(n)=a_{0}-\underbrace {(1-a_{0})} _{a_{1}}\cdot \cos \left({\frac {2\pi n}{N-1}}\right),\quad 0\leq n\leq N-1,}
     * \f]
     *
     * where: \f$ a_{0}=0.5;\quad a_{1}=0.5 \f$
     *
     * @param N Number of elements to compute.
     * @param d_first Output irerator defining the beginning of the destination range.
     */
    template <typename OutIterator, typename Integer>
    constexpr void hanning(OutIterator d_first, Integer N) {
        using value_type  = meta::value_type_t<OutIterator>;
        using size_type   = diff_type_t<OutIterator>;
        constexpr auto a0 = static_cast<value_type>(0.5);
        constexpr auto a1 = static_cast<value_type>(0.5);
        const auto size   = static_cast<size_type>(N);
        const auto factor = constants<value_type>::two_pi / static_cast<value_type>(size - 1);
        for (size_type i = 0; i < size; ++i, ++d_first) {
            const value_type tmp = factor * i;
            *d_first             = a0 - a1 * std::cos(tmp);
        }
    }

}}}    // namespace easy::dsp::windowing
#endif // EASYDSP_HANNING_HPP
