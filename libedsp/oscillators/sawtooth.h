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
public:

    SawtoothOscillator();
    SawtoothOscillator(value_type amplitude, value_type samplerate, value_type frequency, value_type width_);
    ~SawtoothOscillator() override;

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
    void set_width(value_type width) EDSP_NOEXCEPT;

    /**
     * \brief Return the width of the pulse over the interval \f$ \frac{1}{F} \f$
     * @return Value between 0 and 1
     */
    value_type width() const EDSP_NOEXCEPT;

    value_type operator()() EDSP_NOEXCEPT;
private:
    value_type width_{1};
};

EDSP_END_NAMESPACE
#endif //EDSP_GENERATORS_SAWTOOTH_GENERATOR_H
