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
* You should have received a copy of the GNU General Public License along withº
* this program.  If not, see <http://www.gnu.org/licenses/>
*
* Filename: hertz2mel.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_HERTZ2MEL_HPP
#define EDSP_HERTZ2MEL_HPP

#include <cmath>
namespace edsp {  namespace auditory { inline namespace converter {

    /*
     * @brief Represent the logarithmic base used in the O'Shaugnessy's book formulas.
     */
    enum mel_base {
        base_e, /*!< e base */
        base_10 /*!< 10 base */
    };

    namespace internal {

        template <mel_base scale>
        struct converter {};

        template <>
        struct converter<mel_base::base_e> {
            template <typename T>
            constexpr T operator()(T f) noexcept {
                return 1127.01048 * std::log(f / 700.0 + 1.0);
            }
        };

        template <>
        struct converter<mel_base::base_10> {
            template <typename T>
            constexpr T operator()(T f) noexcept {
                return 2595.0 * std::log10(f / 700.0 + 1.0);
            }
        };
    } // namespace internal

    /**
     * @brief Converts a frequency in Hertz into mels.
     *
     * The popular formula from O'Shaugnessy's book can be expressed with different logarithmic bases:
     * \f[
     * {\displaystyle m=2595\log _{10}\left(1+{\frac {f}{700}}\right)=1127\ln \left(1+{\frac {f}{700}}\right)}
     * \f]
     *
     * @param f Frequency in Hertz.
     * @returns Frequency in mels.
     * @see mel2hertz, mel_base
     */
    template <mel_base scale, typename T>
    constexpr T hertz2mel(T f) noexcept {
        return internal::converter<scale>{}(f);
    }

}}} // namespace edsp::converter

#endif //EDSP_HERTZ2MEL_HPP
