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
 * File: sawtooth.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EDSP_OSCILLATOR_SAWTOOTH_HPP
#define EDSP_OSCILLATOR_SAWTOOTH_HPP

#include <edsp/oscillators/sinusoidal.hpp>
#include <edsp/math/constant.hpp>
#include <edsp/meta/expects.hpp>

namespace edsp { namespace oscillators {

    /**
     * @class sawtooth_oscillator
     * @brief The class %sawtooth_oscillator generates a sawtooth signal.
     *
     * The signal increases linearly from -1 to 1 in\f$ [0, 2  \pi  wi] \f$ interval, and decreases linearly from 1 to
     * -1 in the interval \f$ 2  \pi  w, 2  \pi] \f$, where \f$ w \f$ is the width of the periodic signal.
     *
     * If \f$ w \f$ is 0.5, the function generates a standard triangular wave. The triangle wave shares many geometric
     * similarities with the sawtooth wave, except it has two sloping line segments.
     */
    template <typename T>
    class sawtooth_oscillator : public oscillator<T> {
    public:
        using value_type = T;

        /**
         * @brief Creates a sawtooth oscillator that generates a waveform with the configuration.
         *
         * @param amplitude Amplitude of the waveform.
         * @param sample_rate The sampling frequency in Hz.
         * @param frequency The fundamental frequency of the signal (also known as pitch).
         * @param width Width factor, numeric value from [0,1]
         */
        constexpr sawtooth_oscillator(value_type amplitude, value_type sample_rate, value_type frequency,
                                      value_type width) noexcept;
        /**
         * @brief Generates one step.
         * @return Returns the value of the current step.
         */
        constexpr value_type operator()();

        /**
         * @brief Set the width of the periodic signal
         * @param width Numeric value from in the interval [0,1]
         * @see width
         */
        constexpr void set_width(value_type width) noexcept;

        /**
         * @brief Returns the width of the periodic signal
         *
         * The width is a real number between 0 and 1 which specifies the point between
         * 0 and \f$ 2  \pi \f$ where the maximum is.
         * @return Numeric value from in the interval [0,1]
         */
        constexpr value_type width() const noexcept;

    private:
        value_type width_{0.3};
    };

    template <typename T>
    constexpr sawtooth_oscillator<T>::sawtooth_oscillator(value_type amplitude, value_type sample_rate,
                                                          value_type frequency, value_type width) noexcept :
        oscillator<T>(amplitude, sample_rate, frequency, 0) {
        set_width(width);
    }

    template <typename T>
    constexpr void sawtooth_oscillator<T>::set_width(value_type width) noexcept {
        meta::expects(width >= 0 && width <= 1, "width must be a real number between 0 and 1.");
        width_ = width;
    }

    template <typename T>
    constexpr typename sawtooth_oscillator<T>::value_type sawtooth_oscillator<T>::width() const noexcept {
        return width_;
    }

    template <typename T>
    constexpr typename sawtooth_oscillator<T>::value_type sawtooth_oscillator<T>::operator()() {
        const auto t = std::fmod(oscillator<T>::frequency_ * oscillator<T>::timestamp_, 1);
        oscillator<T>::set_timestamp(oscillator<T>::timestamp_ + oscillator<T>::sampling_period_);
        if (width_ != 0 and t < width_) {
            return oscillator<T>::amplitude_ * (2 * t / width_ - 1);
        } else if (width_ != 1 and t >= width_) {
            return oscillator<T>::amplitude_ * (-2 * (t - width_) / (1 - width_) + 1);
        }
        return 0;
    }

}} // namespace edsp::oscillators

#endif // EDSP_OSCILLATOR_SAWTOOTH_HPP
