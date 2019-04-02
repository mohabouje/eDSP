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
 * File: blackman.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EDSP_BLACKMAN_HPP
#define EDSP_BLACKMAN_HPP

#include <edsp/math/numeric.hpp>
#include <edsp/math/constant.hpp>
#include <edsp/meta/iterator.hpp>
#include <cmath>

namespace edsp { namespace windowing {

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
     * @param first Input iterator defining the beginning of the output range.
     * @param last Input iterator defining the ending of the output range.
     */
    template <typename OutputIt>
    constexpr void blackman(OutputIt first, OutputIt last) {
        using value_type  = meta::value_type_t<OutputIt>;
        using size_type   = meta::diff_type_t<OutputIt>;
        constexpr auto a0 = static_cast<value_type>(0.42);
        constexpr auto a1 = static_cast<value_type>(0.50);
        constexpr auto a2 = static_cast<value_type>(0.08);
        const auto size   = static_cast<size_type>(std::distance(first, last));
        const auto factor = constants<value_type>::two_pi / static_cast<value_type>(size - 1);
        for (size_type i = 0; i < size; ++i, ++first) {
            const value_type tmp = factor * i;
            *first               = a0 - a1 * std::cos(tmp) + a2 * std::cos(2 * tmp);
        }
    }

}} // namespace edsp::windowing

#endif // EDSP_BLACKMAN_HPP
