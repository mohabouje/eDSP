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
 * Filename: clipper.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_CLIPPER_HPP
#define EASYDSP_CLIPPER_HPP

#include <algorithm>
#include <easy/meta/iterator.hpp>

namespace easy { namespace dsp { inline namespace algorithm {

    /**
     * @brief Limits the values of the elements in the range [first, last) once it exceeds a threshold [min, max],
     * and stores the result in another range, beginning at d_first.
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param d_first Output irerator defining the beginning of the destination range.
     * @param min Minimum threshold value.
     * @param max Maximum threshold value.
     */
    template <typename InputItr, typename OutputIt, typename Numeric>
    constexpr void clipper(InputItr first, InputItr last, OutputIt d_first, Numeric min, Numeric max) {
        std::transform(first, last, d_first, [=](const meta::value_type_t<InputItr> val) -> meta::value_type_t<OutputIt> {
            return (val < min) ? min : (val > max) ? max : val;
        });
    }

}}} // namespace easy::dsp::algorithm

#endif // EASYDSP_CLIPPER_HPP
