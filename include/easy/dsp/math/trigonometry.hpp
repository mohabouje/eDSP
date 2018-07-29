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
 * Filename: trigonometry.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_TRIGONOMETRY_HPP
#define EASYDSP_TRIGONOMETRY_HPP

#include <cmath>
#include <cstdlib>
#include <numeric>
#include "easymeet/dsp/math/constant.hpp"

namespace easy { namespace dsp { namespace math {

    template <typename T>
    constexpr T asinh(const T& x) {
        return static_cast<T>(std::log(x + std::sqrt(x * x + 1)));
    }

    template <typename T>
    constexpr T acosh(const T& x) {
        return static_cast<T>(std::log(x + std::sqrt(x * x - 1)));
    }

    template <typename T>
    constexpr T deg_to_rad(const T& x) {
        return static_cast<T>(x * constants<T>::pi / 180);
    }

    template <typename T>
    constexpr T rad_to_deg(const T& x) {
        return static_cast<T>(x / constants<T>::pi * 180);
    }

}}} // namespace easy::dsp::math

#endif // EASYDSP_TRIGONOMETRY_HPP
