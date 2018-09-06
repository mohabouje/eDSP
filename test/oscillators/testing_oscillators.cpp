/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: testing_oscillators.cpp
 * Author: Mohammed Boujemaoui
 * Date: 3/9/2018
 */
#include <easy/dsp/oscillators/oscillator.hpp>
#include <algorithm>
#include <functional>
#include <catch/catch.hpp>

using namespace easy::dsp;
using namespace easy::dsp::oscillators;

SCENARIO("Generating Oscillators", "[make_oscillator]") {
    GIVEN("A default configuration") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto frequency   = 600.0;
        constexpr auto amplitude   = 1;
        constexpr auto size        = 1024;

        WHEN("We want to generate a sinusoidal oscillator") {
            constexpr auto phase = 0.15;
            auto sinusoidal = make_oscillator<double, SignalType::Sinusoidal>(amplitude, sample_rate, frequency, phase);

            std::array<double, size> input;
            std::generate(std::begin(input), std::end(input), std::ref(sinusoidal));
        }

        WHEN("We want to generate a square oscillator") {
            constexpr auto dutty = 0.5;
            auto square = make_oscillator<double, SignalType::Square>(amplitude, sample_rate, frequency, dutty);

            std::array<double, size> input;
            std::generate(std::begin(input), std::end(input), std::ref(square));
        }

        WHEN("We want to generate a triangular oscillator") {
            constexpr auto width = 0.2;
            constexpr auto skew  = 0.3;
            auto triangular =
                make_oscillator<double, SignalType::Triangular>(amplitude, sample_rate, frequency, width, skew);

            std::array<double, size> input;
            std::generate(std::begin(input), std::end(input), std::ref(triangular));
        }

        WHEN("We want to generate a sawtooth oscillator") {
            constexpr auto width = 0.5;
            auto sawtooth = make_oscillator<double, SignalType::Sawtooth>(amplitude, sample_rate, frequency, width);

            std::array<double, size> input;
            std::generate(std::begin(input), std::end(input), std::ref(sawtooth));
        }
    }
}
