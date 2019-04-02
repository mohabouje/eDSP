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
 * File: unused.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EDSP_META_UNUSED_HPP
#define EDSP_META_UNUSED_HPP

#include <edsp/types/string_view.hpp>
#include <edsp/meta/data.hpp>
#include <string>

namespace edsp { namespace meta {

    template <typename T>
    constexpr void unused(const T& variable) {
        (void) variable;
    }

    template <typename T>
    constexpr void unused(const T& variable, const edsp::string_view& message) {
        unused(variable);
        unused(message);
    }

}} // namespace edsp::meta

#endif // UNUSED_HPP
