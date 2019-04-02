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
* Filename: index_of.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_INDEX_OF_HPP
#define EDSP_INDEX_OF_HPP

#include <iterator>

namespace edsp { inline namespace algorithm {

    /**
     * @brief Searches for an element equivalent to value in the range [first, last) and returns its position.
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param value Element to be found.
     * @returns Iterator pointing to the first element that is equal than value, or last if no such element is found.
     */
    template <typename ForwardIt>
    constexpr std::int32_t index_of(ForwardIt first, ForwardIt last,
                                    const typename std::iterator_traits<ForwardIt>::value_type& value) {
        const auto element = std::find(first, last, value);
        return static_cast<int32_t>((element != last) ? std::distance(first, element) : -1);
    }
}} // namespace edsp::algorithm

#endif //EDSP_INDEX_OF_HPP
