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
 * Filename: math.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-29
 */

#ifndef EASYMETA_MATH_H
#define EASYMETA_MATH_H

#include <cmath>
#include <cstdint>

namespace easy { namespace meta { inline namespace math {

    template <typename T>
    constexpr bool is_negative(const T& x) {
        return x < 0;
    }

    template <typename T>
    constexpr bool is_zero(const T& x) {
        return x == 0;
    }

    template <typename T>
    constexpr bool is_odd(const T& x) {
        return (x % 2) == 0;
    }

    template <typename T>
    constexpr bool is_even(const T& x) {
        return !is_odd(x);
    }

    template <typename T>
    constexpr bool is_power_two(const T& tmp) {
        const auto x = static_cast<std::int32_t>(tmp);
        return x != 0 && !(x & (x - 1));
    }

    template <typename T>
    constexpr T next_power_two(T tmp) {
        if (is_negative(tmp)) {
            return 0;
        } else if (is_power_two(tmp)) {
            return tmp;
        } else {
            auto x = static_cast<int32_t>(tmp);
            --x;
            x |= x >> 1;
            x |= x >> 2;
            x |= x >> 4;
            x |= x >> 8;
            x |= x >> 16;
            return static_cast<T>(x + 1);
        }
    }

    template <typename T>
    constexpr bool is_prime(T value) {
        auto n = static_cast<std::uint64_t>(value);
        if      (n <= 1)  return 0;
        else if (n <= 3)  return 1;
        else if (!(n & 1)) return 0;
        else if (!(n % 3)) return 0;
        std::uint64_t r = 5;
        while ( r*r <= n ) {
            if ((n % r) == 0 || (n % (r+2)) == 0)
                return 0;
            r += 6;
        }
        return false;
    }

    template <typename T>
    constexpr auto square(T value) {
        return value * value;
    }

    template <typename T>
    constexpr auto fract(T value) {
        return value - std::floor(value);
    }

    template <typename T>
    constexpr auto is_denormal(T value) {
        return std::fpclassify(value) == FP_SUBNORMAL;
    }

    template <typename T>
    constexpr auto is_normal(T value) {
        return std::fpclassify(value) == FP_NORMAL;
    }

    template <typename T>
    constexpr auto is_zero(T value) {
        return std::fpclassify(value) == FP_ZERO;
    }

    template <typename T>
    constexpr auto is_nan(T value) {
        return std::isnan(value);
    }

    template <typename T>
    constexpr auto is_inf(T value) {
        return std::fpclassify(value) == FP_INFINITE;
    }

    template <typename T>
    constexpr auto is_negative(T value) noexcept {
        return value < 0;
    }

    template <typename T>
    constexpr T inv(T value) {
        return static_cast<T>(1) / value;
    }

    template <typename T>
    constexpr auto asinh(T x) {
        return static_cast<T>(std::log(x + std::sqrt(x * x + 1)));
    }

    template <typename T>
    constexpr auto acosh(T x) {
        return static_cast<T>(std::log(x + std::sqrt(x * x - 1)));
    }

    template <typename T>
    constexpr auto manhattan_distance(T x, T y) {
        return x - y;
    }

    template <typename T>
    constexpr auto euclidean_distance(T x, T y) {
        return square(manhattan_distance(x, y));
    }
}}} // namespace easy::meta::math

#endif //EASYMETA_MATH_H
