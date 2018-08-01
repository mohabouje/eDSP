/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: square.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_OSCILLATOR_SQUARE_HPP
#define EASYDSP_OSCILLATOR_SQUARE_HPP

#include "easy/dsp/oscillators/oscillator_impl.hpp"
#include "easy/dsp/math/constant.hpp"

namespace easy { namespace dsp { namespace oscillators {

    template <typename T>
    class SquareOscillator : public Oscillator<T> {
    public:
        using value_type = typename Oscillator<T>::value_type;
        constexpr SquareOscillator(value_type amplitude, value_type samplerate, value_type frequency,
                                   value_type duty) noexcept;
        constexpr value_type operator()();
        constexpr void set_duty_cycle(value_type dutty) noexcept;
        constexpr value_type duty_cycle() const noexcept;

    private:
        value_type duty_{0};
    };

    template <typename T>
    constexpr SquareOscillator<T>::SquareOscillator(value_type amplitude, value_type samplerate, value_type frequency,
                                                    value_type duty) noexcept :
        Oscillator<T>(amplitude, samplerate, frequency, 0),
        duty_(duty) {}

    template <typename T>
    constexpr void SquareOscillator<T>::set_duty_cycle(value_type dutty) noexcept {
        duty_ = dutty / Oscillator<T>::frequency();
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type SquareOscillator<T>::duty_cycle() const noexcept {
        return duty_ * Oscillator<T>::frequency();
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type SquareOscillator<T>::operator()() {
        const auto t               = Oscillator<T>::timestamp();
        const value_type result    = (t >= duty_) ? -1 : 1;
        const value_type increased = t + Oscillator<T>::samplingPeriod();
        setTimestamp((increased > 1. / Oscillator<T>::frequency()) ? 0 : increased);
        return result * Oscillator<T>::amplitude();
    }

}}} // namespace easy::dsp::oscillators

#endif // EASYDSP_OSCILLATOR_SQUARE_HPP
