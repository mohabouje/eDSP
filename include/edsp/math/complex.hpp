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
 * File: complex.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-29
 */

#ifndef EDSP_COMPLEX_H
#define EDSP_COMPLEX_H

#include <edsp/meta/unused.hpp>
#include <edsp/math/numeric.hpp>
#include <limits>
#include <complex>
#include <cmath>

namespace edsp { inline namespace math {

    /**
     * @brief Computes the magnitude of the complex number z.
     * @param z Complex value
     * @returns The magnitude of the complex number.
     */
    template <typename T>
    constexpr T magnitude(const std::complex<T>& z) {
        return std::abs(z);
    }

    /**
     * @brief Computes the phase of the complex number z.
     * @param z Complex value
     * @returns The phase of the complex number.
     */
    template <typename T>
    constexpr T phase(const std::complex<T>& z) {
        return std::arg(z);
    }

    /**
     * @brief Computes the real component of the complex number z.
     * @param z Complex value
     * @returns The real component of the complex number.
     */
    template <typename T>
    constexpr T real(const std::complex<T>& z) {
        return std::real(z);
    }

    /**
     * @brief Computes the imaginary component of the complex number z.
     * @param z Complex value
     * @returns The imaginary component of the complex number.
     */
    template <typename T>
    constexpr T imag(const std::complex<T>& z) {
        return std::imag(z);
    }

    /**
     * @brief Computes the complex conjugate of the complex number z.
     * @param z Complex value
     * @returns The complex conjugate of the complex number.
     */
    template <typename T>
    constexpr std::complex<T> conj(const std::complex<T>& z) {
        return std::conj(z);
    }

    /**
     * @brief Determines if the given real or imaginary part of the complex number is a not-a-number (NaN) value.
     * @param z Complex value
     * @returns true if the number is a NaN, false otherwise
     */
    template <typename T>
    constexpr auto is_nan(const std::complex<T>& z) noexcept {
        return std::isnan(z.real()) || std::isnan(z.imag());
    }

    /**
     * @brief Determines if the given real or imaginary part of the complex number is \f$ \infty \f$.
     * @param z Complex value
     * @returns true if the number is a \f$ \infty \f$, false otherwise
     */
    template <typename T>
    constexpr auto is_inf(const std::complex<T>& z) noexcept {
        return std::isinf(z.real()) || std::isinf(z.imag());
    }

    /**
     * @brief Computes an \f$ \infty \f$ complex number.
     * @returns An \f$ \infty \f$ complex number.
     */
    template <typename T>
    constexpr std::complex<T> infinity() noexcept {
        return std::complex<T>(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
    }

}} // namespace edsp::math

#endif
