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

#include "config.h"

EDSP_BEGIN_NAMESPACE
/**
 * @brief Base class that implements the interface to generate periodic signals.
 */
class Oscillator  {
    EDSP_DECLARE_ALL_IMPLICITS(Oscillator)
public:
    using value_type = edsp::real_t;
    Oscillator();
    virtual ~Oscillator();

    Oscillator(_In_ value_type amplitude_, _In_ value_type samplerate_, _In_ value_type frequency_, _In_ value_type phase_);
    /**
     * @brief Returns the frequency of the generated signal.
     * @return Frequency in Hz
     */
    EDSP_INLINE value_type frequency() const EDSP_NOEXCEPT;

    /**
     * @brief Returns the phase of the signal
     * @return Phase in degree
     */
    EDSP_INLINE value_type phase() const EDSP_NOEXCEPT;

    /**
     * @brief Set the frequency of the signal.
     * The frequency is proportional to the period of the signal.
     * @param frequency Scalar value in Hz
     */
    EDSP_INLINE void set_frequency(_In_ value_type frequency) EDSP_NOEXCEPT;

    /**
     * @brief Set the phase of the signal
     * @param phase Scalar value in degree
     */
    EDSP_INLINE void set_phase(_In_ value_type phase) EDSP_NOEXCEPT;

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
    EDSP_INLINE void set_timestamp(_In_ value_type timestamp) EDSP_NOEXCEPT;

    /**
     * @brief Returns the sample rate of the signal (Hz)
     * @return Sample rate in Hz
     */
    EDSP_INLINE value_type samplerate() const EDSP_NOEXCEPT;

    /**
     * @brief Returns the sampling period (Secs)
     * @return Sampling period in seconds
     */
    EDSP_INLINE value_type sampling_period() const EDSP_NOEXCEPT;

    /**
     * @brief Set the sample rate of the signal (Hz)
     * @param samplerate in Hz
     */
    EDSP_INLINE void set_samplerate(_In_ value_type samplerate) EDSP_NOEXCEPT;

    /**
     * @brief Returns the amplitude of the signal
     * @return Amplitude of the signal
     */
    EDSP_INLINE value_type amplitude() const EDSP_NOEXCEPT;

    /**
     * @brief Set the amplitude of the signal
     * @param Amplitude
     */
    void set_amplitude(_In_ value_type amplitude) EDSP_NOEXCEPT;


private:
    value_type amplitude_{0.};
    value_type timestamp_{0.};
    value_type samplerate_{0.};
    value_type sampling_period_{0.};
    value_type frequency_{1.};
    value_type phase_{0.};
};

Oscillator::Oscillator() = default;
Oscillator::Oscillator(_In_ Oscillator::value_type amplitude_, _In_ Oscillator::value_type samplerate_,
                       _In_ Oscillator::value_type frequency_, _In_ Oscillator::value_type phase_) : amplitude_(amplitude_),
                                                                                           samplerate_(samplerate_),
                                                                                           frequency_(frequency_),
                                                                                           phase_(phase_) {}

Oscillator::~Oscillator() = default;


Oscillator::value_type Oscillator::timestamp() const EDSP_NOEXCEPT {
    return timestamp_;
}

void Oscillator::set_timestamp(_In_ Oscillator::value_type timestamp) EDSP_NOEXCEPT {
    timestamp_ = timestamp;
}

void Oscillator::reset() EDSP_NOEXCEPT {
    timestamp_ = 0;
}

Oscillator::value_type Oscillator::samplerate() const EDSP_NOEXCEPT {
    return samplerate_;
}

void Oscillator::set_samplerate(_In_ Oscillator::value_type samplerate) EDSP_NOEXCEPT {
    samplerate_ = samplerate;
    if (samplerate_ > 0) {
        sampling_period_ =  1. / samplerate_;
    }
}

Oscillator::value_type Oscillator::frequency() const EDSP_NOEXCEPT {
    return frequency_;
}

void Oscillator::set_frequency(_In_ Oscillator::value_type frequency) EDSP_NOEXCEPT {
    frequency_ = frequency;
}

Oscillator::value_type Oscillator::phase() const EDSP_NOEXCEPT {
    return phase_;
}

void Oscillator::set_phase(_In_ Oscillator::value_type phase) EDSP_NOEXCEPT {
    phase_ = phase;
}

Oscillator::value_type Oscillator::amplitude() const EDSP_NOEXCEPT {
    return amplitude_;
}

void Oscillator::set_amplitude(_In_ Oscillator::value_type amplitude) EDSP_NOEXCEPT {
    amplitude_ = amplitude;
}

Oscillator::value_type Oscillator::sampling_period() const EDSP_NOEXCEPT {
    return sampling_period_;
}

EDSP_END_NAMESPACE

#endif //EDSP_PERIODIC_GENERATOR_H
