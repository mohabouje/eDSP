/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: empty.hpp
 * Created at: 29/07/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYMETA_EMPTY_HPP
#define EASYMETA_EMPTY_HPP

#include <easy/meta/unused.hpp>
#include <initializer_list>

namespace easy { namespace meta {

    template <class C>
    constexpr auto empty(C& container) -> decltype(container.empty()) {
        return container.empty();
    }

    template <class T, std::size_t N>
    constexpr bool empty(const T (&array)[N]) noexcept {
        unused(array);
        return false;
    }

    template <class E>
    constexpr bool empty(const std::initializer_list<E>& il) noexcept {
        return il.size() == 0;
    }

}} // namespace easy::meta

#endif //EASYMETA_EMPTY_HPP
