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
#ifndef EDSP_GENERATORS_SAWTOOTH_GENERATOR_H
#define EDSP_GENERATORS_SAWTOOTH_GENERATOR_H

#include "oscillator.h"

EDSP_BEGIN_NAMESPACE

/**
 * @brief Generate a sawtooth wave of a given %frequency sampled with %samplerate
 */
class SawtoothOscillator : public Oscillator {
    EDSP_DEFINE_IMPLICITS(SawtoothOscillator)
public:
    SawtoothOscillator();
    SawtoothOscillator(_In_ value_type amplitude, _In_ value_type samplerate, _In_ value_type frequency, _In_ value_type width);
    ~SawtoothOscillator() EDSP_OVERRIDE;

    /**
     * @brief Set the width of the pulse over the interval \f$ \frac{1}{F} \f$
     *
     * The width defined the portion of the interval \f$ \frac{1}{Fs} \f$ that
     * stores the pulse.
     *
     * Default Value: 1
     *
     * @param width Value between 0 and 1
     */
    EDSP_INLINE void set_width(_In_ value_type width) EDSP_NOEXCEPT;

    /**
     * \brief Return the width of the pulse over the interval \f$ \frac{1}{F} \f$
     * @return Value between 0 and 1
     */
    EDSP_INLINE value_type width() const EDSP_NOEXCEPT;

    EDSP_INLINE value_type operator()() EDSP_NOEXCEPT;
private:
    value_type width_{1};
};

Oscillator::value_type SawtoothOscillator::width() const EDSP_NOEXCEPT {
    return width_;
}

void SawtoothOscillator::set_width(_In_ Oscillator::value_type width) EDSP_NOEXCEPT {
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

SawtoothOscillator::SawtoothOscillator(_In_ Oscillator::value_type amplitude,
                                     _In_ Oscillator::value_type samplerate,
                                     _In_ Oscillator::value_type frequency,
                                     _In_ Oscillator::value_type width)
    : Oscillator(amplitude, samplerate, frequency, 0.), width_(width) {}


EDSP_END_NAMESPACE
#endif //EDSP_GENERATORS_SAWTOOTH_GENERATOR_H
