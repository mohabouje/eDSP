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
* Filename: cent2hertz.hpp
* Author: Mohammed Boujemaoui
* Date: 18/10/18
*/

#ifndef EDSP_CENT2FREQ_HPP
#define EDSP_CENT2FREQ_HPP

#include <edsp/math/numeric.hpp>

namespace edsp { namespace auditory { inline namespace converter {

    /**
     * @brief Converts a frequency in Cent scale into Hertz.
     *
     * Example: 100 cents corresponds to one semitone and 440Hz corresponds to 5700 cents.
     * @param c The frequency in Cent scale.
     * @returns Frequency in Hz.
     * @see hertz2bark
     */
    template <typename T>
    constexpr T cent2hertz(T c) noexcept {
        const T p = 1200 / std::log(2);
        const T q = 5700 - p * std::log(440);
        return math::sign(c) * (std::exp((std::abs(c) - q) / p));
    }

}}} // namespace edsp::auditory::converter

#endif //EDSP_CENT2FREQ_HPP
