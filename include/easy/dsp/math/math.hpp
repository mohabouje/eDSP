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
 * Filename: math.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_MATH_MATH_HPP
#define EASYDSP_MATH_MATH_HPP

#include <cmath>
#include <cstdlib>
#include <numeric>

namespace easy { namespace dsp { namespace math {

    template <typename T>
    constexpr bool sign(const T& x) {
        return x > 0;
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
    constexpr T square(const T& in) {
        return in * in;
    }

    template <typename T>
    constexpr T random() {
        return static_cast<T>(std::rand());
    }

    template <typename T>
    constexpr T random(const T& min, const T& max) {
        return min + random<T>() * (max - min);
    }

    template <typename T>
    constexpr bool is_negative(const T& x) {
        return x < 0;
    }

    template <typename T>
    constexpr bool is_zero(const T& x) {
        return x == 0;
    }

    template <typename T>
    constexpr bool is_power_two(const T& tmp) {
        const auto x = static_cast<int32_t>(tmp);
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

}}} // namespace easy::dsp::math

#endif // EASYDSP_MATH_MATH_HPP
