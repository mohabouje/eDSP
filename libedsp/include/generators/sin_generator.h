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

#include "periodic_generator.h"

EDSP_BEGIN_NAMESPACE

/**
 * @brief Generate a periodic sinusoidal signal with the given %frecuency sampled at %samplerate.
 */
class SinGenerator : public PeriodicGenerator {
public:
    /**
     * @brief Created a SinGenerator with the defualt configuration
     */
    SinGenerator();

    /**
     * @brief Created a TriangularPulseGenerator with the given configuration
     * @param amplitude
     * @param samplerate
     * @param frequency
     * @param phase
     */
    SinGenerator(value_type amplitude, value_type samplerate, value_type frequency, value_type phase);
    ~SinGenerator() override;

    /**
     * \brief Computes the output of the generator in the given timestamp
     *
     * @return Output of the generator
     */
    value_type operator()() EDSP_NOEXCEPT;
};

EDSP_END_NAMESPACE

#endif //EDSP_SINGENERATOR_H
