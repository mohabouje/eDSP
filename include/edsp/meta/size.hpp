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
 * File: size
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-29
 */

#ifndef EDSP_META_SIZE_H
#define EDSP_META_SIZE_H

#include <edsp/meta/unused.hpp>
#include <cstdint>
#include <array>

namespace edsp { namespace meta {
    template <class C>
    constexpr auto size(const C& c) -> decltype(c.size()) {
        return c.size();
    }

    template <class T, std::size_t N>
    constexpr std::size_t size(const T (&array)[N]) noexcept {
        meta::unused(array);
        return N;
    }

}} // namespace edsp::meta
#endif
