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
 * File: pow2db.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EDSP_POW2DB_HPP
#define EDSP_POW2DB_HPP

#include <edsp/meta/expects.hpp>
#include <cmath>

namespace edsp { inline namespace converter {

    /**
     * @brief Convert power to decibels
     *
     * The output is computed as follows:
     * \f[
     *      y = 10 \log10{\left( x \right)}
     * \f]
     * @param power Scalar number representing the power of a sample.
     * @returns Power measurement in decibel (dB).
     */
    template <typename T>
    constexpr T pow2db(T power) noexcept {
        meta::expects(power > 0, "Expected non negative value");
        return 10 * std::log10(power);
    }
}} // namespace edsp::converter

#endif // EDSP_POW2DB_HPP
