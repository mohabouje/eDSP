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
 * Filename: oscillator_impl.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_OSCILLATOR_IMPL_HPP
#define EASYDSP_OSCILLATOR_IMPL_HPP

#include <easy/dsp/math/math.hpp>

namespace easy { namespace dsp { namespace oscillators {

    template <typename T>
    class Oscillator {
    public:
        using value_type = T;
        constexpr Oscillator(value_type amplitude, value_type samplerate, value_type frequency,
                             value_type phase) noexcept;
        constexpr value_type frequency() const noexcept;
        constexpr void setFrequency(value_type frequency) noexcept;
        constexpr value_type phase() const noexcept;
        constexpr void setPhase(value_type phase) noexcept;
        constexpr value_type timestamp() const noexcept;
        constexpr void setTimestamp(value_type timestamp) noexcept;
        constexpr value_type samplerate() const noexcept;
        constexpr void setSamplerate(value_type samplerate) noexcept;
        constexpr value_type samplingPeriod() const noexcept;
        constexpr value_type amplitude() const noexcept;
        constexpr void setAmplitude(value_type amplitude) noexcept;
        constexpr void reset() noexcept;

    private:
        value_type amplitude_{0.};
        value_type timestamp_{0.};
        value_type samplerate_{0.};
        value_type sampling_period_{0.};
        value_type frequency_{1.};
        value_type phase_{0.};
    };

    template <typename T>
    constexpr Oscillator<T>::Oscillator(value_type amplitude, value_type samplerate, value_type frequency,
                                        value_type phase) noexcept :
        amplitude_(amplitude),
        samplerate_(samplerate),
        sampling_period_(math::inv(samplerate)),
        frequency_(frequency),
        phase_(phase) {}

    template <typename T>
    constexpr typename Oscillator<T>::value_type Oscillator<T>::timestamp() const noexcept {
        return timestamp_;
    }

    template <typename T>
    constexpr void Oscillator<T>::setTimestamp(value_type timestamp) noexcept {
        timestamp_ = timestamp;
    }

    template <typename T>
    constexpr void Oscillator<T>::reset() noexcept {
        timestamp_ = 0;
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type Oscillator<T>::samplerate() const noexcept {
        return samplerate_;
    }

    template <typename T>
    constexpr void Oscillator<T>::setSamplerate(value_type samplerate) noexcept {
        samplerate_ = samplerate;
        if (samplerate_ > 0) {
            sampling_period_ = 1. / samplerate_;
        }
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type Oscillator<T>::frequency() const noexcept {
        return frequency_;
    }

    template <typename T>
    constexpr void Oscillator<T>::setFrequency(value_type frequency) noexcept {
        frequency_ = frequency;
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type Oscillator<T>::phase() const noexcept {
        return phase_;
    }

    template <typename T>
    constexpr void Oscillator<T>::setPhase(value_type phase) noexcept {
        phase_ = phase;
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type Oscillator<T>::amplitude() const noexcept {
        return amplitude_;
    }

    template <typename T>
    constexpr void Oscillator<T>::setAmplitude(value_type amplitude) noexcept {
        amplitude_ = amplitude;
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type Oscillator<T>::samplingPeriod() const noexcept {
        return sampling_period_;
    }

}}} // namespace easy::dsp::oscillators

#endif // EASYDSP_OSCILLATOR_IMPL_HPP
