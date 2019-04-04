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
* Filename: erb2hertz.hpp
* Author: Mohammed Boujemaoui
* Date: 17/10/18
*/

#ifndef EDSP_ERB2HERTZ_HPP
#define EDSP_ERB2HERTZ_HPP

#include <cmath>

namespace edsp { namespace auditory { inline namespace converter {

    /**
     * @brief Converts an equivalent rectangular band rate (ERB) into Hz.
     *
     * @note Note that erb values will be clipped to 43.032 which corresponds to infinite frequency.
     * @param erb The equivalent rectangular band rate in Hertz.
     * @returns Hz Frequency in Hz.
     * @see hertz2erb
     * @see [1] B.C.J.Moore & B.R.Glasberg "Suggested formula for
     *          calculating auditory-filter bandwidth and excitation
     *          patterns", J Acoust Soc America V74, pp 750-753, 1983
     * @see https://ccrma.stanford.edu/~jos/bbt/Equivalent_Rectangular_Bandwidth.html
     */
    template <typename T>
    constexpr T erb2hertz(T erb) noexcept {
        return (std::pow(10.0, erb / 21.4) - 1.0) * 1000.0 / 4.37;
    }

}}} // namespace edsp::auditory::converter

#endif //EDSP_ERB2HERTZ_HPP
