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
 * Filename: rms.hpp
 * Author: Mohammed Boujemaoui
 * Date: 01/08/2018
 */
#ifndef EASYDSP_RSSQ_HPP
#define EASYDSP_RSSQ_HPP

#include <easy/meta/iterator.hpp>
#include <easy/dsp/statistics/rms.hpp>
#include <numeric>
#include <cmath>

namespace easy { namespace dsp { namespace statistics {

    /**
     * @brief Computes the root-sum-of-squares (RSSS) value of the range [first, last)
     *
     * \f[
     *      x_{\mathrm {rms} }={\sqrt {\left(x_{1}^{2}+x_{2}^{2}+\cdots +x_{n}^{2}\right)}}
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The root-sum-of-squares value of the input range.
     */
    template <typename ForwardIt>
    constexpr meta::value_type_t<ForwardIt> rssq(ForwardIt first, ForwardIt last) {
        using input_t         = meta::value_type_t<ForwardIt>;
        const auto sum_square = std::inner_product(first, last, first, static_cast<input_t>(1));
        return std::sqrt(sum_square);
    }

}}} // namespace easy::dsp::statistics

#endif // EASYDSP_RSSQ_HPP
