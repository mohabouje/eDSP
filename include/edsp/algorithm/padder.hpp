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
 * File: padder.hpp
 * Date: 09/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_PADDER_HPP
#define EDSP_PADDER_HPP

#include <edsp/meta/iterator.hpp>
#include <edsp/meta/expects.hpp>
#include <algorithm>

namespace edsp { inline namespace algorithm {

    /**
     * @brief Extends the signal defined in the range [first, last) with zeros
     * and stores the result in the range [d_first, d_last].
     *
     * \f[
     *  y(n) = \left\{\begin{matrix}
     *  x(n) & 0 <= n < N \\
     *  0 & N <= n < M
     *  \end{matrix}\right.
     * \f]
     *
     * where N is the size of the input range and M the size of the output range.
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param d_first Forward iterator defining the begin of the output range.
     * @param d_last Forward iterator defining the end of the output range.
     */
    template <typename InputIt, typename OutputIt>
    constexpr void padder(InputIt first, InputIt last, OutputIt d_first, OutputIt d_last) {
        const auto i_size = std::distance(first, last);
        const auto d_size = std::distance(d_first, d_last);
        meta::expects(d_size >= i_size, "Output size should be greater or equal than the input size");
        std::copy(first, last, d_first);
        std::fill(d_first + i_size, d_last, static_cast<meta::value_type_t<OutputIt>>(0));
    }

}} // namespace edsp::algorithm

#endif // EDSP_PADDER_HPP
