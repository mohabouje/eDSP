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
 * Filename: complex.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-29
 */

#ifndef EASYMETA_COMPLEX_H
#define EASYMETA_COMPLEX_H

#include <easy/meta/unused.hpp>
#include <easy/dsp/math/math.hpp>
#include <limits>
#include <complex>
#include <cmath>

namespace easy { inline namespace math {

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

    template <typename T>
    constexpr T conj(const std::complex<T>& value) {
        return std::conj(value);
    }

    template <typename T>
    constexpr T real(T value) {
        return value;
    }

    template <typename T>
    constexpr T imag(T value) {
        meta::unused(value);
        return 0;
    }

    template <typename T>
    constexpr T conj(T value) {
        return value;
    }

    template <typename T>
    constexpr auto is_nan(const std::complex<T>& value) noexcept {
        return is_nan(value.real()) || is_nan(value.imag());
    }

    template <typename T>
    constexpr auto is_inf(const std::complex<T>& value) noexcept {
        return is_inf(value.real()) || is_inf(value.imag());
    }

    template <typename T>
    constexpr std::complex<T> addmul(const std::complex<T>& left, const T factor,
                                     const std::complex<T>& right) noexcept {
        return std::complex<T>(left.real() + factor * right.real(), left.imag() + factor * right.imag());
    }

    template <typename T>
    constexpr std::complex<T> infinity() noexcept {
        return std::complex<T>(std::numeric_limits<T>::infinity());
    }

}} // namespace easy::math

#endif
