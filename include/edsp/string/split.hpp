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
 * File: split.hpp
 * Author: Mohammed Boujemaoui
 * Date: 05/10/2018
 */
#ifndef EDSP_SPLIT_HPP
#define EDSP_SPLIT_HPP

#include <edsp/meta/iterator.hpp>
#include <sstream>

namespace edsp { namespace string {

    /**
     * @brief Splits this string around matches of the given character and stores the result in another range, beginning at d_first.
     * @param str Input string.
     * @param character The delimiting character.
     * @param d_first Output iterator defining the beginning of the destination range.
     */

    template <typename Char, typename OutputIt>
    inline void split(const std::basic_string<Char>& str, OutputIt d_first, Char character = ' ') {
        std::stringstream test(str);
        std::basic_string<Char> segment;
        while (std::getline(test, segment, character)) {
            if (!segment.empty()) {
                *d_first = segment;
                ++d_first;
            }
        }
    }

}} // namespace edsp::string

#endif //EDSP_SPLIT_HPP
