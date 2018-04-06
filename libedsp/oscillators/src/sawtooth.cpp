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
#include "oscillators/sawtooth.h"
using namespace edsp;

Oscillator::value_type SawtoothOscillator::width() const EDSP_NOEXCEPT {
    return width_;
}

void SawtoothOscillator::set_width(Oscillator::value_type width) EDSP_NOEXCEPT {
    width_ = width;
}

Oscillator::value_type SawtoothOscillator::operator()() EDSP_NOEXCEPT {
    const auto t = timestamp();
    const value_type result = (t >= width_) ? -2 * t / (1 - width_) + 1
                                            : 2 * t / width_ - 1;
    const value_type increased = t + sampling_period();
    set_timestamp((increased > 1. / frequency()) ? 0 : increased);
    return result * amplitude();
}

SawtoothOscillator::SawtoothOscillator() = default;

SawtoothOscillator::~SawtoothOscillator() = default;

SawtoothOscillator::SawtoothOscillator(Oscillator::value_type amplitude,
                                     Oscillator::value_type samplerate,
                                     Oscillator::value_type frequency,
                                     Oscillator::value_type width)
    : Oscillator(amplitude, samplerate, frequency, 0.), width_(width) {}
