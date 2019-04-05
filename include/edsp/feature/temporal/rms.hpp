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
 * File: rms.hpp
 * Author: Mohammed Boujemaoui
 * Date: 14/6/2018
 */
#ifndef EDSP_STATISTICAL_RMS_H
#define EDSP_STATISTICAL_RMS_H

#include <numeric>
#include <cmath>

namespace edsp { namespace feature { inline namespace temporal {

    /**
     * @brief Computes the root-mean-square (RMS) value of the range [first, last)
     *
     * The RMS value is defined as:
     * \f[
     *      x_{\mathrm {rms} }={\sqrt {{\frac {1}{n}}\left(x_{1}^{2}+x_{2}^{2}+\cdots +x_{n}^{2}\right)}}
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The root mean square value of the input range.
     */
    template <typename ForwardIt>
    constexpr auto rms(ForwardIt first, ForwardIt last) {
        using value_type       = typename std::iterator_traits<ForwardIt>::value_type;
        const auto accumulated = std::inner_product(first, last, first, static_cast<value_type>(1));
        return std::sqrt(accumulated / static_cast<value_type>(std::distance(first, last)));
    }
}}} // namespace edsp::feature::temporal

#endif // EDSP_STATISTICAL_RMS_H
