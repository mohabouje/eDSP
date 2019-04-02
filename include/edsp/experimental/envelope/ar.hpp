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
 * File: ar.hpp
 * Author: Mohammed Boujemaoui
 * Date: 14/6/2018
 */
#ifndef EDSP_FEATURE_TEMPORAL_EnvelopeFollower_HPP
#define EDSP_FEATURE_TEMPORAL_EnvelopeFollower_HPP

#include <edsp/math/numeric.hpp>
#include <numeric>
#include <cmath>
#include <functional>
#include <algorithm>

namespace edsp { namespace envelope {

    /**
     * @brief This class implements a traditional AR (Attack, Release) envelope.
     *
     * The envelope follower takes an high-frequency signal as input and provides an output which is
     * the envelope of the original signal. It is frequently used  to detect the amplitude variations of an incoming signal to produce a
     * control signal that resembles those variations.
     *
     * This class implements a basic Envelope Follower based in a non-symmetric low pass filter.
     * The output of a low-pass filter can be viewed as a moving average of its input.
     *
     * This minimal envelope generator has an attack period, in which the level of the envelope rises from an initial zero level to a maximum
     * level, followed by a release phase,in which the level falls back to zero.
     */
    template <typename T>
    class ar {
    public:
        using value_type = T;
        using size_type  = std::size_t;

        /**
         * @brief Creates an EnvelopeFollower object class
         * @param sample_rate The sample rate in Hz.
         * @param attackTime The attack time of the first order lowpass in the attack phase in msecs.
         * @param releaseTime The release time of the first order lowpass in the attack phase in msecs.
         * @param rectify If true, enables the rectification of the output signal.
         */
        constexpr ar(value_type sample_rate, value_type attackTime, value_type releaseTime,
                     bool rectify = false) noexcept;

        /**
         * @brief Returns the sample rate in Hz.
         * @return Sample rate in Hz.
         */
        constexpr value_type sample_rate() const noexcept;

        /**
         * @brief Sets the sample rate in Hz and resets the internal parameters.
         * @param sample_rate Sample rate in Hz.
         */
        constexpr void set_sample_rate(value_type sample_rate) noexcept;

        /**
         * @brief Returns the attack time of the first order lowpass in the attack phase.
         * @return Attack time in msecs.
         */
        constexpr value_type attack_time() const noexcept;

        /**
         * @brief Set the the attack time of the first order lowpass in the attack phase.
         * @param attackTime Attack time in msecs.
         */
        constexpr void set_attack_time(value_type attackTime) noexcept;

        /**
         * @brief Returns the release time of the first order lowpass in the release phase.
         * @return Release time in msecs.
         */
        constexpr value_type release_time() const noexcept;

        /**
         * @brief Set the the release time of the first order lowpass in the attack phase.
         * @param releaseTime Release time in msecs.
         */
        constexpr void set_release_time(value_type releaseTime) noexcept;

        /**
         * @brief Checks if the rectification is enabled
         * @return true if the rectification is enabled, false otherwise.
         */
        constexpr bool rectification() const noexcept;

        /**
         * @brief Enables the rectification of the output signal.
         *
         * If the rectification is enabled, the envelope-follower is based on the absolute value of signal
         * @param enabled State of the rectification.
         */
        constexpr void set_rectification(bool enabled) noexcept;

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
        template <typename InIterator, typename OutputIt>
        constexpr void apply(InIterator first, InIterator last, OutputIt d_first);

        /**
         * @brief Computes the envelope of the element
         * @param value Input element.
         * @return Compute envelope value.
         */
        constexpr value_type operator()(value_type value);

    private:
        value_type sample_rate_{44100};
        value_type attack_time_{10};
        value_type attack_gain_{0};
        value_type release_time_{1500};
        value_type release_gain_{0};
        value_type last_{0};
        bool rectification_{false};
    };

    template <typename T>
    constexpr ar<T>::ar(value_type sample_rate, value_type attack_time, value_type release_time,
                        bool rectify) noexcept :
        sample_rate_(sample_rate),
        attack_time_(attack_time),
        release_time_(release_time),
        rectification_(rectify) {
        reset();
    }

    template <typename T>
    constexpr typename ar<T>::value_type ar<T>::sample_rate() const noexcept {
        return sample_rate_;
    }

    template <typename T>
    constexpr void ar<T>::set_sample_rate(value_type sample_rate) noexcept {
        sample_rate_ = sample_rate;
        reset();
    }

    template <typename T>
    constexpr typename ar<T>::value_type ar<T>::attack_time() const noexcept {
        return attack_time_;
    }

    template <typename T>
    constexpr void ar<T>::set_attack_time(value_type attack_time) noexcept {
        attack_time_ = attack_time;
        reset();
    }

    template <typename T>
    constexpr typename ar<T>::value_type ar<T>::release_time() const noexcept {
        return release_time_;
    }

    template <typename T>
    constexpr void ar<T>::set_release_time(value_type release_time) noexcept {
        release_time_ = release_time;
        reset();
    }

    template <typename T>
    constexpr bool ar<T>::rectification() const noexcept {
        return rectification_;
    }

    template <typename T>
    constexpr void ar<T>::set_rectification(bool enabled) noexcept {
        rectification_ = enabled;
    }

    template <typename T>
    constexpr void ar<T>::reset() noexcept {
        attack_gain_ = (attack_gain_ > 0) ? static_cast<value_type>(std::exp(-1 / (attack_time_ * sample_rate_))) : 0;
        release_gain_ =
            (release_gain_ > 0) ? static_cast<value_type>(std::exp(-1 / (release_time_ * sample_rate_))) : 0;
        last_ = 0;
    }

    template <typename T>
    template <typename InIterator, typename OutputIt>
    constexpr void ar<T>::apply(InIterator first, InIterator last, OutputIt d_first) {
        std::transform(first, last, d_first, std::ref(*this));
    }

    template <typename T>
    constexpr typename ar<T>::value_type ar<T>::operator()(value_type value) {
        const auto rectified = rectification_ ? std::abs(value) : value;
        const auto current   = (last_ < rectified) ? (1 - attack_gain_) * rectified + attack_gain_ * last_
                                                 : (1 - release_gain_) * rectified + release_gain_ * last_;
        last_ = math::is_denormal(current) ? 0 : current;
        return last_;
    }

}} // namespace edsp::envelope

#endif // EDSP_FEATURE_TEMPORAL_EnvelopeFollower_HPP
