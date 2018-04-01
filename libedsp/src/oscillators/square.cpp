/*
 * eDSP, A cross-platform DSP framework written in C++.
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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "oscillators/square.h"
using namespace edsp;


void SquareOscillator::set_duty_cycle(Oscillator::value_type dutty) EDSP_NOEXCEPT {
    duty_ = dutty;
    duty_t_ = dutty / frequency();
}

Oscillator::value_type SquareOscillator::duty_cycle() const EDSP_NOEXCEPT {
    return duty_;
}

Oscillator::value_type SquareOscillator::operator()() EDSP_NOEXCEPT {
    const auto t = timestamp();
    const value_type result = (t >= duty_t_) ? -1 : 1;
    const value_type increased = t + sampling_period();
    set_timestamp((increased > 1. / frequency()) ? 0 : increased);
    return result * amplitude();
}

SquareOscillator::SquareOscillator(Oscillator::value_type amplitude,
                                           Oscillator::value_type samplerate,
                                           Oscillator::value_type frequency,
                                           Oscillator::value_type duty_)
    : Oscillator(amplitude, samplerate, frequency, 0.), duty_(duty_) {
}

SquareOscillator::~SquareOscillator() = default;

SquareOscillator::SquareOscillator() = default;
