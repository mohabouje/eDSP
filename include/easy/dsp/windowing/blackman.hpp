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
 * Filename: blackman.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_BLACKMAN_HPP
#define EASYDSP_BLACKMAN_HPP

#include <easy/dsp/math/math.hpp>
#include <easy/dsp/math/constant.hpp>
#include <easy/meta/iterator.hpp>
#include <cmath>

namespace easy { namespace dsp { namespace windowing {

    /**
     * @brief Computes a Blackman window of length N and stores the result in the range, beginning at d_first.
     *
     * Blackman windows are defined as:
     *
     * \f[
     * w(n)=a_{0}-a_{1}\cos \left({\frac {2\pi n}{N-1}}\right)+a_{2}\cos \left({\frac {4\pi n}{N-1}}\right)-a_{3}\cos \left({\frac {6\pi n}{N-1}}\right)
     * \f]
     *
     * where: \f$ a_{0}=0.42;\quad a_{1}=0.5;\quad a_{2}=0.08;\quad a_{3}=0\, \f$
     *
     * @param N Number of elements to compute.
     * @param d_first Output irerator defining the beginning of the destination range.
     */
    template <typename OutIterator, typename Integer>
    constexpr void blackman(OutIterator d_first, Integer N) {
        using value_type = value_type_t<OutIterator>;
        using size_type = diff_type_t<OutIterator>;
        constexpr auto a0 = static_cast<value_type>(0.42);
        constexpr auto a1 = static_cast<value_type>(0.50);
        constexpr auto a2 = static_cast<value_type>(0.08);
        const auto size   = static_cast<size_type>(N);
        const auto factor = constants<value_type>::two_pi / static_cast<value_type>(size - 1);
        for (size_type i = 0; i < size; ++i, ++d_first) {
            const value_type tmp = factor * i;
            *d_first     = a0 - a1 * std::cos(tmp) + a2 * std::cos(2 * tmp);
        }
    }


}}} // namespace easy::dsp::windowing

#endif // EASYDSP_BLACKMAN_HPP
