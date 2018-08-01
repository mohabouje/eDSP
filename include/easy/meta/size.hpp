/*
 * Easy Meet, Yet another header-only library for C++ meta-programming.
 * Copyright (C) 2018 Mohammed Boujemaoui
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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: size
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-29
 */

#ifndef EASYMETA_SIZE_H
#define EASYMETA_SIZE_H

#include <cstdint>
#include <array>

namespace easy { namespace meta {
    template <class C>
    constexpr auto size(const C& c) -> decltype(c.size()) {
        return c.size();
    }

    template <class T, std::size_t N>
    constexpr std::size_t size(const T (&array)[N]) noexcept {
        return N;
    }

}} // namespace easy::meta
#endif