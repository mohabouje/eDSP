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
* Filename: derivative.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_DERIVATIVE_HPP
#define EDSP_DERIVATIVE_HPP

#include <numeric>
#include <algorithm>

namespace edsp { inline namespace algorithm {

    /**
         * @brief Computes the first order derivative of the elements in the range [first, last),
         * and stores the result in another range, beginning at d_first.
         *
         * The definition of the first order derivative derivative is:
         *
         * \f[
         *  y(n) = x(n) - x(n - 1)
         * \f]
         *
         * @param first Forward iterator defining the begin of the range to examine.
         * @param last Forward iterator defining the end of the range to examine.
         * @param d_first Output iterator defining the beginning of the destination range.
         */
    template <typename InputItr, typename OutputIt, typename Numeric>
    constexpr void derivative(InputItr first, InputItr last, OutputIt d_first) {
        std::adjacent_difference(first, last, d_first);
    }

}} // namespace edsp::algorithm

#endif //EDSP_DERIVATIVE_HPP
