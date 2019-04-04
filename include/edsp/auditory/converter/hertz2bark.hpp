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
* Filename: hz2bark.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_HZ2BARK_HPP
#define EDSP_HZ2BARK_HPP

#include <cmath>

namespace edsp { namespace auditory { inline namespace converter {

    /**
     * @brief Converts a frequency in Hertz into its equivalent Bark scale value.
     *
     * The conversion of a frequency f (Hz) into Bark is implemented as follows:
     * \f[
     * { \alpha =[(26.81f)/(1960+f)]-0.53\,
     * f]
     * An then:
     * - If \f$  \alpha < 2 \f$ then \f$ f_b = 0.15 * (2 - \alpha) \f$.
     * - If \f$  \alpha > 20.1 \f$ then \f$ f_b = 0.22 * (\alpha - 20.1) \f$.
     *
     * @param f Frequency in Hz
     * @returns Frequency in Bark scale.
     * @see bark2band, hertz2band
     */
    template <typename T>
    constexpr T hertz2bark(T f) noexcept {
        const auto bark = 26.81 * f / (1960. + f) - 0.53;
        if (bark < 2) {
            return bark + 0.15 * (2. - bark);
        } else if (bark > 20.1) {
            return bark + 0.22 * (bark - 20.1);
        }
        return bark;
    }

}}} // namespace edsp::auditory::converter

#endif //EDSP_HZ2BARK_HPP
