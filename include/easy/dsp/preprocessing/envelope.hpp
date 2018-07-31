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
 * Filename: envelope.hpp
 * Author: Mohammed Boujemaoui
 * Date: 14/6/2018
 */
#ifndef EASYDSP_FEATURE_TEMPORAL_ENVELOPE_HPP
#define EASYDSP_FEATURE_TEMPORAL_ENVELOPE_HPP

#include <easy/meta/math.hpp>
#include <numeric>
#include <cmath>

namespace easy { namespace dsp {

    template <typename T>
    class Envelope {
    public:
        using value_type = T;
        using size_type  = std::size_t;

        constexpr Envelope(value_type samplerate, value_type attack_time, value_type release_time,
                             bool rectify = false) noexcept;
        constexpr value_type samplerate() const noexcept;
        constexpr void set_samplerate(value_type samplerate) noexcept;
        constexpr value_type attack_time() const noexcept;
        constexpr void set_attack_time(value_type attack_time) noexcept;
        constexpr value_type release_time() const noexcept;
        constexpr void set_release_time(value_type release_time) noexcept;
        constexpr bool is_rectification_enabled() const noexcept;
        constexpr void enable_rectification(bool enabled) noexcept;
        constexpr void reset() noexcept;

        template <typename BiIterator>
        constexpr void apply(BiIterator first, BiIterator last);

        template <typename InputIterator, typename OutputIterator>
        constexpr void apply(InputIterator first, InputIterator last, OutputIterator out);

    private:
        value_type samplerate_{44100};
        value_type attack_time_{10};
        value_type attack_gain_{0};
        value_type release_time_{1500};
        value_type release_gain_{0};
        value_type last_{0};
        bool rectification_{false};
    };

    template <typename T>
    constexpr Envelope<T>::Envelope(value_type samplerate, value_type attack_time, value_type release_time,
                                      bool rectify) noexcept : samplerate_(samplerate),
                                                                 attack_time_(attack_time),
                                                                 release_time_(release_time),
                                                                 rectification_(rectify) {
        reset();
    }

    template <typename T>
    constexpr typename Envelope<T>::value_type Envelope<T>::samplerate() const noexcept {
        return samplerate_;
    }

    template <typename T>
    constexpr void Envelope<T>::set_samplerate(value_type samplerate) noexcept {
        samplerate_ = samplerate;
        reset();
    }

    template <typename T>
    constexpr typename Envelope<T>::value_type Envelope<T>::attack_time() const noexcept {
        return attack_time_;
    }

    template <typename T>
    constexpr void Envelope<T>::set_attack_time(value_type attack_time) noexcept {
        attack_time_ = attack_time;
        reset();
    }

    template <typename T>
    constexpr typename Envelope<T>::value_type Envelope<T>::release_time() const noexcept {
        return release_time_;
    }

    template <typename T>
    constexpr void Envelope<T>::set_release_time(value_type release_time) noexcept {
        release_time_ = release_time;
        reset();
    }

    template <typename T>
    constexpr bool Envelope<T>::is_rectification_enabled() const noexcept {
        return rectification_;
    }

    template <typename T>
    constexpr void Envelope<T>::enable_rectification(bool enabled) noexcept {
        rectification_ = enabled;
    }

    template <typename T>
    constexpr void Envelope<T>::reset() noexcept {
        attack_gain_  = (attack_gain_ > 0) ? static_cast<value_type>(std::exp(-1 / (attack_time_ * samplerate_))) : 0;
        release_gain_ = (release_gain_ > 0) ? static_cast<value_type>(std::exp(-1 / (release_time_ * samplerate_))) : 0;
        last_         = 0;
    }

    template <typename T>
    template <typename BiIterator>
    constexpr void Envelope<T>::apply(BiIterator first, BiIterator last) {
        apply(first, last, first);
    }

    template <typename T>
    template <typename InputIterator, typename OutputIterator>
    constexpr void Envelope<T>::apply(InputIterator first, InputIterator last, OutputIterator out) {
        for (; first != last; ++first, ++out) {
            const auto rectified = rectification_ ? std::abs(*first) : *first;
            const auto current   = (last_ < rectified) ? (1 - attack_gain_) * rectified + attack_gain_ * last_
                                                     : (1 - release_gain_) * rectified + release_gain_ * last_;
            last_ = meta::is_denormal(current) ? 0 : current;
            *out  = last_;
        }
    }

}} // namespace easy::dsp

#endif // EASYDSP_FEATURE_TEMPORAL_ENVELOPE_HPP
