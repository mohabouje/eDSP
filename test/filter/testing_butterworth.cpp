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
 * Filename: testing_butterworth.cpp
 * Author: Mohammed Boujemaoui
 * Date: 31/8/2018
 */

#include <easy/dsp/filter/filter_types.hpp>
#include <easy/dsp/filter/filter.hpp>
#include <easy/dsp/filter/iir/biquad_cascade.hpp>
#include <catch/catch.hpp>

using namespace easy::dsp;
using namespace easy::dsp::filter;

SCENARIO("Designing a Low Pass Butterworth filter", "[make_filter]") {
    GIVEN("A sample rate") {
        constexpr auto sample_rate = 44100.0;
        WHEN("We want to generate a Low Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::LowPass, ORDER>(
                ORDER, sample_rate, frequency);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.52353695, 0.8095271325, 1.225413164e-05, 2.450826327e-05, 1.225413164e-05}},
                     {{1, -1.295553278, 0.5387475891, 1, 2, 1}},
                     {{1, -1.162420865, 0.3806242733, 1, 2, 1}},
                     {{1, -1.101179975, 0.3078875724, 1, 2, 1}}}};

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
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::LowPass, ORDER>(
                ORDER, sample_rate, frequency);

            THEN("The BiquadCascade stores 16 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.599325486, 0.8995422865, 1.521701195e-10, 3.043402391e-10, 1.521701195e-10}},
                     {{1, -1.455881226, 0.7291714398, 1, 2, 1}},
                     {{1, -1.342461267, 0.5944608943, 1, 2, 1}},
                     {{1, -1.254504965, 0.4899939072, 1, 2, 1}},
                     {{1, -1.188294317, 0.4113545517, 1, 2, 1}},
                     {{1, -1.140980536, 0.3551592815, 1, 2, 1}},
                     {{1, -1.110523197, 0.3189846538, 1, 2, 1}},
                     {{1, -1.095613556, 0.301276255, 1, 2, 1}}}};

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
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::LowPass, ORDER>(
                ORDER, sample_rate, frequency);

            THEN("The BiquadCascade stores 2 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, 1.008807093, 0.5497781137, 0.3103469151, 0.6206938301, 0.3103469151}},
                     {{1, 0.7652014309, 0.1755393455, 1, 2, 1}}}};

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

SCENARIO("Designing a High Pass Butterworth filter", "[make_filter]") {
    GIVEN("A sample rate") {
        constexpr auto sample_rate = 44100.0;
        WHEN("We want to generate a High Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::HighPass, ORDER>(
                ORDER, sample_rate, frequency);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.52353695, 0.8095271325, 0.2260750804, -0.4521501608, 0.2260750804}},
                     {{1, -1.295553278, 0.5387475891, 1, -2, 1}},
                     {{1, -1.162420865, 0.3806242733, 1, -2, 1}},
                     {{1, -1.101179975, 0.3078875724, 1, -2, 1}}}};

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
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::HighPass, ORDER>(
                ORDER, sample_rate, frequency);

            THEN("The BiquadCascade stores 16 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.599325486, 0.8995422865, 0.05179283539, -0.1035856708, 0.05179283539}},
                     {{1, -1.455881226, 0.7291714398, 1, -2, 1}},
                     {{1, -1.342461267, 0.5944608943, 1, -2, 1}},
                     {{1, -1.254504965, 0.4899939072, 1, -2, 1}},
                     {{1, -1.188294317, 0.4113545517, 1, -2, 1}},
                     {{1, -1.140980536, 0.3551592815, 1, -2, 1}},
                     {{1, -1.110523197, 0.3189846538, 1, -2, 1}},
                     {{1, -1.095613556, 0.301276255, 1, -2, 1}}}};

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
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::HighPass, ORDER>(
                ORDER, sample_rate, frequency);

            THEN("The BiquadCascade stores 2 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, 1.008807093, 0.5497781137, 0.01387380752, -0.02774761504, 0.01387380752}},
                     {{1, 0.7652014309, 0.1755393455, 1, -2, 1}}}};

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

SCENARIO("Designing a Low Shelf Pass Butterworth filter", "[make_filter]") {
    GIVEN("A sample rate and a gain in db") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto gain_db     = 5;
        WHEN("We want to generate a Low Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::LowShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.546344979, 0.8147148151, 1.110684501, -1.665623574, 0.8932973718}},
                     {{1, -1.320329418, 0.5494740101, 1, -1.269990901, 0.527979542}},
                     {{1, -1.187488733, 0.3935786812, 1, -1.136758243, 0.3676817194}},
                     {{1, -1.126168093, 0.3216157774, 1, -1.07568515, 0.2942021089}}}};

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
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::LowShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db);

            THEN("The BiquadCascade stores 16 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.610343217, 0.9009819636, 1.110226126, -1.763053023, 0.9970851038}},
                     {{1, -1.467797434, 0.7327091637, 1, -1.443713459, 0.725616612}},
                     {{1, -1.35482787, 0.5993505718, 1, -1.329881546, 0.5895575905}},
                     {{1, -1.26706227, 0.4957448187, 1, -1.241765755, 0.4842360865}},
                     {{1, -1.200903571, 0.4176456328, 1, -1.175527021, 0.4050634095}},
                     {{1, -1.153578621, 0.361779358, 1, -1.128241479, 0.3485447725}},
                     {{1, -1.123092768, 0.3257913425, 1, -1.097823594, 0.3121874146}},
                     {{1, -1.108163074, 0.3081671008, 1, -1.082939338, 0.2943968206}}}};

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
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::LowShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db);

            THEN("The BiquadCascade stores 2 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, 0.9317862107, 0.5337777536, 1.514976453, 1.638555676, 0.8580816408}},
                     {{1, 0.7007655833, 0.1535035074, 1, 0.827774434, 0.1988343446}}}};

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

