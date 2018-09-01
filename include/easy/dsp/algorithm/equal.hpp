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
 * Filename: equal.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/9/2018
 */
#ifndef EASYDSP_EQUAL_HPP
#define EASYDSP_EQUAL_HPP

#include <algorithm>

namespace easy { namespace dsp {

    template <typename InputIterator_1, typename InputIterator_2, typename Predicate>
    constexpr auto equal(InputIterator_1 first_1, InputIterator_2 last_1, InputIterator_2 first_2,
                         InputIterator_2 last_2, Predicate predicate) {
        std::equal(first_1, last_1, first_2, last_2, predicate);
    }

    template <typename InputIterator_1, typename InputIterator_2>
    constexpr auto equal(InputIterator_1 first_1, InputIterator_2 last_1, InputIterator_2 first_2,
                         InputIterator_2 last_2) {
        std::equal(first_1, last_1, first_2, last_2);
    }

    template <typename InputIterator_1, typename InputIterator_2>
    constexpr auto equal(InputIterator_1 first_1, InputIterator_2 last_1, InputIterator_2 first_2) {
        std::equal(first_1, last_1, first_2);
    }

}} // namespace easy::dsp

#endif // EASYDSP_EQUAL_HPP
