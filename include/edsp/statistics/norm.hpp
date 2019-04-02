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
* Filename: norm.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_NORM_HPP
#define EDSP_NORM_HPP

#include <edsp/meta/iterator.hpp>
#include <edsp/math/numeric.hpp>
#include <functional>

namespace edsp { namespace statistics {

    /**
     * @brief Compute the L2-norm of the signals in the range [first1, last1).
     *
     * The \f$ l^2 \f$-norm is defined as:
     *
     * \f[
     * |x|=\sqrt(\sum_{n=0}^{N - 1}|x(n)|^2),
     * \f]
     *
     * where \f$ |x_k| \f$ denotes the complex modules.
     *
     * @param first Input iterator defining the beginning of the first input range.
     * @param last Input iterator defining the ending of the first input range.
     * @returns L2-norm of the input signal.
     */
    template <typename InputIt>
    constexpr meta::value_type_t<InputIt> norm(InputIt first, InputIt last) {
        using value_type     = meta::value_type_t<InputIt>;
        const auto predicate = [](const value_type accumulated, const value_type comming) {
            return accumulated + math::square(std::abs(comming));
        };
        const auto accumulated = std::accumulate(first, last, static_cast<value_type>(0), std::cref(predicate));
        return std::sqrt(accumulated);
    }

}} // namespace edsp::statistics

#endif //EDSP_NORM_HPP
