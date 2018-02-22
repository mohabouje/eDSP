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
#include "oscillators/sin.h"
#include "base/constants.h"
#include <cmath>
using namespace edsp;

SinOscillator::SinOscillator() = default;

SinOscillator::~SinOscillator() = default;

SinOscillator::SinOscillator(Oscillator::value_type amplitude, Oscillator::value_type samplerate,
                           Oscillator::value_type frequency, Oscillator::value_type phase) : Oscillator(amplitude,
                                                                                                             samplerate,
                                                                                                             frequency,
                                                                                                             phase) {

}

Oscillator::value_type SinOscillator::operator()() EDSP_NOEXCEPT {
    const value_type result = std::sin(2 * constants<value_type>::pi  * (frequency() * timestamp() + phase()));
    set_timestamp(timestamp() + sampling_period());
    return result;}


