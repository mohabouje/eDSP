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
 * File: mag2db.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EDSP_MAG2DB_HPP
#define EDSP_MAG2DB_HPP

#include <edsp/meta/expects.hpp>
#include <cmath>

namespace edsp { inline namespace converter {

    /**
     * @brief Convert magnitude to decibels (dB)
     *
     * The output is computed as follows:
     * \f[
     *      y = 20 \log10{ \left( x \right) }
     * \f]
     * @param magnitude Scalar number in magnitude scale.
     * @return Scalar number in decibels.
     */
    template <typename T>
    constexpr T mag2db(T magnitude) noexcept {
        meta::expects(magnitude > 0, "Expected non negative value");
        return 20 * std::log10(magnitude);
    }
}} // namespace edsp::converter

#endif // EDSP_MAG2DB_HPP
