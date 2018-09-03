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
 * Filename: sawtooth.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_OSCILLATOR_SAWTOOTH_HPP
#define EASYDSP_OSCILLATOR_SAWTOOTH_HPP

#include "easy/dsp/oscillators/oscillator_impl.hpp"
#include "easy/dsp/math/constant.hpp"

namespace easy { namespace dsp { namespace oscillators {

    template <typename T>
    class SawtoothOscillator : public Oscillator<T> {
    public:
        using value_type = typename Oscillator<T>::value_type;
        constexpr SawtoothOscillator(value_type amplitude, value_type samplerate, value_type frequency,
                                     value_type width) noexcept;

        constexpr value_type operator()();
        constexpr void set_width(value_type dutty) noexcept;
        constexpr value_type width() const noexcept;

    private:
        value_type width_{0};
    };

    template <typename T>
    constexpr SawtoothOscillator<T>::SawtoothOscillator(value_type amplitude, value_type samplerate,
                                                        value_type frequency, value_type width) noexcept :
        Oscillator<T>(amplitude, samplerate, frequency, 0),
        width_(width) {}

    template <typename T>
    constexpr void SawtoothOscillator<T>::set_width(value_type dutty) noexcept {
        width_ = dutty / Oscillator<T>::frequency();
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type SawtoothOscillator<T>::width() const noexcept {
        return width_ * Oscillator<T>::frequency();
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type SawtoothOscillator<T>::operator()() {
        const auto t               = Oscillator<T>::timestamp();
        const value_type result    = (t >= width_) ? -2 * t / (1 - width_) + 1 : 2 * t / width_ - 1;
        const value_type increased = t + Oscillator<T>::samplingPeriod();
        this->setTimestamp((increased > 1. / Oscillator<T>::frequency()) ? 0 : increased);
        return result * Oscillator<T>::amplitude();
    }

}}} // namespace easy::dsp::oscillators

#endif // EASYDSP_OSCILLATOR_SAWTOOTH_HPP
