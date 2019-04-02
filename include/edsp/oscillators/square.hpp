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
 * File: square.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EDSP_OSCILLATOR_SQUARE_HPP
#define EDSP_OSCILLATOR_SQUARE_HPP

#include <edsp/oscillators/sinusoidal.hpp>
#include <edsp/meta/expects.hpp>
#include <cmath>

namespace edsp { namespace oscillators {

    /**
     * @class square_oscillator
     * @brief The class %square_oscillator generates a square signal.
     *
     * The square wave can be constructed from straight line segments. The square waves contain a wide range of harmonics.
     * It can be defined as simply the sign function of a sinusoid:
     * 
     * \f[
     * 
     * {\displaystyle {\begin{aligned}x(t)&={sgn} 
     * \left(\sin {\frac {t}{T}}\right)={sgn}(\sin ft)\\v(t)&={sgn} \left(\cos {\frac {t}{T}}\right)={sgn}(\cos ft),\end{aligned}}}
     * 
     * \f]
     *
     * which will be 1 when the sinusoid is positive, −1 when the sinusoid is negative, and 0 at the discontinuities.
     * Here, T is the period of the square wave, or equivalently, f is its frequency, where f = 1/T.
     */

    template <typename T>
    class square_oscillator : public oscillator<T> {
    public:
        using value_type = T;

        /**
         * @brief Creates a square oscillator that generates a waveform with the configuration.
         *
         * @param amplitude Amplitude of the waveform.
         * @param sample_rate The sampling frequency in Hz.
         * @param frequency The fundamental frequency of the signal (also known as pitch).
         * @param duty Duty factor, numeric value from [0,1]
         */
        constexpr square_oscillator(value_type amplitude, value_type sample_rate, value_type frequency,
                                    value_type duty) noexcept;

        /**
         * @brief Generates one step.
         * @return Returns the value of the current step.
         */
        constexpr value_type operator()();

        /**
         * @brief Set the duty cycle of the oscillator
         *
         * The duty cycle is the fraction of one period in which a signal or system is active. In this case a signal is
         * active when the output is 1.
         *
         * @param duty Numeric value representing the duty cycle [0, 1]
         */
        constexpr void set_duty(value_type duty) noexcept;

        /**
         * @brief Returns the current duty cycle
         * @return Numeric value representing the dity cycle.
         */
        constexpr value_type duty() const noexcept;

    private:
        value_type duty_{0};
    };

    template <typename T>
    constexpr square_oscillator<T>::square_oscillator(value_type amplitude, value_type sample_rate,
                                                      value_type frequency, value_type duty) noexcept :
        oscillator<T>(amplitude, sample_rate, frequency, 0) {
        set_duty(duty);
    }

    template <typename T>
    constexpr void square_oscillator<T>::set_duty(value_type duty) noexcept {
        meta::expects(duty >= 0 && duty <= 1, "duty must be a real number between 0 and 1.");
        duty_ = duty * oscillator<T>::inverse_frequency_;
    }

    template <typename T>
    constexpr typename square_oscillator<T>::value_type square_oscillator<T>::duty() const noexcept {
        return duty_ * oscillator<T>::frequency_;
    }

    template <typename T>
    constexpr typename square_oscillator<T>::value_type square_oscillator<T>::operator()() {
        const auto current_t = std::fmod(oscillator<T>::timestamp_, oscillator<T>::inverse_frequency_);
        oscillator<T>::set_timestamp(oscillator<T>::timestamp_ + oscillator<T>::sampling_period_);
        return (current_t >= duty_ ? 1 : -1) * oscillator<T>::amplitude_;
    }

}} // namespace edsp::oscillators

#endif // EDSP_OSCILLATOR_SQUARE_HPP
