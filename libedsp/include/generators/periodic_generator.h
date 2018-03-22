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
#ifndef EDSP_GENERATORS_PERIODIC_GENERATOR_H
#define EDSP_GENERATORS_PERIODIC_GENERATOR_H

#include "time_series_generator.h

EDSP_BEGIN_NAMESPACE

    class PeriodicGenerator : public TimeSeriesGenerator {
    public:
        PeriodicGenerator();
        PeriodicGenerator(value_type amplitud, value_type samplerate, value_type frequency, value_type phase);
        ~PeriodicGenerator() override;

        EDSP_INLINE value_type frequency() const EDSP_NOEXCEPT;
        EDSP_INLINE value_type phase() const EDSP_NOEXCEPT;
        void set_frequency(value_type frequency) EDSP_NOEXCEPT;
        void set_phase(value_type phase) EDSP_NOEXCEPT;
    private:
        value_type frequency_{1};
        value_type phase_{0};
    };

    PeriodicGenerator::PeriodicGenerator() = default;

    PeriodicGenerator::~PeriodicGenerator() = default;

    PeriodicGenerator::PeriodicGenerator(Generator::value_type amplitud, Generator::value_type samplerate,
                                         Generator::value_type frequency_, Generator::value_type phase_)
            : TimeSeriesGenerator(amplitud, samplerate), frequency_(frequency_), phase_(phase_) {}

    Generator::value_type PeriodicGenerator::frequency() const EDSP_NOEXCEPT {
        return frequency_;
    }

    void PeriodicGenerator::set_frequency(Generator::value_type frequency) EDSP_NOEXCEPT {
        frequency_ = frequency;
    }

    Generator::value_type PeriodicGenerator::phase() const EDSP_NOEXCEPT {
        return phase_;
    }

    void PeriodicGenerator::set_phase(Generator::value_type phase) EDSP_NOEXCEPT {
        phase_ = phase;
    }



EDSP_END_NAMESPACE

#endif //EDSP_PERIODIC_GENERATOR_H
