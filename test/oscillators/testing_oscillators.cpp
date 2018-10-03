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
    {0.000000000000,  -0.213734852679, -0.417591611371, -0.602148713814, -0.758876561857, -0.880531730324,
     -0.961491733348, -0.998014876448, -0.988413184845, -0.933130415892, -0.834721550120, -0.697734708779,
     -0.528500955225, -0.33441694823,  -0.125707196336, 0.089237058888,  0.300057082412,  0.497009493685,
     0.670991825771,  0.813963210245,  0.919315998632,  0.982181145325,  0.999653238222,  0.970924776939,
     0.897323492715,  0.782250985212,  0.631025512218,  0.45063197953,   0.249420019648,  0.036676500970,
     -0.177762080161, -0.383985105835, -0.572461653023, -0.734480980241, -0.862555108239, -0.950764888794,
     -0.995033567497, -0.993315197402, -0.945689195700, -0.854356673323, -0.723538707129, -0.559281256159,
     -0.369175738090, -0.162008179868, 0.052646842412,  0.264868707671,  0.464849247027,  0.643346043818,
     0.792109586500,  0.904264532852,  0.974627464787,  0.999946448210,  0.979051326289,  0.912907800106,
     0.804572797252,  0.659053191086,  0.483074400177,  0.284769562450,  0.073303649366,  -0.141550107717,
     -0.349861902877, -0.542004277300, -0.709097067506, -0.843417816133, -0.938758677515, -0.990713323073,
     -0.996880586757, -0.956975438729, -0.87284258470,  -0.748369098483, -0.589308977945, -0.403013011692,
     -0.198091162212, 0.015985783377,  0.229323920725,  0.432063490671,  0.614834563595,  0.769190085524,
     0.887996272082,  0.965762307604,  0.998894111862,  0.985860446165,  0.92726681969,   0.825811961334,
     0.686194035856,  0.514862568602,  0.319735914090,  0.109832159022,  -0.105147662845, -0.315267919307,
     -0.510817570652, -0.682758980713, -0.823145605499, -0.925489255291, -0.985059956577, -0.999104555255,
     -0.966973958004, -0.890153131151, -0.772192470613, -0.618543714730, -0.436307983572, -0.233907589445,
     -0.020696786422, 0.193470551293,  0.398696341733,  0.585495750672,  0.745235548220,  0.870533107193,
     0.955597602894,  0.996497645222,  0.991342974088,  0.940371820764,  0.845939897650,  0.712411525308,
     0.545957928483,  0.354272023202,  0.146212876505,  -0.068603729344, -0.280249705425, -0.478943498484,
     -0.655502160875, -0.801765754996, -0.910974477700, -0.97808107}};

SCENARIO("Generating Sinusoidal Signals", "[make_oscillator]") {
    GIVEN("A default configuration with Fs = 44100 & F = 1500") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto frequency   = 1500.0;
        constexpr auto amplitude   = 1;

        WHEN("We want to generate a sinusoidal signal") {
            constexpr auto phase = easy::dsp::constants<double>::pi;
            auto sinusoidal =
                make_oscillator<double, OscillatorType::Sinusoidal>(amplitude, sample_rate, frequency, phase);
            std::array<double, size> input;
            std::generate(std::begin(input), std::end(input), std::ref(sinusoidal));
            THEN("The expected signal is the right one") {
                for (auto i = 0; i < size; ++i) {
                    REQUIRE(Approx(input[i]).margin(0.01) == sinusoidal_data_1500_pi[i]);
                }
            }
        }
    }

    GIVEN("A default configuration with Fs = 44100 & F = 600") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto frequency   = 600.0;
        constexpr auto amplitude   = 1;

        WHEN("We want to generate a sinusoidal signal") {
            constexpr auto phase = 0.15;
            auto sinusoidal =
                make_oscillator<double, OscillatorType::Sinusoidal>(amplitude, sample_rate, frequency, phase);
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
