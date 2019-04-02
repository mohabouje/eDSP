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
 * File: triangular.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EDSP_OSCILLATOR_TRIANGLE_HPP
#define EDSP_OSCILLATOR_TRIANGLE_HPP

#include <edsp/oscillators/sawtooth.hpp>
#include <edsp/math/constant.hpp>

namespace edsp { namespace oscillators {

    /**
     * @class triangular_oscillator
     * @brief The class %triangular_oscillator generates a triangular signal.
     *
     * The signal increases linearly from -1 to 1 in\f$ [0, \pi ] \f$ interval, and decreases linearly from 1 to
     * -1 in the interval \f$ [ \pi , 2 \pi] \f$.
     *
     * The triangle wave shares many geometric similarities with the sawtooth wave, except it has two sloping line segments.
     * @see sawtooth_oscillator
     */
    template <typename T>
    class triangular_oscillator : public sawtooth_oscillator<T> {
    public:
        using value_type = T;

        /**
         * @brief Creates a sawtooth oscillator that generates a waveform with the configuration.
         *
         * @param amplitude Amplitude of the waveform.
         * @param sample_rate The sampling frequency in Hz.
         * @param frequency The fundamental frequency of the signal (also known as pitch).
         */
        constexpr triangular_oscillator(value_type amplitude, value_type sample_rate, value_type frequency) noexcept;
    };

    template <typename T>
    constexpr triangular_oscillator<T>::triangular_oscillator(value_type amplitude, value_type sample_rate,
                                                              value_type frequency) noexcept :
        sawtooth_oscillator<T>(amplitude, sample_rate, frequency, 0.5) {}

}} // namespace edsp::oscillators

#endif // EDSP_OSCILLATOR_TRIANGLE_HPP
