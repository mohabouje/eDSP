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
 * Filename: envelope_follower.hpp
 * Author: Mohammed Boujemaoui
 * Date: 14/6/2018
 */
#ifndef EASYDSP_FEATURE_TEMPORAL_EnvelopeFollower_HPP
#define EASYDSP_FEATURE_TEMPORAL_EnvelopeFollower_HPP

#include <easy/dsp/math/math.hpp>
#include <numeric>
#include <cmath>

namespace easy { namespace dsp {

    /**
     * @class EnvelopeFollower
     * @brief This class implements a basic Envelope Follower
     *
     * The envelope follower takes an high-frequency signal as input and provides an output which is
     * the envelope of the original signal. It is frequently used  to detect the amplitude variations of an incoming signal to produce a
     * control signal that resembles those variations.
     *
     * This class implements a basic Envelope Follower based in a non-symmetric lowpass filter.
     * The output of a low-pass filter can be viewed as a moving average of its input.  A minimal envelope generator has an attack period,
     * in which the level of the envelope rises from an initial zero level to a maximum level, followed by a release phase,in which the level
     * falls back to zero.     *
     */
    template <typename T>
    class EnvelopeFollower {
    public:
        using value_type = T;
        using size_type  = std::size_t;

        /**
         * @brief Creates an EnvelopeFollower object class
         * @param samplerate The sample rate in Hz.
         * @param attackTime The attack time of the first order lowpass in the attack phase in msecs.
         * @param releaseTime The release time of the first order lowpass in the attack phase in msecs.
         * @param rectify If true, enables the rectification of the output signal.
         */
        constexpr EnvelopeFollower(value_type samplerate, value_type attackTime, value_type releaseTime,
                                   bool rectify = false) noexcept;

        /**
         * @brief Returns the sample rate in Hz.
         * @return Sample rate in Hz.
         */
        constexpr value_type sampleRate() const noexcept;

        /**
         * @brief Sets the sample rate in Hz and resets the internal parameters.
         * @param samplerate Sample rate in Hz.
         */
        constexpr void setSampleRate(value_type samplerate) noexcept;

        /**
         * @brief Returns the attack time of the first order lowpass in the attack phase.
         * @return Attack time in msecs.
         */
        constexpr value_type attackTime() const noexcept;

        /**
         * @brief Set the the attack time of the first order lowpass in the attack phase.
         * @param attackTime Attack time in msecs.
         */
        constexpr void setAttackTime(value_type attackTime) noexcept;

        /**
         * @brief Returns the release time of the first order lowpass in the release phase.
         * @return Release time in msecs.
         */
        constexpr value_type releaseTime() const noexcept;

        /**
         * @brief Set the the release time of the first order lowpass in the attack phase.
         * @param releaseTime Release time in msecs.
         */
        constexpr void setReleaseTime(value_type releaseTime) noexcept;

        /**
         * @brief Checks if the rectification is enabled
         * @return true if the rectification is enabled, false otherwise.
         */
        constexpr bool isRectificationEnabled() const noexcept;

        /**
         * @brief Enables the rectification of the output signal.
         *
         * If the rectification is enabled, the envelope-follower is based on the absolute value of signal
         * @param enabled State of the rectification.
         */
        constexpr void enableRectification(bool enabled) noexcept;

        /**
         * @brief Resets the temporal an internal data.
         */
        constexpr void reset() noexcept;

        /**
         * @brief Computes the envelope of the element's value in the range [first, last),
         * and stores the result in another range, beginning at d_first.
         *
         * @param first Input iterator defining the beginning of the input range.
         * @param last Input iterator defining the ending of the input range.
         * @param d_first Output iterator defining the beginning of the destination range.
         */
        template <typename InIterator, typename OutIterator>
        constexpr void apply(InIterator first, InIterator last, OutIterator d_first);

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
    constexpr EnvelopeFollower<T>::EnvelopeFollower(value_type samplerate, value_type attack_time,
                                                    value_type release_time, bool rectify) noexcept :
        samplerate_(samplerate),
        attack_time_(attack_time),
        release_time_(release_time),
        rectification_(rectify) {
        reset();
    }

    template <typename T>
    constexpr typename EnvelopeFollower<T>::value_type EnvelopeFollower<T>::sampleRate() const noexcept {
        return samplerate_;
    }

    template <typename T>
    constexpr void EnvelopeFollower<T>::setSampleRate(value_type samplerate) noexcept {
        samplerate_ = samplerate;
        reset();
    }

    template <typename T>
    constexpr typename EnvelopeFollower<T>::value_type EnvelopeFollower<T>::attackTime() const noexcept {
        return attack_time_;
    }

    template <typename T>
    constexpr void EnvelopeFollower<T>::setAttackTime(value_type attack_time) noexcept {
        attack_time_ = attack_time;
        reset();
    }

    template <typename T>
    constexpr typename EnvelopeFollower<T>::value_type EnvelopeFollower<T>::releaseTime() const noexcept {
        return release_time_;
    }

    template <typename T>
    constexpr void EnvelopeFollower<T>::setReleaseTime(value_type release_time) noexcept {
        release_time_ = release_time;
        reset();
    }

    template <typename T>
    constexpr bool EnvelopeFollower<T>::isRectificationEnabled() const noexcept {
        return rectification_;
    }

    template <typename T>
    constexpr void EnvelopeFollower<T>::enableRectification(bool enabled) noexcept {
        rectification_ = enabled;
    }

    template <typename T>
    constexpr void EnvelopeFollower<T>::reset() noexcept {
        attack_gain_  = (attack_gain_ > 0) ? static_cast<value_type>(std::exp(-1 / (attack_time_ * samplerate_))) : 0;
        release_gain_ = (release_gain_ > 0) ? static_cast<value_type>(std::exp(-1 / (release_time_ * samplerate_))) : 0;
        last_         = 0;
    }

    template <typename T>
    template <typename InIterator, typename OutIterator>
    constexpr void EnvelopeFollower<T>::apply(InIterator first, InIterator last, OutIterator d_first) {
        for (; first != last; ++first, ++d_first) {
            const auto rectified = rectification_ ? std::abs(*first) : *first;
            const auto current   = (last_ < rectified) ? (1 - attack_gain_) * rectified + attack_gain_ * last_
                                                     : (1 - release_gain_) * rectified + release_gain_ * last_;
            last_    = math::is_denormal(current) ? 0 : current;
            *d_first = last_;
        }
    }

}} // namespace easy::dsp

#endif // EASYDSP_FEATURE_TEMPORAL_EnvelopeFollower_HPP
