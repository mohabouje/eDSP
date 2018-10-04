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
 * Filename: bartlett.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_BARTLETT_HPP
#define EASYDSP_BARTLETT_HPP

#include <easy/dsp/math/numeric.hpp>
#include <easy/meta/iterator.hpp>

namespace easy { namespace dsp { namespace windowing {

    /**
     * @brief Computes a Bartlett window of length N and stores the result in the range, beginning at d_first.
     * @param N Number of elements to compute.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename OutIterator, typename Integer>
    constexpr void bartlett(OutIterator d_first, Integer N) {
        using value_type  = meta::value_type_t<OutIterator>;
        using size_type   = meta::diff_type_t<OutIterator>;
        const auto size   = static_cast<size_type>(N);
        const auto middle = math::is_even(size) ? size / 2 : (size + 1) / 2;
        const auto factor = math::inv(static_cast<value_type>(size - 1));
        for (size_type i = 0; i < middle; ++i, ++d_first) {
            *d_first = 2 * i * factor;
        }
        for (size_type i = middle; i < size; ++i, ++d_first) {
            *d_first = 2 - 2 * i * factor;
        }
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_BARTLETT_HPP
