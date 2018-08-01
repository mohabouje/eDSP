/*
 * Easy Meet, Yet another header-only library for C++ meta-programming.
 * Copyright (C) 2018 Mohammed Boujemaoui
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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: complex.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-29
 */

#ifndef EASYMETA_COMPLEX_H
#define EASYMETA_COMPLEX_H

#include <complex>
#include <cmath>

namespace easy { namespace meta { inline namespace math {

    template <typename T>
    constexpr T magnitude(const std::complex<T>& value) {
        return static_cast<T>(std::abs(value));
    }

    template <typename T>
    constexpr T phase(const std::complex<T>& value) {
        return static_cast<T>(std::arg(value));
    }

    template <typename T>
    constexpr T real(const std::complex<T>& value) {
        return std::real(value);
    }

    template <typename T>
    constexpr T imag(const std::complex<T>& value) {
        return std::imag(value);
    }

}}} // namespace easy::meta::math

#endif