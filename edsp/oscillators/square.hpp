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
#ifndef EDSP_GENERATORS_SQUARE_PULSE_GENERATOR_H
#define EDSP_GENERATORS_SQUARE_PULSE_GENERATOR_H

#include "oscillator.h"
EDSP_BEGIN_NAMESPACE

/**
 * @brief Generate a square wave with the given %frequency and %amplitude sampled at %samplerate
 *
 * The parameter %duty defines the relative placement of the transition between the positive period and the
 * negative one
 */
class SquareOscillator : public Oscillator {
    EDSP_DEFINE_IMPLICITS(SquareOscillator)
public:

    /**
     * @brief Default constructor
     */
    SquareOscillator();

    /**
     * @brief Creates an SquarePulseGenerator with the given configuration
     * @param amplitude
     * @param samplerate
     * @param frequency
     * @param duty
     */
    SquareOscillator(_In_ value_type amplitude, _In_ value_type samplerate, _In_ value_type frequency, _In_ value_type duty);

    ~SquareOscillator() EDSP_OVERRIDE;

    /**
     * @brief Set the duty cycle.
     *
     * The duty cycle defines the relative placement of the transition between
     * the positives values and negative ones of the cycle.
     * @param dutty Value between 0 and 1
     */
    EDSP_INLINE void set_duty_cycle(_In_ value_type dutty) EDSP_NOEXCEPT;

    /**
     * Return the duty cycle
     *
     * See also: set_duty_cycle
     * @return Value between 0 and 1
     */
    EDSP_INLINE value_type duty_cycle() const EDSP_NOEXCEPT;

    /**
     * \brief Computes the output of the generator in the given timestamp
     *
     * @return Output of the generator
     */
    EDSP_INLINE value_type operator()() EDSP_NOEXCEPT;

private:
    value_type duty_ = 0;
    value_type duty_t_ = 0;
};

void SquareOscillator::set_duty_cycle(_In_ Oscillator::value_type dutty) EDSP_NOEXCEPT {
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

SquareOscillator::SquareOscillator(_In_ Oscillator::value_type amplitude,
                                           _In_ Oscillator::value_type samplerate,
                                           _In_ Oscillator::value_type frequency,
                                           _In_ Oscillator::value_type duty)
    : Oscillator(amplitude, samplerate, frequency, 0.), duty_(duty), duty_t_(duty / frequency) {
}

SquareOscillator::~SquareOscillator() = default;

SquareOscillator::SquareOscillator() = default;

EDSP_END_NAMESPACE
#endif //EDSP_GENERATORS_SQUARE_PULSE_GENERATOR_H
