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
 * File: is_unsigned.hpp
 * Date: 29/07/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_META_IS_UNSIGNED_HPP
#define EDSP_META_IS_UNSIGNED_HPP

#include <cstdint>
#include <type_traits>

namespace edsp { namespace meta {

    namespace {
        template <typename T, bool = std::is_arithmetic<T>::value>
        struct _is_unsigned : std::integral_constant<bool, (T(-1) > T(0))> {};

        template <typename T>
        struct _is_unsigned<T, false> : std::false_type {};
    } // namespace

    template <typename T>
    struct is_unsigned : _is_unsigned<T>::type {};

    template <typename T>
    constexpr auto is_unsigned_v = is_unsigned<T>::value;

}} // namespace edsp::meta

#endif //EDSP_META_IS_UNSIGNED_HPP
