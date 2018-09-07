/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi
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
 * Filename: cast.hpp
 * Author: Mohammed Boujemaoui
 * Date: 7/9/2018
 */

#ifndef EASYDSP_CAST_HPP
#define EASYDSP_CAST_HPP

namespace easy { inline namespace meta {

    template <typename Casted, typename Original>
    constexpr Casted sc(Original&& value) noexcept {
        return static_cast<Casted>(value);
    }

}}

#endif // EASYDSP_CAST_HPP
