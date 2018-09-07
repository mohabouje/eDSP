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
#include <easy/dsp/math/constant.hpp>
#include <algorithm>
#include <functional>
#include <catch/catch.hpp>

using namespace easy::dsp;
using namespace easy::dsp::oscillators;

static constexpr auto size                                        = 128;
static constexpr std::array<double, size> sinusoidal_data_600_015 = {
    {0.149438,  0.233970,  0.316765,  0.397211,  0.474710,  0.548687,  0.618594,  0.683911,  0.744155,  0.798878,
     0.847674,  0.890182,  0.926086,  0.955119,  0.977067,  0.991766,  0.999107,  0.999037,  0.991554,  0.976716,
     0.954632,  0.925465,  0.889433,  0.846802,  0.797889,  0.743057,  0.682712,  0.617303,  0.547314,  0.473264,
     0.395704,  0.315207,  0.232373,  0.147814,  0.062159,  -0.023957, -0.109896, -0.195019, -0.278695, -0.360304,
     -0.439240, -0.514917, -0.586775, -0.654279, -0.716929, -0.774260, -0.825848, -0.871309, -0.910306, -0.942549,
     -0.967800, -0.985871, -0.996628, -0.999992, -0.995937, -0.984493, -0.965746, -0.939834, -0.906949, -0.867337,
     -0.821289, -0.769149, -0.711303, -0.648180, -0.580248, -0.508011, -0.432006, -0.352796, -0.270968, -0.187130,
     -0.101904, -0.015922, 0.070178,  0.155758,  0.240182,  0.322824,  0.403071,  0.480328,  0.554022,  0.623605,
     0.688563,  0.748411,  0.802708,  0.851050,  0.893077,  0.928480,  0.956994,  0.978408,  0.992565,  0.999357,
     0.998735,  0.990705,  0.975324,  0.952708,  0.923024,  0.886492,  0.843384,  0.794018,  0.738762,  0.678026,
     0.612259,  0.541951,  0.467621,  0.389823,  0.309132,  0.226149,  0.141487,  0.055776,  -0.030349, -0.116249,
     -0.201287, -0.284831, -0.366262, -0.444976, -0.520388, -0.591940, -0.659101, -0.721372, -0.778291, -0.829437,
     -0.874429, -0.912934, -0.944666, -0.969390, -0.986922, -0.997133, -0.999946, -0.995341}};

static constexpr std::array<double, size> sinusoidal_data_1500_pi = {
    {0.000000,  -0.213735, -0.417592, -0.602149, -0.758877, -0.880532, -0.961492, -0.998015, -0.988413, -0.933130,
     -0.834722, -0.697735, -0.528501, -0.334842, -0.125707, 0.089237,  0.300057,  0.497009,  0.670992,  0.813963,
     0.919316,  0.982181,  0.999653,  0.970925,  0.897323,  0.782251,  0.631026,  0.450636,  0.249420,  0.036677,
     -0.177762, -0.383985, -0.572462, -0.734481, -0.862555, -0.950765, -0.995034, -0.993315, -0.945689, -0.854357,
     -0.723539, -0.559281, -0.369176, -0.162008, 0.052647,  0.264869,  0.464849,  0.643346,  0.792110,  0.904265,
     0.974627,  0.999946,  0.979051,  0.912908,  0.804573,  0.659053,  0.483074,  0.284770,  0.073304,  -0.141550,
     -0.349862, -0.542004, -0.709097, -0.843418, -0.938759, -0.990713, -0.996881, -0.956975, -0.872842, -0.748369,
     -0.589309, -0.403013, -0.198091, 0.015986,  0.229324,  0.432063,  0.614835,  0.769190,  0.887996,  0.965762,
     0.998894,  0.985860,  0.927264,  0.825812,  0.686194,  0.514863,  0.319736,  0.109832,  -0.105148, -0.315268,
     -0.510818, -0.682759, -0.823146, -0.925489, -0.985060, -0.999105, -0.966974, -0.890153, -0.772192, -0.618544,
     -0.436308, -0.233908, -0.020697, 0.193471,  0.398696,  0.585496,  0.745236,  0.870533,  0.955598,  0.996498,
     0.991343,  0.940372,  0.845940,  0.712412,  0.545958,  0.354272,  0.146213,  -0.068604, -0.280250, -0.478943,
     -0.655502, -0.801766, -0.910974, -0.978081, -0.999984, -0.975671, -0.906266, -0.794977}};

SCENARIO("Generating Sinusoidal Signals", "[make_oscillator]") {
    GIVEN("A default configuration with Fs = 44100 & F = 1500") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto frequency   = 1500.0;
        constexpr auto amplitude   = 1;

        WHEN("We want to generate a sinusoidal oscillator") {
            constexpr auto phase = easy::constants<double>::pi;
            auto sinusoidal = make_oscillator<double, SignalType::Sinusoidal>(amplitude, sample_rate, frequency, phase);
            std::array<double, size> input;
            std::generate(std::begin(input), std::end(input), std::ref(sinusoidal));
            THEN("The expected signal is the right one") {
                for (auto i = 0; i < size; ++i) {
                    REQUIRE(Approx(input[i]) == sinusoidal_data_1500_pi[i]);
                }
            }
        }
    }

    GIVEN("A default configuration") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto frequency   = 600.0;
        constexpr auto amplitude   = 1;

        WHEN("We want to generate a sinusoidal oscillator") {
            constexpr auto phase = 0.15;
            auto sinusoidal = make_oscillator<double, SignalType::Sinusoidal>(amplitude, sample_rate, frequency, phase);
            std::array<double, size> input;
            std::generate(std::begin(input), std::end(input), std::ref(sinusoidal));
            THEN("The expected signal is the right one") {
                for (auto i = 0; i < size; ++i) {
                    REQUIRE(Approx(input[i]) == sinusoidal_data_600_015[i]);
                }
            }
        }
    }
}
