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
 * Filename: join.hpp
 * Author: Mohammed Boujemaoui
 * Date: 05/10/2018
 */
#ifndef EASYDSP_JOIN_HPP
#define EASYDSP_JOIN_HPP

#include <easy/meta/iterator.hpp>
#include <sstream>

namespace easy { namespace dsp  { namespace string {

    /**
     * @brief Join the strings in the range [first, last) and stores the result in another string,
     * beginning at d_first.
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @param delimiter The delimiting character.
     * @see split
     */

    template <typename InputIt, typename Char>
    inline void join(InputIt first, InputIt last, std::basic_string<Char>& d_str, Char delimiter = '') {
        std::stringstream ss;
        for (; first != last; ++first) {
            ss << *first << delimiter;
        }
        d_str = ss.str();
    };


}}}

#endif //EASYDSP_JOIN_HPP
