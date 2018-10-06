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
 * Filename: to_upper.hpp
 * Author: Mohammed Boujemaoui
 * Date: 05/10/2018
 */

#ifndef EASYDSP_TO_UPPER_HPP
#define EASYDSP_TO_UPPER_HPP

#include <algorithm>
#include <cctype>

namespace edsp { namespace string {

    /**
     * Converts the given character to uppercase according to the character conversion rules defined by the currently
     * installed C locale.
     * @param character character to be converted.
     * @return Uppercase version of the input character.
     */
    template <typename Char>
    constexpr Char toupper(Char character) {
        return std::toupper(character);
    }

    /**
     * @brief Converts the characters in the range [first, last) to uppercase according to the character conversion rules
     * defined by the currently installed C locale and stores the result in another range, beginning at d_first.
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename InputIt, typename OutputIt>
    constexpr void toupper(InputIt first, InputIt last, OutputIt d_first) {
        std::transform(first, last, first, toupper);
    }

}} // namespace edsp::string

#endif //EASYDSP_TO_UPPER_HPP
