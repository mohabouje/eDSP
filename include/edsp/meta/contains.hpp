/**
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
 * File: contains.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-29
 */

#ifndef EDSP_META_CONTAINS_H
#define EDSP_META_CONTAINS_H

#include <type_traits>
#include <algorithm>

namespace edsp { namespace meta {

    template <typename InputIterator>
    constexpr auto contains(InputIterator first, InputIterator last,
                            const typename std::iterator_traits<InputIterator>::value_type& value) {
        const auto iter = std::find(first, last, value);
        return (iter != last);
    }

}} // namespace edsp::meta

#endif //EDSP_META_CONTAINS_H
