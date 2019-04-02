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
 * File: equal.hpp
 * Date: 29/07/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_META_COMPARE_HPP
#define EDSP_META_COMPARE_HPP

#include <cmath>
#include <type_traits>
#include <limits>

namespace edsp { namespace meta {

    namespace {

        template <typename T, bool = std::is_floating_point<T>::value>
        struct _equal {
            constexpr bool operator()(const float& lhs, const float& rhs) {
                return std::abs(lhs - rhs) < std::numeric_limits<float>::epsilon();
            }
        };

        template <typename T>
        struct _equal<T, false> {
            constexpr bool operator()(const T& lhs, const T& rhs) {
                return lhs == rhs;
            }
        };
    } // namespace

    template <typename T>
    constexpr auto equal(const T& lhs, const T& rhs) {
        return _equal<T>{}(lhs, rhs);
    }
}}; // namespace edsp::meta

#endif //EDSP_META_COMPARE_HPP
