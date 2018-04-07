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

#include "window.hpp"

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
    EDSP_DEFINE_IMPLICITS(Kaiser)
public:
    /**
     * @brief Creates and computes a Kaiser %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Kaiser(_In_ size_type size);

    /**
     * @brief Creates and compute a Kaiser %window with the given size and the spectral sidelobe attenuation factor.
     * @param size The number of elements to initially create.
     * @param beta Spectral slidelobe attenuation factor.
     */
    Kaiser(_In_ size_type size, _In_ value_type beta);
    ~Kaiser() EDSP_OVERRIDE;

    EDSP_INLINE void initialize() EDSP_OVERRIDE;

    /**
     * @brief Set the spectral sidelobe attenuation factor.
     * @param beta sidelobe attenuation factor.
     */
    EDSP_INLINE void set_beta(_In_ value_type beta) EDSP_NOEXCEPT;

    /**
     * @brief Returns the Kaiser %window parameter that modify the sidelobe attenuation of the FFT.
     * @return The spectral sidelobe attenuation factor
     */
    EDSP_INLINE value_type beta() const EDSP_NOEXCEPT;
private:
    value_type _beta = 0.5;
};

Kaiser::Kaiser(_In_ Window::size_type size) : Window(size) {

}

Kaiser::Kaiser(_In_ Window::size_type size, _In_ Window::value_type beta) : Window(size), _beta(beta) {

}

Kaiser::~Kaiser() = default;

void Kaiser::initialize() = default;

void Kaiser::set_beta(_In_ Window::value_type beta) EDSP_NOEXCEPT {
    _beta = beta;
}

Window::value_type Kaiser::beta() const EDSP_NOEXCEPT {
    return _beta;
}

EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_KAISER_H
