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
#ifndef EDSP_GENERATORS_TRIANGULAR_PULSE_GENERATOR_H
#define EDSP_GENERATORS_TRIANGULAR_PULSE_GENERATOR_H

#include "oscillator.h"

EDSP_BEGIN_NAMESPACE

/**
 * @brief Generate a triangular pulse over the interval w sampled at times T (1 / %samplerate)
 *
 * This class generated a triangular pulse with a width (w) over the interval \f$ \frac{1}{f} \f$ sampled at times
 * \f$ \frac{1}{f_s} \f$. The location of the peak can be managed by the parameter %skew.
 *
 * See also: set_width, set_skew
 **/
class TriangleOscillator : public Oscillator {
    EDSP_DEFINE_IMPLICITS(TriangleOscillator)
public:
    /**
     * @brief Default constrcutor
     */
    TriangleOscillator();

    /**
     * @brief Created a TriangularPulseGenerator with the given configuration
     * @param amplitude
     * @param samplerate
     * @param frequency
     * @param width_
     * @param skew_
     */
    TriangleOscillator(_In_ value_type amplitude, _In_ value_type samplerate, _In_ value_type frequency,
                             value_type width_, _In_ value_type skew_);


    ~TriangleOscillator() EDSP_OVERRIDE;

    /**
     * @brief Set the width of the pulse over the interval \f$ \frac{1}{F} \f$
     *
     * The width defined the portion of the interval \f$ \frac{1}{Fs} \f$ that
     * stores the pulse.
     *
     * Default Value: 0.3
     *
     * @param width Value between 0 and 1
     */
    EDSP_INLINE void set_width(_In_ value_type width) EDSP_NOEXCEPT;

    /**
     * \brief Return the width of the pulse over the interval \f$ \frac{1}{F} \f$
     * @return Value between 0 and 1
     */
    EDSP_INLINE value_type width() const EDSP_NOEXCEPT;

    /**
     * @brief Modify the relative placement of the peak withing the width
     *
     * -1 indicated that the peak should be at \f$ -\frac{\omega}{2} \$f, while 1 indicated that the peak should
     * be at \$[ \frac{\omega}{2} \$]
     *
     * Default value: 0
     *
     * @param skew Value between -1 and 1
     */
    EDSP_INLINE void set_skew(_In_ value_type skew) EDSP_NOEXCEPT;

    /**
     * \brief Returns the current skew
     * @return Value between -1 and 1
     */
    EDSP_INLINE value_type skew() const EDSP_NOEXCEPT;

    /**
     * \brief Computes the output of the generator in the given timestamp
     *
     * @return Output of the generator
     */
    EDSP_INLINE value_type operator()() EDSP_NOEXCEPT;

private:
    value_type width_{0.3};
    value_type skew_{0};
    value_type peak_{0};
    void compute_peak_position();
};

TriangleOscillator::TriangleOscillator() = default;

TriangleOscillator::~TriangleOscillator() = default;

TriangleOscillator::TriangleOscillator(_In_ Oscillator::value_type amplitude, _In_ Oscillator::value_type samplerate,
                                                   _In_ Oscillator::value_type frequency,
                                                   _In_ Oscillator::value_type width_, _In_ Oscillator::value_type skew_)
        : Oscillator(amplitude, samplerate, frequency, 0.), width_(width_), skew_(skew_) {}


Oscillator::value_type TriangleOscillator::operator()() EDSP_NOEXCEPT {
    const auto half_w = width_ / 2;
    const auto t = timestamp();
    value_type result = 0;
    if (t >= half_w && t < peak_) {
        result = (t + half_w) / (peak_ + half_w);
    } else if (t > peak_ && t < half_w) {
        result = (t - half_w) / (peak_ - half_w);
    }

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

EDSP_END_NAMESPACE

#endif //EDSP_GENERATORS_TRIANGULAR_PULSE_GENERATOR_H
