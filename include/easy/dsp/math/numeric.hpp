/* 
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (c) 2018  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 * Filename: numeric.hpp
 * Created at: 04/10/18
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 */

#ifndef EASYDSP_NUMERIC_HPP
#define EASYDSP_NUMERIC_HPP

#include <cmath>
#include <cstdint>
#include <complex>
#include <random>

namespace easy { namespace dsp { inline namespace math {

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
     * @returns true if the number is even, false otherwise
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

    template <typename T>
    constexpr T manhattan_distance(T x, T y) noexcept {
        return x - y;
    }

    template <typename T>
    constexpr T euclidean_distance(T x, T y) noexcept {
        return square(manhattan_distance(x, y));
    }

    template <typename T>
    constexpr T logarithmic_distance(T x, T y) noexcept {
        return std::log(std::abs(x) / std::abs(y));
    }

}}} // namespace easy::dsp::math

#endif //EASYDSP_NUMERIC_HPP
