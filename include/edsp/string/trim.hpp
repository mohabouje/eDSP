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
 * File: trim.hpp
 * Author: Mohammed Boujemaoui
 * Date: 05/10/2018
 */
#ifndef EDSP_TRIM_HPP
#define EDSP_TRIM_HPP

#include <edsp/meta/iterator.hpp>
#include <sstream>
#include <algorithm>

namespace edsp { namespace string {

    /**
    * @brief Filters the leading whitespace of the input string.
    * @param str Input string.
    */
    template <typename String>
    inline void ltrim(String& str) {
        str.erase(
            std::begin(str), std::find_if(std::begin(str), std::end(str),
                                [](auto character) { return !std::isspace(character); }));
    }

    /**
    * @brief Filters the trailing whitespace of the last position of the input string.
    * @param str Input string.
    */
    template <typename String>
    inline void rtrim(String& str) {
        str.erase(
            std::find_if(std::rbegin(str), std::rend(str),
                         [](auto character) { return !std::isspace(character); })
                .base(), std::end(str));
    }

    /**
     * @brief Filters the leading and trailing whitespace of the input string.
     * @param str Input string.
     */
    template <typename String>
    inline void trim(String& str) {
        ltrim(str);
        rtrim(str);
    }

}} // namespace edsp::string

#endif //EDSP_TRIM_HPP
