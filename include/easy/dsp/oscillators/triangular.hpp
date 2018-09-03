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
 * Filename: triangular.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_OSCILLATOR_TRIANGLE_HPP
#define EASYDSP_OSCILLATOR_TRIANGLE_HPP

#include "easy/dsp/oscillators/oscillator_impl.hpp"
#include "easy/dsp/math/constant.hpp"

namespace easy { namespace dsp { namespace oscillators {

    template <typename T>
    class TriangularOscillator : public Oscillator<T> {
    public:
        using value_type = typename Oscillator<T>::value_type;
        constexpr TriangularOscillator(value_type amplitude, value_type samplerate, value_type frequency,
                                       value_type width, value_type skew) noexcept;
        constexpr value_type operator()();
        constexpr void set_width(value_type width) noexcept;
        constexpr value_type width() const noexcept;
        constexpr void set_skew(value_type skew) noexcept;
        constexpr value_type skew() const noexcept;

    private:
        value_type width_{0.3};
        value_type skew_{0};
        value_type peak_{0};
        constexpr void compute_peak_position();
    };

    template <typename T>
    constexpr TriangularOscillator<T>::TriangularOscillator(value_type amplitude, value_type samplerate,
                                                            value_type frequency, value_type width,
                                                            value_type skew) noexcept :
        Oscillator<T>(amplitude, samplerate, frequency, 0),
        width_(width),
        skew_(skew) {}

    template <typename T>
    constexpr typename Oscillator<T>::value_type TriangularOscillator<T>::operator()() {
        const auto half_w = width_ / 2;
        const auto t      = Oscillator<T>::timestamp();
        value_type result = 0;
        if (t >= half_w && t < peak_) {
            result = (t + half_w) / (peak_ + half_w);
        } else if (t > peak_ && t < half_w) {
            result = (t - half_w) / (peak_ - half_w);
        }

        const value_type increased = t + Oscillator<T>::samplingPeriod();
        this->setTimestamp((increased > 1. / Oscillator<T>::frequency()) ? 0 : increased);
        return result * Oscillator<T>::amplitude();
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type TriangularOscillator<T>::skew() const noexcept {
        return skew_;
    }

    template <typename T>
    constexpr void TriangularOscillator<T>::set_skew(value_type skew) noexcept {
        skew_ = skew;
        compute_peak_position();
    }

    template <typename T>
    constexpr typename Oscillator<T>::value_type TriangularOscillator<T>::width() const noexcept {
        return width_;
    }

    template <typename T>
    constexpr void TriangularOscillator<T>::set_width(value_type width) noexcept {
        width_ = width;
        compute_peak_position();
    }

    template <typename T>
    constexpr void TriangularOscillator<T>::compute_peak_position() {
        peak_ = skew_ * width_ / static_cast<T>(2);
    }

}}} // namespace easy::dsp::oscillators

#endif // EASYDSP_OSCILLATOR_TRIANGLE_HPP
