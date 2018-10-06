/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: boxcar.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/8/2018
 */
#ifndef EASYDSP_BOXCAR_HPP
#define EASYDSP_BOXCAR_HPP

#include <edsp/math/numeric.hpp>
#include <edsp/meta/iterator.hpp>

namespace edsp { namespace windowing {

    /**
     * @brief Computes a boxcar (rectangular) window of length N and stores the result in the range, beginning at d_first.
     *
     * Boxcar windows are defined as:
     *
     * \f[
     *  w(n)=1
     * \f]
     *
     * @param N Number of elements to compute.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename OutIterator, typename Integer>
    constexpr void boxcar(OutIterator d_first, Integer N) {
        using value_type = meta::value_type_t<OutIterator>;
        using size_type  = meta::diff_type_t<OutIterator>;
        const auto size  = static_cast<size_type>(N);
        for (size_type i = 0; i < size; ++i, ++d_first) {
            *d_first = static_cast<value_type>(1);
        }
    }

}} // namespace edsp::windowing

#endif // EASYDSP_BOXCAR_HPP
