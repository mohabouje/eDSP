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
* Filename: erb2hertz.hpp
* Author: Mohammed Boujemaoui
* Date: 17/10/18
*/

#ifndef EDSP_ERB2HERTZ_HPP
#define EDSP_ERB2HERTZ_HPP

#include <cmath>

namespace edsp { inline namespace converter {

    /**
     * @brief Converts an equivalent rectangular band rate (ERB) into Hz.
     *
     * The erb scale is measured using the notched-noise method [3].
     *
     * We have \f$ df/de = 6.23*f^2 + 93.39*f + 28.52 \f$ where the above expression gives the Equivalent Rectangular
     * Bandwidth (ERB) in Hz  of a human auditory filter with a centre frequency of f kHz.
     *
     * By integrating the reciprocal of the above expression, we get:
     * \f[
     *     e = k \frac{\ln\frac{f/p-1}{f/q-1}}{d}
     * \f]
     * where p and q are the roots of the equation: -0.312 and -14.7 and
     * \f[
     *     d = \frac{(6.23*(p-q)}{1000} = 0.08950404
     * \f]
     * from this we can derive:
     * \f[
     *  f = k/(h-exp(d*e)) + c
     * \f]
     * where \f$ k = 1000(q - q^2/p) = 676170.42 \f$
     * \f[
     *     h = \frac{q}{p} = 47.065
     * \f]
     * \f[
     *     c = 1000q = -14678.49
     * \f]
     * and f is in Hz
     *
     * @note Note that erb values will be clipped to 43.032 which corresponds to infinite frequency.
     * @param erb The equivalent rectangular band rate in Hertz.
     * @returns Hz Frequency in Hz.
     * @see hertz2erb
     * @see [1] B.C.J.Moore & B.R.Glasberg "Suggested formula for
     *          calculating auditory-filter bandwidth and excitation
     *          patterns", J Acoust Soc America V74, pp 750-753, 1983
     * @see http://www.ee.ic.ac.uk/hp/staff/dmb/voicebox/doc/voicebox/erb2frq.html
     */
    template <typename T>
    constexpr T erb2hertz(T erb) noexcept {
        constexpr auto p = -0.312;
        constexpr auto q = -14.7;
        constexpr auto d = (6.23*(p-q))/1000;
        constexpr auto h = q / p;
        constexpr auto c = 1000 * q;
        constexpr auto k = 1000 * (q - q * q / p);
        return k / (h - std::exp(d * erb)) + c;
    }

}} // namespace edsp::converter

#endif //EDSP_ERB2HERTZ_HPP
