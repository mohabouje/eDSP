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
#ifndef EDSP_GENERATORS_SINGENERATOR_H
#define EDSP_GENERATORS_SINGENERATOR_H

#include "oscillator.h"
#include "base/constants.h"
#include <cmath>

EDSP_BEGIN_NAMESPACE

/**
 * @brief Generate a periodic sinusoidal signal with the given %frecuency sampled at %samplerate.
 */
class SinOscillator : public Oscillator {
    EDSP_DEFINE_IMPLICITS(SinOscillator)
public:
    /**
     * @brief Created a SinGenerator with the defualt configuration
     */
    SinOscillator();

    /**
     * @brief Created a TriangularPulseGenerator with the given configuration
     * @param amplitude
     * @param samplerate
     * @param frequency
     * @param phase
     */
    SinOscillator(_In_ value_type amplitude, _In_ value_type samplerate, _In_ value_type frequency, _In_ value_type phase);

    ~SinOscillator() EDSP_OVERRIDE;

    /**
     * \brief Computes the output of the generator in the given timestamp
     *
     * @return Output of the generator
     */
    EDSP_INLINE value_type operator()() EDSP_NOEXCEPT;
};

SinOscillator::SinOscillator() = default;

SinOscillator::~SinOscillator() = default;

SinOscillator::SinOscillator(_In_ Oscillator::value_type amplitude, _In_ Oscillator::value_type samplerate,
                           _In_ Oscillator::value_type frequency, _In_ Oscillator::value_type phase) : Oscillator(amplitude,
                                                                                                             samplerate,
                                                                                                             frequency,
                                                                                                             phase) {

}

Oscillator::value_type SinOscillator::operator()() EDSP_NOEXCEPT {
    const value_type result = std::sin(2 * constants<value_type>::pi  * (frequency() * timestamp() + phase()));
    set_timestamp(timestamp() + sampling_period());
    return result;
}


EDSP_END_NAMESPACE

#endif //EDSP_SINGENERATOR_H