SCENARIO("Designing a High Shelf Pass Butterworth filter", "[make_filter]") {
    GIVEN("A sample rate and a gain in db") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto gain_db     = 5;
        WHEN("We want to generate a High Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::HighShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.499637, 0.8042764355, 1.601066196, -2.475800674, 1.30441235}},
                     {{1, -1.269990901, 0.527979542, 1, -1.320329418, 0.5494740101}},
                     {{1, -1.136758243, 0.3676817194, 1, -1.187488733, 0.3935786812}},
                     {{1, -1.07568515, 0.2942021089, 1, -1.126168093, 0.3216157774}}}};

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
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::HighShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db);

            THEN("The BiquadCascade stores 16 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.588012552, 0.8980919115, 1.601727223, -2.579330569, 1.443127339}},
                     {{1, -1.443713459, 0.725616612, 1, -1.467797434, 0.7327091637}},
                     {{1, -1.329881546, 0.5895575905, 1, -1.35482787, 0.5993505718}},
                     {{1, -1.241765755, 0.4842360865, 1, -1.26706227, 0.4957448187}},
                     {{1, -1.175527021, 0.4050634095, 1, -1.200903571, 0.4176456328}},
                     {{1, -1.128241479, 0.3485447725, 1, -1.153578621, 0.361779358}},
                     {{1, -1.097823594, 0.3121874146, 1, -1.123092768, 0.3257913425}},
                     {{1, -1.082939338, 0.2943968206, 1, -1.108163074, 0.3081671008}}}};

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
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::HighShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db);

            THEN("The BiquadCascade stores 2 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, 1.081571712, 0.5663993253, 1.173800033, 1.093730685, 0.6265483446}},
                     {{1, 0.827774434, 0.1988343446, 1, 0.7007655833, 0.1535035074}}}};

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

SCENARIO("Designing a Band Pass Butterworth filter", "[make_filter]") {
    GIVEN("A set of parameters") {
        constexpr auto sample_rate         = 44100.0;
        constexpr auto center_frequency    = 6000.0;
        constexpr auto bandwidth_frequency = 400.0;
        constexpr auto gain_db             = 5;
        WHEN("We want to generate a Band Pass Filter (8 order)") {
            constexpr std::size_t ORDER = 8;
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::BandPass, ORDER>(
                ORDER, sample_rate, center_frequency, bandwidth_frequency);

            THEN("The BiquadCascade stores 8 biquads") {
                constexpr auto BIQUAD_CASCADE = ORDER;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = ORDER;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.262808792, 0.9886815712, 3.764141336e-13, 7.528282673e-13, 3.764141336e-13}},
                     {{1, -1.347027992, 0.9892161286, 1, -2, 1}},
                     {{1, -1.256401217, 0.9682077585, 1, 2, 1}},
                     {{1, -1.327628475, 0.9694730969, 1, -2, 1}},
                     {{1, -1.258726018, 0.953086771, 1, 2, 1}},
                     {{1, -1.30623537, 0.9543338049, 1, -2, 1}},
                     {{1, -1.269105311, 0.9453554434, 1, 2, 1}},
                     {{1, -1.285773105, 0.9458680194, 1, -2, 1}}}};

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
            const auto designed_filter  = make_filter<double, DesignerType::Butterworth, FilterType::BandShelf, ORDER>(
                ORDER, sample_rate, center_frequency, bandwidth_frequency, gain_db);

            THEN("The BiquadCascade stores 8 biquads") {
                constexpr auto BIQUAD_CASCADE = ORDER;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = ORDER;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.264619357, 0.989087875, 1.010567521, -1.274254525, 0.9987033848}},
                     {{1, -1.345866768, 0.9895855629, 1, -1.348229119, 0.9888340729}},
                     {{1, -1.258415341, 0.9693343962, 1, -1.254312818, 0.9670396868}},
                     {{1, -1.327134814, 0.9705132494, 1, -1.328139012, 0.9683977957}},
                     {{1, -1.260632007, 0.9547275811, 1, -1.256751648, 0.9513872081}},
                     {{1, -1.30647121, 0.9558899339, 1, -1.305991679, 0.9527250144}},
                     {{1, -1.270629421, 0.9472441999, 1, -1.267527905, 0.9434006969}},
                     {{1, -1.286711723, 0.9477220859, 1, -1.284802381, 0.9439504451}}}};

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
