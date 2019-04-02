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
 * File: is_null.hpp
 * Date: 29/07/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_META_ISNULL_HPP
#define EDSP_META_ISNULL_HPP

#include <edsp/meta/data.hpp>
#include <edsp/meta/unused.hpp>
#include <cstring>
#include <memory>

namespace edsp { namespace meta {

    template <class T, std::size_t N>
    constexpr bool is_null(T (&array)[N]) noexcept {
        meta::unused(array);
        return false;
    }

    template <class E>
    constexpr bool is_null(const std::initializer_list<E>& il) noexcept {
        meta::unused(il);
        return false;
    }

    template <class T>
    constexpr bool is_null(const T* ptr) {
        return ptr == nullptr || ptr == NULL;
    }

    constexpr bool is_null(const char* str) noexcept {
        return str == nullptr || (strlen(str) == 0);
    }

    template <class T>
    constexpr bool is_null(const std::unique_ptr<T>& smart) noexcept {
        return is_null(smart.get());
    }

    template <class T>
    constexpr bool is_null(const std::shared_ptr<T>& smart) noexcept {
        return is_null(smart.get());
    }

}} // namespace edsp::meta

#endif //EDSP_META_ISNULL_HPP
