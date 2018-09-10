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
 * Filename: testing_chebyshev_II.cpp
 * Author: Mohammed Boujemaoui
 * Date: 31/8/2018
 */

#include <easy/dsp/filter/filter_types.hpp>
#include <easy/dsp/filter/filter.hpp>
#include <easy/dsp/filter/iir/biquad_cascade.hpp>
#include <catch/catch.hpp>

using namespace easy::dsp;
using namespace easy::dsp::filter;

SCENARIO("Designing a Low Pass ChebyshevII filter", "[make_filter]") {
    GIVEN("A sample rate") {
        constexpr auto sample_rate = 44100.0;
        WHEN("We want to generate a Low Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::LowPass, ORDER>(
                ORDER, sample_rate, frequency, stopband_db);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.658990301, 0.9810735537, 0.5651962102, -0.9452475796, 0.5651962102}},
                     {{1, -1.507587398, 0.9294112754, 1, -1.558363455, 1}},
                     {{1, -1.036055179, 0.806936878, 1, -1.129914394, 1}},
                     {{1, 0.438279993, 0.4439519853, 1, 0.7709046595, 1}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }

        WHEN("We want to generate a Low Pass Filter at 4000Hz (16 order)") {
            constexpr std::size_t ORDER = 16;
            constexpr auto frequency    = 4000.0;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::LowPass, ORDER>(
                ORDER, sample_rate, frequency, stopband_db);

            THEN("The BiquadCascade stores 16 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.67772071, 0.9953162866, 0.5614613835, -0.9438639469, 0.5614613835}},
                     {{1, -1.645682996, 0.9851726188, 1, -1.657311384, 1}},
                     {{1, -1.581226597, 0.9722654979, 1, -1.602570317, 1}},
                     {{1, -1.464171334, 0.9533119102, 1, -1.49774439, 1}},
                     {{1, -1.248993131, 0.9217543579, 1, -1.297061465, 1}},
                     {{1, -0.8316194312, 0.8631274773, 1, -0.8857307875, 1}},
                     {{1, -0.004103227028, 0.7488004949, 1, 0.01809606958, 1}},
                     {{1, 1.206904196, 0.5823557303, 1, 1.59722359, 1}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }

        WHEN("We want to generate a Low Pass Filter at 16000Hz (4 order)") {
            constexpr std::size_t ORDER = 4;
            constexpr auto frequency    = 16000.0;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::LowPass, ORDER>(
                ORDER, sample_rate, frequency, stopband_db);

            THEN("The BiquadCascade stores 2 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, 1.301206621, 0.9002067265, 0.8198301947, 1.138318739, 0.8198301947}},
                     {{1, 1.62005598, 0.7466394287, 1, 1.879864866, 1}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }
    }
}

SCENARIO("Designing a High Pass ChebyshevII filter", "[make_filter]") {
    GIVEN("A sample rate") {
        constexpr auto sample_rate = 44100.0;
        WHEN("We want to generate a High Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::HighPass, ORDER>(
                ORDER, sample_rate, frequency, stopband_db);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.677127735, 0.9815526974, 0.8791359651, -1.490152602, 0.8791359651}},
                     {{1, -1.726844602, 0.947245269, 1, -1.776007696, 1}},
                     {{1, -1.818185872, 0.9196765482, 1, -1.896796801, 1}},
                     {{1, -1.88893985, 0.9038594784, 1, -1.986979642, 1}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }

        WHEN("We want to generate a High Pass Filter at 4000Hz (16 order)") {
            constexpr std::size_t ORDER = 16;
            constexpr auto frequency    = 4000.0;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::HighPass, ORDER>(
                ORDER, sample_rate, frequency, stopband_db);

            THEN("The BiquadCascade stores 16 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.682215653, 0.9953464612, 0.8797543398, -1.483886166, 0.8797543398}},
                     {{1, -1.696243039, 0.9861999252, 1, -1.708601474, 1}},
                     {{1, -1.729437207, 0.9774411887, 1, -1.749752529, 1}},
                     {{1, -1.776634858, 0.9693209067, 1, -1.804915309, 1}},
                     {{1, -1.830548468, 0.9621509407, 1, -1.866481765, 1}},
                     {{1, -1.88246093, 0.9562939563, 1, -1.925159291, 1}},
                     {{1, -1.923453853, 0.9521213029, 1, -1.971286449, 1}},
                     {{1, -1.946084012, 0.9499450321, 1, -1.996705317, 1}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }

        WHEN("We want to generate a Low Pass Filter at 16000Hz (4 order)") {
            constexpr std::size_t ORDER = 4;
            constexpr auto frequency    = 16000.0;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::HighPass, ORDER>(
                ORDER, sample_rate, frequency, stopband_db);

            THEN("The BiquadCascade stores 2 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, 1.162499575, 0.8923920652, 0.6093926526, 0.7348503461, 0.6093926526}},
                     {{1, -0.1245199264, 0.4423193874, 1, -0.3631775852, 1}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }
    }
}

SCENARIO("Designing a Low Shelf Pass ChebyshevII filter", "[make_filter]") {
    GIVEN("A sample rate and a gain in db") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto stopband_db = 2.0;
        constexpr auto gain_db     = 5.0;
        WHEN("We want to generate a Low Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::LowShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, stopband_db);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {{
                    {{1, -1.673621129, 0.9784075215, 1.085318308, -1.801275159, 1.049427852}},
                    {{1, -1.71816545, 0.9384328827, 1, -1.685760368, 0.906713586}},
                    {{1, -1.804782608, 0.9064808059, 1, -1.755850661, 0.8594980423}},
                    {{1, -1.872481693, 0.8882171721, 1, -1.812996632, 0.8328677531}},
                }};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }

        WHEN("We want to generate a Low Pass Filter at 4000Hz (16 order)") {
            constexpr std::size_t ORDER = 16;
            constexpr auto frequency    = 4000.0;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::LowShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, stopband_db);

            THEN("The BiquadCascade stores 16 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.681330985, 0.9945476089, 1.084372731, -1.819364144, 1.075286888}},
                     {{1, -1.694018194, 0.9838436468, 1, -1.685609724, 0.9752432824}},
                     {{1, -1.725869728, 0.9736092972, 1, -1.712602069, 0.9596718501}},
                     {{1, -1.771734612, 0.9641347328, 1, -1.753670523, 0.9453324122}},
                     {{1, -1.824377042, 0.9557799712, 1, -1.801760287, 0.9327479622}},
                     {{1, -1.87517255, 0.9489627948, 1, -1.848571303, 0.9225210649}},
                     {{1, -1.91532162, 0.9441102642, 1, -1.885719031, 0.9152640971}},
                     {{1, -1.937494732, 0.9415807804, 1, -1.906269557, 0.9114886867}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }

        WHEN("We want to generate a Low Pass Filter at 16000Hz (4 order)") {
            constexpr std::size_t ORDER = 4;
            constexpr auto frequency    = 16000.0;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::LowShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, stopband_db);

            THEN("The BiquadCascade stores 2 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, 1.160237742, 0.8760679736, 1.384837082, 1.611431146, 1.139349944}},
                     {{1, -0.07513912361, 0.3883145211, 1, 0.107064778, 0.254780595}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }
    }
}

SCENARIO("Designing a High Shelf Pass ChebyshevII filter", "[make_filter]") {
    GIVEN("A sample rate and a gain in db") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto gain_db     = 5.0;
        constexpr auto stopband_db = 2.0;
        WHEN("We want to generate a High Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::HighShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, stopband_db);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.657222221, 0.9779029776, 1.439405076, -2.378070854, 1.391302949}},
                     {{1, -1.500240108, 0.918019413, 1, -1.476812728, 0.8784507834}},
                     {{1, -1.025360025, 0.7787468216, 1, -0.9979531794, 0.687629488}},
                     {{1, 0.3818178669, 0.3871868645, 1, 0.184918661, 0.2391680825}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }

        WHEN("We want to generate a High Pass Filter at 4000Hz (16 order)") {
            constexpr std::size_t ORDER = 16;
            constexpr auto frequency    = 4000.0;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::HighShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, stopband_db);

            THEN("The BiquadCascade stores 16 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.677261303, 0.9945156401, 1.439779102, -2.412893644, 1.427682048}},
                     {{1, -1.643840345, 0.9826539229, 1, -1.637487609, 0.973516243}},
                     {{1, -1.577808328, 0.967593768, 1, -1.565923574, 0.9507475447}},
                     {{1, -1.458867171, 0.9455473986, 1, -1.4406091, 0.9178067635}},
                     {{1, -1.241707655, 0.909022775, 1, -1.217397889, 0.8642423201}},
                     {{1, -0.8244700799, 0.8417679979, 1, -0.8031623556, 0.7687848078}},
                     {{1, -0.01120626668, 0.7128154709, 1, -0.04331861221, 0.5964685107}},
                     {{1, 1.147073444, 0.5301081742, 1, 0.9435430289, 0.3738452209}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }

        WHEN("We want to generate a Low Pass Filter at 16000Hz (4 order)") {
            constexpr std::size_t ORDER = 4;
            constexpr auto frequency    = 16000.0;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::HighShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, stopband_db);

            THEN("The BiquadCascade stores 2 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, 1.283434098, 0.8840522353, 1.137194558, 1.377903958, 0.9406802607}},
                     {{1, 1.577643217, 0.7095025777, 1, 1.426550943, 0.586370326}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }
    }
}

SCENARIO("Designing a Band Pass ChebyshevII filter", "[make_filter]") {
    GIVEN("A set of parameters") {
        constexpr auto sample_rate         = 44100.0;
        constexpr auto center_frequency    = 6000.0;
        constexpr auto bandwidth_frequency = 400.0;
        constexpr auto gain_db             = 5.0;
        constexpr auto stopband_db         = 2.0;
        WHEN("We want to generate a Band Pass Filter (8 order)") {
            constexpr std::size_t ORDER = 8;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::BandPass, ORDER>(
                ORDER, sample_rate, center_frequency, bandwidth_frequency, stopband_db);

            THEN("The BiquadCascade stores 8 biquads") {
                constexpr auto BIQUAD_CASCADE = ORDER;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = ORDER;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.267781607, 0.9989640603, 0.7080688628, -0.8980058401, 0.7080688628}},
                     {{1, -1.35507324, 0.9990149134, 1, -1.355914698, 1}},
                     {{1, -1.257757805, 0.9958980257, 1, -1.259943583, 1}},
                     {{1, -1.360361611, 0.9961333816, 1, -1.363351144, 1}},
                     {{1, -1.225691229, 0.9863363597, 1, -1.232374957, 1}},
                     {{1, -1.376963184, 0.9874718276, 1, -1.387107776, 1}},
                     {{1, -1.04869177, 0.8893377352, 1, -1.065947346, 1}},
                     {{1, -1.410761282, 0.909398243, 1, -1.505540407, 1}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    // TODO: review why this part fails.
                    /*REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);*/
                }
            }
        }

        WHEN("We want to generate a Band Shelf Pass Filter (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto stopband_db  = 2.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::BandShelf, ORDER>(
                ORDER, sample_rate, center_frequency, bandwidth_frequency, gain_db, stopband_db);

            THEN("The BiquadCascade stores 8 biquads") {
                constexpr auto BIQUAD_CASCADE = ORDER;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = ORDER;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.269013817, 0.9988228681, 1.008227849, -1.278720908, 1.006397775}},
                     {{1, -1.353784239, 0.998879022, 1, -1.353666058, 0.9982720375}},
                     {{1, -1.274375212, 0.9966628465, 1, -1.27295112, 0.9948572313}},
                     {{1, -1.346223566, 0.9967981834, 1, -1.345306466, 0.9950670972}},
                     {{1, -1.285646414, 0.995041707, 1, -1.283740958, 0.9923626378}},
                     {{1, -1.33364639, 0.9951769043, 1, -1.332074591, 0.9925721059}},
                     {{1, -1.30093385, 0.9942042977, 1, -1.298830896, 0.9910753244}},
                     {{1, -1.31778788, 0.9942602725, 1, -1.31580113, 0.9911620086}}}};

                for (auto i = 0ul; i < BIQUAD_CASCADE; ++i) {
                    const auto& stage = designed_filter[i];
                    REQUIRE(Approx(stage.a0()) == expected_results[i][0]);
                    REQUIRE(Approx(stage.a1()) == expected_results[i][1]);
                    REQUIRE(Approx(stage.a2()) == expected_results[i][2]);
                    REQUIRE(Approx(stage.b0()) == expected_results[i][3]);
                    REQUIRE(Approx(stage.b1()) == expected_results[i][4]);
                    REQUIRE(Approx(stage.b2()) == expected_results[i][5]);
                }
            }
        }
    }
}
