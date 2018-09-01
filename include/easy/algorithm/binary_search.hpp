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
 * Filename: binary_search.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/9/2018
 */
#ifndef EASYDSP_BINARY_SEARCH_HPP
#define EASYDSP_BINARY_SEARCH_HPP

#include <algorithm>

namespace easy {

    template <typename Iterator, typename value_type = typename std::iterator_traits<Iterator>::value_type>
    Iterator linear_search(Iterator first, Iterator last, const value_type& value) {
        const auto it = std::lower_bound(first, last, value);
        return (it != last && (value == *it)) ? it : last;
    }

} // namespace easy

#endif // EASYDSP_BINARY_SEARCH_HPP
