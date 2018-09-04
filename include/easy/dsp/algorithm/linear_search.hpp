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
 * Filename: linear_search.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/9/2018
 */
#ifndef EASYDSP_LINEAR_SEARCH_HPP
#define EASYDSP_LINEAR_SEARCH_HPP

#include <algorithm>
namespace easy { namespace dsp {

    template <typename Iterator, typename value_type = typename std::iterator_traits<Iterator>::value_type>
    Iterator linear_search(Iterator first, Iterator last, const value_type& value) {
        return std::find(first, last, value);
    }
}} // namespace easy::dsp

#endif // EASYDSP_LINEAR_SEARCH_HPP
