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
#ifndef EDSP_GENERATORS_TIME_SERIES_GENERATOR_H
#define EDSP_GENERATORS_TIME_SERIES_GENERATOR_H

#include "generator.h"

EDSP_BEGIN_NAMESPACE

    /**
     * @brief Base class for generators based in discrete time series.
     *
     * The class introduce an abstraction to manage the current timestamp of the signal
     * and the sample rate.
     */
    class TimeSeriesGenerator : public Generator {

    public:
        /**
         * @brief Default constructor
         */
        TimeSeriesGenerator();

        /**
         * @brief Created a TimeSeriesGenerator with the given amplitude and samplerate.
         * @param amplitude
         * @param samplerate
         */
        TimeSeriesGenerator(value_type amplitude, value_type samplerate);

        ~TimeSeriesGenerator() override;

        /**
         * @brief Reset the generator to initial timestamp..
         */
        void reset() EDSP_NOEXCEPT;

        /**
         * @brief Returns the current timestamp
         * @return
         */
        EDSP_INLINE value_type timestamp() const EDSP_NOEXCEPT;

        /**
         * @brief Set the current timestamp of the signal.
         * @param timestamp
         */
        EDSP_INLINE void set_timestamp(value_type timestamp) EDSP_NOEXCEPT;

        /**
         * @brief Returns the sample rate of the signal
         * @return
         */
        EDSP_INLINE value_type samplerate() const EDSP_NOEXCEPT;

        /**
         * @brief Set the sample rate of the signal
         * @param samplerate
         */
        EDSP_INLINE void set_samplerate(value_type samplerate) EDSP_NOEXCEPT;
    private:
        value_type timestamp_{0.};
        value_type samplerate_{0.};
    };

    TimeSeriesGenerator::TimeSeriesGenerator(Generator::value_type amplitude, Generator::value_type samplerate)
            : Generator(amplitude), samplerate_(samplerate_) {}

    TimeSeriesGenerator::TimeSeriesGenerator() = default;

    TimeSeriesGenerator::~TimeSeriesGenerator() = default;

    Generator::value_type TimeSeriesGenerator::timestamp() const EDSP_NOEXCEPT {
        return timestamp_;
    }

    void TimeSeriesGenerator::set_timestamp(Generator::value_type timestamp) EDSP_NOEXCEPT {
        timestamp_ = timestamp;
    }

    void TimeSeriesGenerator::reset() EDSP_NOEXCEPT {
        timestamp_ = 0;
    }

    Generator::value_type TimeSeriesGenerator::samplerate() const EDSP_NOEXCEPT {
        return samplerate_;
    }

    void TimeSeriesGenerator::set_samplerate(Generator::value_type samplerate) EDSP_NOEXCEPT {
        samplerate_ = samplerate;
    }

EDSP_END_NAMESPACE


#endif //EDSP_GENERATORS_TIME_SERIES_GENERATOR_H
