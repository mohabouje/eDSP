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

 * File: numeric.hpp
 * Date: 04/10/18
 * Author: Mohammed Boujemaoui Boulaghmoudi
 */

#ifndef EDSP_NUMERIC_HPP
#define EDSP_NUMERIC_HPP

#include <cmath>
#include <cstdint>
#include <complex>
#include <random>

namespace edsp { inline namespace math {

    /**
     * @brief Determines if the number is negative.
     * @param x Number to evaluate.
     * @returns true if the number is a negative number, false otherwise
     */
    template <typename T>
    constexpr bool is_negative(T x) {
        return x < 0;
    }

    /**
     * @brief Determines if the number is odd.
     * @param x Number to evaluate.
     * @returns true if the number is odd, false otherwise
     */
    template <typename T>
    constexpr bool is_odd(T x) {
        return (x % 2) == 1;
    }

    /**
     * @brief Determines if the number is even.
     * @param x Number to evaluate.
     * @returns true if the number is even, false otherwise
     */
    template <typename T>
    constexpr bool is_even(T x) {
        return !is_odd(x);
    }

    /**
     * @brief Determines if the number is power of two.
     * @param x Number to evaluate.
     * @returns true if the number is a power of two, false otherwise
     */
    template <typename T>
    constexpr bool is_power_two(T x) {
        const auto tmp = static_cast<std::int32_t>(x);
        return tmp != 0 && !(tmp & (tmp - 1));
    }

    /**
     * @brief Determines if the number is denormal floating-point.
     * @param x Number to evaluate.
     * @returns true if the number is denormal, false otherwise
     */
    template <typename T>
    constexpr bool is_denormal(T x) {
        return std::fpclassify(x) == FP_SUBNORMAL;
    }

    /**
     * @brief Determines if the number is normal floating-point.
     * @param x Number to evaluate.
     * @returns true if the number is normal, false otherwise
     */
    template <typename T>
    constexpr bool is_normal(T x) {
        return std::fpclassify(x) == FP_NORMAL;
    }

    /**
     * @brief Determines if the number is zero.
     * @param x Number to evaluate.
     * @returns true if the number is zero, false otherwise
     */
    template <typename T>
    constexpr bool is_zero(T x) {
        return std::fpclassify(x) == FP_ZERO;
    }

    /**
     * @brief Determines if the number is not-a-number (NAN).
     * @param x Number to evaluate.
     * @returns true if the number is NAN, false otherwise
     */
    template <typename T>
    constexpr bool is_nan(T x) noexcept {
        return std::isnan(x);
    }

    /**
     * @brief Determines if the number is \f$ \infty \f$.
     * @param x Number to evaluate.
     * @returns true if the number is \f$ \infty \f$, false otherwise
     */
    template <typename T>
    constexpr bool is_inf(T x) {
        return std::fpclassify(x) == FP_INFINITE;
    }

    /**
     * @brief Determines if the number is prime.
     * @param x Number to evaluate.
     * @returns true if the number is prime, false otherwise
     */
    template <typename T>
    constexpr bool is_prime(T x) {
        auto n = static_cast<std::uint64_t>(x);
        if (n <= 1)
            return 0;
        else if (n <= 3)
            return 1;
        else if (!(n & 1))
            return 0;
        else if (!(n % 3))
            return 0;
        std::uint64_t r = 5;
        while (r * r <= n) {
            if ((n % r) == 0 || (n % (r + 2)) == 0)
                return 0;
            r += 6;
        }
        return false;
    }

    /**
     * @brief Determines the sign of the input number.
     * @param x Number to evaluate.
     * @returns Returns -1 if the number is negative, 1 otherwise
     */
    template <typename T>
    constexpr T sign(T x) noexcept {
        return is_negative(x) ? static_cast<T>(-1) : static_cast<T>(1);
    }

