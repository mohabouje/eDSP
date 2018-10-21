/*
* eDSP, A cross-platform Digital Signal Processing library written in modern C++.
* Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
* You should have received a copy of the GNU General Public License along withº
* this program.  If not, see <http://www.gnu.org/licenses/>
*
* Filename: freqz.hpp
* Author: Mohammed Boujemaoui
* Date: 19/10/18
*/

#ifndef EDSP_FREQZ_HPP
#define EDSP_FREQZ_HPP

#include <edsp/chart/plt.hpp>
#include <edsp/filter.hpp>
#include <edsp/algorithm/linspace.hpp>
#include <edsp/converter/mag2db.hpp>
#include <edsp/converter/rad2deg.hpp>

namespace edsp { namespace chart {

    /**
     * @brief Plots the frequency response of a biquad digital filter.
     * @param biquad Biquad digital filter.
     * @param N Number of evaluation points.
     * @param samplerate Sampling rate in Hz.
     */
    template <typename T, typename Numeric, typename Float>
    inline void freqz(const filter::biquad<T>& biquad, Numeric N, Float samplerate) {
#if defined(USE_MATPLOTLIB)

        std::vector<std::complex<T>> spectrum(N);
        std::vector<T> frequencies(N), magnitude(N), phase(N);

        std::array<T, 3> a = {{biquad.a0(), biquad.a1(), biquad.a2()}}, b = {{biquad.b0(), biquad.b1(), biquad.b2()}};
        filter::freq(std::cbegin(b), std::cend(b), std::cbegin(a), std::cend(a), std::begin(spectrum), N);
        algorithm::linspace(std::begin(frequencies), (Float)0, samplerate / 2, N);
        std::transform(std::cbegin(spectrum), std::cend(spectrum), std::begin(magnitude),
                       [](const auto& element) -> T { return converter::mag2db(std::abs(element)); });
        std::transform(std::cbegin(spectrum), std::cend(spectrum), std::begin(phase),
                       [](const auto& element) -> T { return std::arg(element); });

        plt::figure_size(640, 480);
        plt::title("Magnitude Response (dB) and Phase Response");
        plt::subplot(2, 1, 1);
        plt::ylabel("Magnitude (dB)");
        plt::xlabel("Frequency (Hz)");
        plt::xlim((Float)0, samplerate / 2);
        plt::plot(frequencies, magnitude);
        plt::grid(true);
        plt::subplot(2, 1, 2);
        plt::ylabel("Phase (degrees)");
        plt::xlabel("Frequency (Hz)");
        plt::plot(frequencies, phase);
        plt::xlim((Float)0, samplerate / 2);
        plt::grid(true);
        plt::pause(100);
#endif
    }

    /**
     * @brief Plots the frequency response of a cascade of biquad digital filters.
     * @param cascade Cascade of digital filter.
     * @param N Number of evaluation points.
     * @param samplerate Sampling rate in Hz.
     */
    template <typename T, std::size_t Order, typename Numeric, typename Float>
    inline void freqz(const filter::biquad_cascade<T, Order>& cascade, Numeric N, Float samplerate) {
#if defined(USE_MATPLOTLIB)

        std::vector<std::complex<T>> spectrum(N), global(N, std::complex<T>(1, 1));
        std::vector<T> frequencies(N), magnitude(N), phase(N);

        for (const auto& biquad : cascade) {
            std::array<T, 3> a = {{biquad.a0(), biquad.a1(), biquad.a2()}},
                             b = {{biquad.b0(), biquad.b1(), biquad.b2()}};
            filter::freq(std::cbegin(b), std::cend(b), std::cbegin(a), std::cend(a), std::begin(spectrum), N);
            std::transform(std::cbegin(spectrum), std::cend(spectrum), std::cbegin(global), std::begin(global),
                           std::multiplies<std::complex<T>>());
        }

        algorithm::linspace(std::begin(frequencies), (Float)0, samplerate / 2, N);
        std::transform(std::cbegin(global), std::cend(global), std::begin(magnitude),
                       [](const auto& element) -> T { return converter::mag2db(std::abs(element)); });
        std::transform(std::cbegin(global), std::cend(global), std::begin(phase),
                       [](const auto& element) -> T { return std::arg(element); });

        plt::figure_size(640, 480);
        plt::title("Magnitude Response (dB) and Phase Response");
        plt::subplot(2, 1, 1);
        plt::ylabel("Magnitude (dB)");
        plt::xlabel("Frequency (Hz)");
        plt::xlim((Float)0, samplerate / 2);
        plt::plot(frequencies, magnitude);
        plt::grid(true);
        plt::subplot(2, 1, 2);
        plt::ylabel("Phase (degrees)");
        plt::xlabel("Frequency (Hz)");
        plt::plot(frequencies, phase);
        plt::xlim((Float)0, samplerate / 2);
        plt::grid(true);
        plt::pause(100);
#endif
    }

}} // namespace edsp::chart

#endif //EDSP_FREQZ_HPP
