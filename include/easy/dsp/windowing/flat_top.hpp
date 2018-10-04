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
 * Filename: flat_top.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_FLAT_TOP_HPP
#define EASYDSP_FLAT_TOP_HPP

#include <easy/dsp/math/numeric.hpp>
#include <easy/dsp/math/constant.hpp>
#include <easy/meta/iterator.hpp>

namespace easy { namespace dsp { namespace windowing {

    /**
     * @brief Computes a Flat top window of length N and stores the result in the range, beginning at d_first.
     *
     * Flat top windows are defined as:
     *
     * \f[
     *  w(n)=a_{0}-a_{1}\cos \left({\frac {2\pi n}{N-1}}\right)+a_{2}\cos \left({\frac {4\pi n}{N-1}}\right)-a_{3}\cos \left({\frac {6\pi n}{N-1}}\right)+a_{4}\cos \left({\frac {8\pi n}{N-1}}\right)
     * \f]
     *
     * where: \f$ a_{0}=1;\quad a_{1}=1.93;\quad a_{2}=1.29;\quad a_{3}=0.388;\quad a_{4}=0.028\, \f$
     *
     * @param N Number of elements to compute.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename OutIterator, typename Integer>
    constexpr void flattop(OutIterator d_first, Integer N) {
        using value_type  = meta::value_type_t<OutIterator>;
        using size_type   = meta::diff_type_t<OutIterator>;
        constexpr auto a0 = static_cast<value_type>(0.21557895);
        constexpr auto a1 = static_cast<value_type>(0.41663158);
        constexpr auto a2 = static_cast<value_type>(0.277263158);
        constexpr auto a3 = static_cast<value_type>(0.083578947);
        constexpr auto a4 = static_cast<value_type>(0.006947368);
        const auto size   = static_cast<size_type>(N);
        const auto factor = constants<value_type>::two_pi / static_cast<value_type>(size - 1);
        for (size_type i = 0; i < size; ++i, ++d_first) {
            const value_type tmp = factor * i;
            *d_first =
                a0 - a1 * std::cos(tmp) + a2 * std::cos(2 * tmp) - a3 * std::cos(3 * tmp) + a4 * std::cos(4 * tmp);
        }
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_FLAT_TOP_HPP
