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
 * File: real2complex.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/9/2018
 */
#ifndef EDSP_REAL2COMPLEX_HPP
#define EDSP_REAL2COMPLEX_HPP

#include <edsp/meta/iterator.hpp>
#include <algorithm>
#include <complex>

namespace edsp { inline namespace converter {

    /**
     * @brief Converts a range of scalar numbers in to an equivalent complex number
     * and stores the result in another range.
     *
     * @note Use this function when the output range does not have an imaginary part.
     * @param first Input iterator defining the beginning of the range representing the real part.
     * @param last Input iterator defining the ending of the range representing the real part.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename InputIt, typename OutputIt>
    constexpr void real2complex(InputIt first, InputIt last, OutputIt d_first) {
        using output_t = meta::value_type_t<OutputIt>;
        std::transform(first, last, d_first, [](const auto real) -> output_t { return {real, 0}; });
    }

    /**
     * @brief Converts a range of scalar numbers in to an equivalent complex number
     * and stores the result in another range.
     *
     * @param first1 Input iterator defining the beginning of the range representing the real part.
     * @param last1 Input iterator defining the ending of the range representing the real part.
     * @param first2 Input iterator defining the beginning of the range representing the imaginary part.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename InputIt, typename OutputIt>
    constexpr void real2complex(InputIt first1, InputIt last1, InputIt first2, OutputIt d_first) {
        using output_t = meta::value_type_t<OutputIt>;
        std::transform(first1, last1, first2, d_first, [](const auto real, const auto imag) -> output_t {
            return {real, imag};
        });
    }

}} // namespace edsp::converter

#endif // EASDY_REAL2COMPLEX_HPP
