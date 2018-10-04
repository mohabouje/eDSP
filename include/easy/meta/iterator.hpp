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
 * Filename: iterator.hpp
 * Author: Mohammed Boujemaoui
 * Date: 7/9/2018
 */
#ifndef EASYDSP_ITERATOR_HPP
#define EASYDSP_ITERATOR_HPP

#include <type_traits>
#include <iterator>

namespace easy { namespace meta {

    template <typename Iterator>
    using value_type_t = typename std::iterator_traits<Iterator>::value_type;

    template <typename Iterator>
    using diff_type_t = typename std::iterator_traits<Iterator>::difference_type;

}}     // namespace easy::meta
#endif // EASYDSP_ITERATOR_HPP
