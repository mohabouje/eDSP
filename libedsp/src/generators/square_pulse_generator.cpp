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
#include "generators/square_pulse_generator.h"
using namespace edsp;


void SquarePulseGenerator::set_duty_cycle(Generator::value_type dutty) EDSP_NOEXCEPT {
    duty_ = dutty;
    duty_t_ = dutty / frequency();
}

Generator::value_type SquarePulseGenerator::duty_cycle() const EDSP_NOEXCEPT {
    return duty_;
}

Generator::value_type SquarePulseGenerator::operator()() EDSP_NOEXCEPT {
    const auto t = timestamp();
    const value_type result = (t >= duty_t_) ? -1 : 1;
    const value_type increased = t + 1. / samplerate();
    set_timestamp((increased > 1. / frequency()) ? 0 : increased);
    return result * amplitude();
}

SquarePulseGenerator::SquarePulseGenerator(Generator::value_type amplitude,
                                           Generator::value_type samplerate,
                                           Generator::value_type frequency,
                                           Generator::value_type duty_)
    : PeriodicGenerator(amplitude, samplerate, frequency, 0.), duty_(duty_) {
}

SquarePulseGenerator::~SquarePulseGenerator() = default;

SquarePulseGenerator::SquarePulseGenerator() = default;
