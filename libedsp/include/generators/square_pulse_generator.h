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

#include "periodic_generator.h"
EDSP_BEGIN_NAMESPACE

/**
 * @brief Generate a square wave with the given %frequency and %amplitude samplet at %samplerate
 *
 * The parameter %duty defines the relative placement of the transition between the positive period and the
 * negative one
 */
class SquarePulseGenerator : public PeriodicGenerator {
public:

    /**
     * @brief Default constructor
     */
    SquarePulseGenerator();

    /**
     * @brief Creates an SquarePulseGenerator with the given configuration
     * @param amplitude
     * @param samplerate
     * @param frequency
     * @param duty
     */
    SquarePulseGenerator(value_type amplitude, value_type samplerate, value_type frequency, value_type duty);

    ~SquarePulseGenerator() override;

    /**
     * @brief Set the duty cycle.
     *
     * The duty cycle defines the relative placement of the transition between
     * the positives values and negative ones of the cycle.
     * @param dutty Value between 0 and 1
     */
    void set_duty_cycle(value_type dutty) EDSP_NOEXCEPT;

    /**
     * Return the duty cycle
     *
     * See also: set_duty_cycle
     * @return Value between 0 and 1
     */
    value_type duty_cycle() const EDSP_NOEXCEPT;

    /**
     * \brief Computes the output of the generator in the given timestamp
     *
     * @return Output of the generator
     */
    value_type operator()() EDSP_NOEXCEPT;

private:
    value_type duty_;
    value_type duty_t_;
};

EDSP_END_NAMESPACE
#endif //EDSP_GENERATORS_SQUARE_PULSE_GENERATOR_H