    /**
     * @brief Computes the closest next higher power of 2 of the input number.
     * @param x Number to evaluate.
     * @returns Closest next higher power of 2.
     */
    template <typename T>
    constexpr T next_power_two(T x) {
        if (is_negative(x)) {
            return 0;
        } else if (is_power_two(x)) {
            return x;
        } else {
            auto _x = static_cast<int32_t>(x);
            --_x;
            _x |= _x >> 1;
            _x |= _x >> 2;
            _x |= _x >> 4;
            _x |= _x >> 8;
            _x |= _x >> 16;
            return static_cast<T>(_x + 1);
        }
    }

    /**
     * @brief Computes the square value of the input number.
     * @param x Number to evaluate.
     * @returns Square value of the input number.
     */
    template <typename T>
    constexpr T square(T x) {
        return x * x;
    }

    /**
     * @brief Computes the fractional part of the input number.
     * @param x Number to evaluate.
     * @returns Fractional part of the input number.
     */
    template <typename T>
    constexpr T fract(T x) {
        return x - std::floor(x);
    }

    /**
     * @brief Computes the inverse value of the input number.
     * @param x Number to evaluate.
     * @returns Inverse value of the input number.
     */
    template <typename T>
    constexpr T inv(T x) {
        return static_cast<T>(1) / x;
    }

    /**
     * @brief Computes the half value of the input number.
     * @param x Number to evaluate.
     * @returns Half value of the input number.
     */
    template <typename T>
    constexpr T half(T x) {
        return 0.5 * x;
    }

    /**
    * @brief Computes a random number in the range [min, max].
    *
    * The generated numbers follow a uniform distribution.
    * @param min Minimum number
    * @param max Maximum number
    * @return Random number in the range [min, max]
    */
    template <typename T>
    inline typename std::enable_if<std::is_floating_point<T>::value, T>::type rand(T min, T max) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_real_distribution<T> distribution(min, max);
        return distribution(eng);
    }

    /**
    * @brief Computes a random number.
    * The generated numbers follow a uniform distribution.
    * @return Random number.
    */
    template <typename T>
    inline typename std::enable_if<std::is_floating_point<T>::value, T>::type rand() {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_real_distribution<T> distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        return distribution(eng);
    }

    /**
    * @brief Computes a random number in the range [min, max].
    *
    * The generated numbers follow a uniform distribution.
    * @param min Minimum number
    * @param max Maximum number
    * @return Random number in the range [min, max]
    */
    template <typename T>
    inline typename std::enable_if<std::is_integral<T>::value, T>::type rand(T min, T max) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(eng);
    }

    /**
    * @brief Computes a random number.
    * The generated numbers follow a uniform distribution.
    * @return Random number.
    */
    template <typename T>
    inline typename std::enable_if<std::is_integral<T>::value, T>::type rand() {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<T> distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        return distribution(eng);
    }

    enum distances { manhattan, euclidean, logarithmic };

    namespace internal {

        template <distances d>
        struct distance {};

        template <>
        struct distance<distances::manhattan> {
            template <typename T>
            constexpr T operator()(T x, T y) noexcept {
                return x - y;
            }
        };

        template <>
        struct distance<distances::euclidean> {
            template <typename T>
            constexpr T operator()(T x, T y) noexcept {
                return math::square(x - y);
            }
        };

        template <>
        struct distance<distances::logarithmic> {
            template <typename T>
            constexpr T operator()(T x, T y) noexcept {
                return std::log(std::abs(x) / std::abs(y));
            }
        };
    } // namespace internal

    /**
     * @brief Computes the distance between x and y
     * @param x First element of the equation
     * @param y Second element of the equation
     * @tparam d Distance implementation to be used.
     * @return The computed distance
     * @see distances
     */
    template <distances d, typename T>
    constexpr T distance(T x, T y) noexcept {
        return internal::distance<d>{}(x, y);
    }

}} // namespace edsp::math

#endif //EDSP_NUMERIC_HPP
