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
 * Filename: sine.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_OSCILLATOR_SIN_HPP
#define EASYDSP_OSCILLATOR_SIN_HPP

#include "easy/dsp/oscillators/oscillator_impl.hpp"
#include "easy/dsp/math/constant.hpp"
#include <cmath>

namespace easy { namespace dsp { namespace oscillators {

    template <typename T>
    class SinOscillator : public Oscillator<T> {
    public:
        using value_type = typename Oscillator<T>::value_type;
        constexpr SinOscillator(value_type amplitude, value_type samplerate, value_type frequency,
                                value_type phase) noexcept;
        constexpr value_type operator()();
    };

    template <typename T>
    constexpr SinOscillator<T>::SinOscillator(value_type amplitude, value_type samplerate, value_type frequency,
                                              value_type phase) noexcept :
        Oscillator<T>(amplitude, samplerate, frequency, phase) {}

    template <typename T>
    constexpr typename SinOscillator<T>::value_type SinOscillator<T>::operator()() {
        const value_type result =
            std::sin(constants<value_type>::two_pi *
                     (Oscillator<T>::frequency() * Oscillator<T>::timestamp() + Oscillator<T>::phase()));
        this->setTimestamp(Oscillator<T>::timestamp() + Oscillator<T>::samplingPeriod());
        return result * Oscillator<T>::amplitude();
    }

}}} // namespace easy::dsp::oscillators

#endif // EASYDSP_OSCILLATOR_SIN_HPP
