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
 * File: db2pow.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EDSP_DB2POW_HPP
#define EDSP_DB2POW_HPP

#include <cmath>
namespace edsp { inline namespace converter {

    /**
     * @brief Convert decibels to power.
     *
     * The output is computed as follows:
     * \f[
     *      y = 10^{\frac{x}{10}}
     * \f]
     * @param db Scalar number in decibels.
     * @returns Power measurements.
     */
    template <typename T>
    constexpr T db2pow(T db) noexcept {
        return std::pow(10, db / static_cast<T>(10));
    }

}} // namespace edsp::converter

#endif // EDSP_DB2POW_HPP
