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
 * File: rad2deg.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EDSP_RAD2DEG_HPP
#define EDSP_RAD2DEG_HPP

#include <edsp/math/constant.hpp>
#include <cmath>

namespace edsp { inline namespace converter {

    /**
     * @brief Convert angle from radians to degrees.
     *
     * The output is computed as follows:
     * \f[
     *      y =  x \frac{180}{\pi}
     * \f]
     * @param radians Angle in radians.
     * @returns Angle in degrees.
     */
    template <typename T>
    constexpr T rad2deg(T radians) noexcept {
        return radians / constants<T>::pi * static_cast<T>(180);
    }

}} // namespace edsp::converter

#endif // EDSP_RAD2DEG_HPP
