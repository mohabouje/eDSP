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
* Filename: adsr.hpp
* Author: Mohammed Boujemaoui
* Date: 17/10/18
*/

#ifndef EDSP_ADSR_HPP
#define EDSP_ADSR_HPP

#include <numeric>
#include <cmath>
#include <functional>
#include <algorithm>

#include <edsp/meta/expects.hpp>

namespace edsp { namespace envelope {

    /**
     * @brief This class implements a traditional ADSR (Attack, Decay, Sustain, Release) envelope.
     */
    template <typename T>
    class adsr {
    public:
        using value_type = T;
        using size_type  = std::size_t;

        enum adsr_state { idle, attack, decay, sustain, release };

        constexpr adsr() = default;

        constexpr void key_on() {
            if (target_ <= 0.0)
                target_ = 1.0;
            state_ = adsr_state::attack;
        }

        constexpr void key_off() {
            target_ = 0.0;
            state_  = adsr_state::release;

            if (release_time_ > 0.0)
                release_rate_ = value_ / (release_time_ * sample_rate_);
        }

        constexpr value_type sample_rate() const {
            return sample_rate_;
        }

        constexpr value_type attack_rate() const {
            return attack_rate_;
        }

        constexpr value_type release_rate() const {
            return release_time_;
        }

        constexpr value_type decay_rate() const {
            return decay_rate_;
        }

        constexpr value_type attack_target() const {
            return target_;
        }

        constexpr value_type sustain_level() const {
            return sustain_level_;
        }

        constexpr value_type attack_time() const {
            return 1.0 / (attack_rate_ * sample_rate_);
        }

        constexpr value_type decay_time() const {
            return (1.0 - sustain_level_) / (decay_rate_ * sample_rate_);
        }

        constexpr value_type release_time() const {
            return release_time_;
        }

        constexpr void set_attack_target(value_type attack_target) {
            meta::expects(attack_target >= 0, "Negative target not allowed");
            target_ = attack_target > 0.000000001 ? attack_target : 0.000000001; // -180 dB;
        }

        constexpr void set_attack_rate(value_type attack_rate) {
            meta::expects(attack_rate >= 0, "Negative rate not allowed");
            attack_rate_ = attack_rate;
        }

        constexpr void set_decay_rate(value_type decay_rate) {
            meta::expects(decay_rate >= 0, "Negative rate not allowed");
            decay_rate_ = decay_rate;
        }

        constexpr void set_sustain_level(value_type sustain_level) {
            meta::expects(sustain_level >= 0, "Negative levels not allowed");
            sustain_level_ = sustain_level;
        }

        constexpr void set_release_rate(value_type release_rate) {
            meta::expects(release_rate >= 0, "Negative levels not allowed");
            release_rate_ = release_rate;
            release_time_ = -1.0;
        }

        constexpr void set_attack_time(value_type attack_time) {
            meta::expects(attack_time > 0, "Requires strictly positive integer");
            attack_rate_ = 1.0 / (attack_time * sample_rate_);
        }

        constexpr void set_decay_time(value_type decay_time) {
            meta::expects(decay_time > 0, "Requires strictly positive integer");
            decay_rate_ = (1.0 - sustain_level_) / (decay_time * sample_rate_);
        }

        constexpr void set_release_time(value_type release_time) {
            meta::expects(release_time > 0, "Requires strictly positive integer");
            release_rate_ = sustain_level_ / (release_time * sample_rate_);
            release_time_ = release_time;
        }

        constexpr void set_target(value_type target) {
            target_ = target > 0.000000001 ? target : 0.000000001; // -180 dB;
            set_sustain_level(target_);
            if (value_ < target_)
                state_ = adsr_state::attack;
            else if (value_ > target_)
                state_ = adsr_state ::decay;
        }

        constexpr void set_sample_rate(value_type sample_rate) {
            auto old_rate = sample_rate_;
            sample_rate_  = sample_rate;
            attack_rate_  = old_rate * attack_rate_ / sample_rate;
            decay_rate_   = old_rate * decay_rate_ / sample_rate;
            release_rate_ = old_rate * release_rate_ / sample_rate;
        }

        constexpr value_type operator()(value_type input) {
            switch (state_) {
                case adsr_state::attack:
                    value_ += attack_rate_;
                    if (value_ >= target_) {
                        value_  = target_;
                        target_ = sustain_level_;
                        state_  = adsr_state::decay;
                    }
                    break;
                case adsr_state::decay:
                    if (value_ > sustain_level_) {
                        value_ -= decay_rate_;
                        if (value_ <= sustain_level_) {
                            value_ = sustain_level_;
                            state_ = adsr_state::sustain;
                        }
                    } else {
                        value_ += decay_rate_; // attack target < sustain level
                        if (value_ >= sustain_level_) {
                            value_ = sustain_level_;
                            state_ = adsr_state::sustain;
                        }
                    }
                    break;
                case adsr_state::release:
                    value_ -= release_rate_;
                    if (value_ <= 0.0) {
                        value_ = 0.0;
                        state_ = adsr_state::idle;
                    }
                    break;
                default:
                    break;
            }
            return value_ * input;
        }

        template <typename InIterator, typename OutputIt>
        constexpr void apply(InIterator first, InIterator last, OutputIt d_first) {
            std::transform(first, last, d_first, std::ref(*this));
        }

    private:
        adsr_state state_{adsr_state::idle};
        value_type sample_rate_{44100};
        value_type target_{0.0};
        value_type value_{0.0};
        value_type attack_rate_{0.001};
        value_type decay_rate_{0.001};
        value_type release_rate_{0.001};
        value_type release_time_{-1.0};
        value_type sustain_level_{0.5};
    };

}} // namespace edsp::envelope

#endif //EDSP_ADSR_HPP
