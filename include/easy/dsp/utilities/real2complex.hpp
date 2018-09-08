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
 * Filename: real2complex.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/9/2018
 */
#ifndef EASYDSP_REAL2COMPLEX_HPP
#define EASYDSP_REAL2COMPLEX_HPP

#include <complex>
#include <algorithm>
#include <easy/meta/type_traits.hpp>

namespace easy { namespace dsp {

    template <typename T>
    constexpr std::complex<T> real2complex(T real) noexcept {
        return std::complex<T>(real, 0);
    }

    template <typename T>
    constexpr std::complex<T> real2complex(T real, T imag) noexcept {
        return std::complex<T>(real, imag);
    }

    template <typename InputIterator, typename ComplexIterator>
    constexpr void real2complex(InputIterator first, InputIterator last, ComplexIterator out) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        std::transform(first, last, out, real2complex<value_type>);
    };

    template <typename InputIterator, typename ComplexIterator>
    constexpr void real2complex(InputIterator first_1, InputIterator last_1, InputIterator first_2,
                                ComplexIterator out) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        std::transform(first_1, last_1, first_2, out, real2complex<value_type>);
    };

}} // namespace easy::dsp

#endif // EASDY_REAL2COMPLEX_HPP
