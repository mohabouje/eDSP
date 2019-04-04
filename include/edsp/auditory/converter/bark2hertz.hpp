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
* Filename: bark2herz.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_BARK2HERZ_HPP
#define EDSP_BARK2HERZ_HPP

#include <cmath>

namespace edsp { namespace auditory { inline namespace converter {

    /**
     * @brief Converts a critical band rate in Bark scale to Hertz.
     *
     * The conversion of a critical band rate z into Hertz is as follows:
     * \f[
     * f = 52548/ (z^{2}-52.56z+690.39)\, with z in bark.
     * \f]
     * or
     * \f[
     * {\displaystyle f=600\sinh(z/6)} {\displaystyle f=600\sinh(z/6)}
     * \f]
     *
     * @param z The critical band rate, in Bark
     * @returns Frequency in Hz.
     * @see hertz2bark
     */
    template <typename T>
    constexpr T bark2hertz(T z) noexcept {
        auto bark = z;
        if (z < 2) {
            bark = (20. * z - 6.0) / 17.0;
        } else if (z > 20.1) {
            bark = (50. * z + 221.1) / 61.0;
        }
        return 1960. * (bark + 0.53) / (26.28 - bark);
    }

}}} // namespace edsp::auditory::converter

#endif //EDSP_BARK2HERZ_HPP
