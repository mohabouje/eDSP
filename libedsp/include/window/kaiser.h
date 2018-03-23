/*
 * eDSP, A cross-platform DSP framework written in C++.
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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EDSP_WINDOW_KAISER_H
#define EDSP_WINDOW_KAISER_H

#include "window.h"

EDSP_BEGIN_NAMESPACE

    /**
     * @brief Kaiser %window implementation.
     *
     * This %window is also called Kaiser-Bessel window was developed by James Kaiser.
     * The Fourier transform of the window has a stop-band attenuation that is derived
     * from the parameter %beta.
     *
     * By default: %beta = 0.5
     */
    class Kaiser : Window {
    public:

        /**
         * @brief Creates and computes a Kaiser %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Kaiser(size_type size);

        /**
         * @brief Creates and compute a Kaiser %window with the given size and the spectral sidelobe attenuation factor.
         * @param size The number of elements to initially create.
         * @param beta Spectral slidelobe attenuation factor.
         */
        Kaiser(size_type size, value_type beta);
        ~Kaiser() override;

        void initialize() override;

        /**
         * @brief Set the spectral sidelobe attenuation factor.
         * @param beta sidelobe attenuation factor.
         */
        void set_beta(value_type beta) EDSP_NOEXCEPT;

        /**
         * @bried Returns the Kaiser %window parameter that modify the sidelobe attenuation of the FFT.
         * @return The spectral sidelobe attenuation factor
         */
        value_type beta() const EDSP_NOEXCEPT;
    private:
        value_type beta_{0.5};
    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_KAISER_H
