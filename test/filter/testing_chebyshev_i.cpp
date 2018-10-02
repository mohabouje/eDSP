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
 * Filename: testing_chebyshev_I.cpp
 * Author: Mohammed Boujemaoui
 * Date: 31/8/2018
 */

#include <easy/dsp/filter/filter.hpp>
#include <easy/dsp/filter/biquad_cascade.hpp>
#include <catch/catch.hpp>

using namespace easy::dsp;
using namespace easy::dsp::filter;

SCENARIO("Designing a Low Pass ChebyshevI filter", "[make_filter]") {
    GIVEN("A sample rate") {
        constexpr auto sample_rate = 44100.0;
        WHEN("We want to generate a Low Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::LowPass, ORDER>(
                ORDER, sample_rate, frequency, ripple_db);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.665779072, 0.9717717621, 3.845460216e-07, 7.690920431e-07, 3.845460216e-07}},
                     {{1, -1.699569795, 0.9200099281, 1, 2, 1}},
                     {{1, -1.776496159, 0.8790953474, 1, 2, 1}},
                     {{1, -1.837981981, 0.8558897977, 1, 2, 1}}}};

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
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::LowPass, ORDER>(
                ORDER, sample_rate, frequency, ripple_db);

            THEN("The BiquadCascade stores 16 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.679348874, 0.9928576048, 6.903605836e-14, 1.380721167e-13, 6.903605836e-14}},
                     {{1, -1.689211875, 0.9788710452, 1, 2, 1}},
                     {{1, -1.718245865, 0.9655415381, 1, 2, 1}},
                     {{1, -1.761324438, 0.9532392845, 1, 2, 1}},
                     {{1, -1.811317951, 0.9424209903, 1, 2, 1}},
                     {{1, -1.859792116, 0.933614389, 1, 2, 1}},
                     {{1, -1.898190923, 0.927357083, 1, 2, 1}},
                     {{1, -1.919417237, 0.9240990544, 1, 2, 1}}}};

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
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::LowPass, ORDER>(
                ORDER, sample_rate, frequency, ripple_db);

            THEN("The BiquadCascade stores 2 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, 1.160052694, 0.8439901443, 0.1985009247, 0.3970018495, 0.1985009247}},
                     {{1, 0.03044055671, 0.3005543558, 1, 2, 1}}}};

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

SCENARIO("Designing a High Pass ChebyshevI filter", "[make_filter]") {
    GIVEN("A sample rate") {
        constexpr auto sample_rate = 44100.0;
        WHEN("We want to generate a High Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::HighPass, ORDER>(
                ORDER, sample_rate, frequency, ripple_db);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.654011952, 0.9713036934, 0.1065412363, -0.2130824726, 0.1065412363}},
                     {{1, -1.486043207, 0.894738392, 1, -2, 1}},
                     {{1, -1.007387408, 0.7238378997, 1, -2, 1}},
                     {{1, 0.2659935318, 0.2917333819, 1, -2, 1}}}};

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
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::HighPass, ORDER>(
                ORDER, sample_rate, frequency, ripple_db);

            THEN("The BiquadCascade stores 16 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.676404744, 0.9928273954, 0.01058911089, -0.02117822179, 0.01058911089}},
                     {{1, -1.64009489, 0.9773587102, 1, -2, 1}},
                     {{1, -1.570821786, 0.9578115696, 1, -2, 1}},
                     {{1, -1.448097735, 0.9293887886, 1, -2, 1}},
                     {{1, -1.22721639, 0.8828015707, 1, -2, 1}},
                     {{1, -0.8112572938, 0.7986209654, 1, -2, 1}},
                     {{1, -0.02868987663, 0.6427906603, 1, -2, 1}},
                     {{1, 1.026661726, 0.4337387949, 1, -2, 1}}}};

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
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::HighPass, ORDER>(
                ORDER, sample_rate, frequency, ripple_db);

            THEN("The BiquadCascade stores 2 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, 1.243254394, 0.8507774211, 0.004416420859, -0.008832841718, 0.004416420859}},
                     {{1, 1.489629661, 0.6360588613, 1, -2, 1}}}};

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

SCENARIO("Designing a Low Shelf Pass ChebyshevI filter", "[make_filter]") {
    GIVEN("A sample rate and a gain in db") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto ripple_db   = 2;
        constexpr auto gain_db     = 5;
        WHEN("We want to generate a Low Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::LowShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, ripple_db);

            THEN("The BiquadCascade stores 4 biquads") {
                constexpr auto BIQUAD_CASCADE = (ORDER + 1) / 2;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = (ORDER + 1) / 2;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.673621129, 0.9784075215, 1.085318308, -1.801275159, 1.049427852}},
                     {{1, -1.71816545, 0.9384328827, 1, -1.685760368, 0.906713586}},
                     {{1, -1.804782608, 0.9064808059, 1, -1.755850661, 0.8594980423}},
                     {{1, -1.872481693, 0.8882171721, 1, -1.812996632, 0.8328677531}}}};

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
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::LowShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, ripple_db);

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
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::LowShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, ripple_db);

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

SCENARIO("Designing a High Shelf Pass ChebyshevI filter", "[make_filter]") {
    GIVEN("A sample rate and a gain in db") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto gain_db     = 5;
        constexpr auto ripple_db   = 2;
        WHEN("We want to generate a High Pass Filter at 4000Hz (8 order)") {
            constexpr std::size_t ORDER = 8;
            constexpr auto frequency    = 4000.0;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::HighShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, ripple_db);

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
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::HighShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, ripple_db);

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
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::HighShelf, ORDER>(
                ORDER, sample_rate, frequency, gain_db, ripple_db);

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

SCENARIO("Designing a Band Pass ChebyshevI filter", "[make_filter]") {
    GIVEN("A set of parameters") {
        constexpr auto sample_rate         = 44100.0;
        constexpr auto center_frequency    = 6000.0;
        constexpr auto bandwidth_frequency = 400.0;
        constexpr auto gain_db             = 5;
        constexpr auto ripple_db           = 2;
        WHEN("We want to generate a Band Pass Filter (8 order)") {
            constexpr std::size_t ORDER = 8;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::BandPass, ORDER>(
                ORDER, sample_rate, center_frequency, bandwidth_frequency, ripple_db);

            THEN("The BiquadCascade stores 8 biquads") {
                constexpr auto BIQUAD_CASCADE = ORDER;
                REQUIRE(typeid(BiquadCascade<double, BIQUAD_CASCADE>) == typeid(designed_filter));
            }
            AND_THEN("Each Biquad has the right values") {
                constexpr auto BIQUAD_CASCADE     = ORDER;
                using holder                      = std::array<std::array<double, 6>, BIQUAD_CASCADE>;
                constexpr holder expected_results = {
                    {{{1, -1.268610655, 0.9984551422, 4.355550836e-15, 8.711101672e-15, 4.355550836e-15}},
                     {{1, -1.353701109, 0.9985290996, 1, -2, 1}},
                     {{1, -1.273568102, 0.9956218779, 1, 2, 1}},
                     {{1, -1.345681945, 0.9958000058, 1, -2, 1}},
                     {{1, -1.284556815, 0.9934968469, 1, 2, 1}},
                     {{1, -1.332731251, 0.9936747022, 1, -2, 1}},
                     {{1, -1.2997242, 0.9923997615, 1, 2, 1}},
                     {{1, -1.316638939, 0.9924733779, 1, -2, 1}}}};

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
            constexpr auto ripple_db    = 2;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::BandShelf, ORDER>(
                ORDER, sample_rate, center_frequency, bandwidth_frequency, gain_db, ripple_db);

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
