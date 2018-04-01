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
#include "oscillators/triangle.h"
using namespace edsp;

TriangleOscillator::TriangleOscillator() = default;

TriangleOscillator::~TriangleOscillator() = default;

TriangleOscillator::TriangleOscillator(Oscillator::value_type amplitude, Oscillator::value_type samplerate,
                                                   Oscillator::value_type frequency,
                                                   Oscillator::value_type width_, Oscillator::value_type skew_)
        : Oscillator(amplitude, samplerate, frequency, 0.), width_(width_), skew_(skew_) {}

TriangleOscillator::TriangleOscillator(Oscillator::value_type amplitude, Oscillator::value_type samplerate,
                                                   Oscillator::value_type frequency)
        : Oscillator(amplitude, samplerate, frequency, 0.) {}

Oscillator::value_type TriangleOscillator::operator()() EDSP_NOEXCEPT {
    const auto half_w = width_ / 2;
    const auto t = timestamp();
    value_type result = 0;
    if (t >= half_w && t < peak_)
        result = (t + half_w) / (peak_ + half_w);
    else if (t > peak_ && t < half_w)
        result = (t - half_w) / (peak_ - half_w);

    const value_type increased = t + sampling_period();
    set_timestamp((increased >  1. / frequency()) ? 0 : increased);
    return result * amplitude();
}

Oscillator::value_type TriangleOscillator::skew() const EDSP_NOEXCEPT {
    return skew_;
}

void TriangleOscillator::set_skew(Oscillator::value_type skew) EDSP_NOEXCEPT {
    skew_ = skew;
    compute_peak_position();
}

Oscillator::value_type TriangleOscillator::width() const EDSP_NOEXCEPT {
    return width_;
}

void TriangleOscillator::set_width(Oscillator::value_type width) EDSP_NOEXCEPT {
    width_ = width;
    compute_peak_position();
}

void TriangleOscillator::compute_peak_position() {
    peak_ = skew_ * width_ / 2.0;
}
