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
 * Filename: testing_biquad.cpp
 * Created at: 10/06/18
 * Created by: Mohammed Boujemaoui
 */

#include <easy/dsp/filter/biquad.hpp>
#include <easy/meta/meta.hpp>
#include <catch/catch.hpp>

using namespace easy;
using namespace easy::dsp;

constexpr std::array<ereal, 14> hamming = {
    {0.0800000000000000, 0.1326902281995235, 0.2786902165036683, 0.4845531270825514, 0.7031182480395664,
     0.8843149441587066, 0.9866332360159840, 0.9866332360159840, 0.8843149441587066, 0.7031182480395666,
     0.4845531270825514, 0.2786902165036688, 0.1326902281995234, 0.0800000000000000}};

constexpr std::array<ereal, 14> filtered_hamming = {
    {0.0600000000000000, 0.1225176711496426, 0.2243161029851142, 0.4080561361272294, 0.6038674248104523,
     0.7454970053272414, 0.8343232053689902, 0.8383218172944669, 0.7436858710921658, 0.5892356489435457,
     0.4057487890439693, 0.2277438949872962, 0.1045839910529946, 0.0628555966544836}};

SCENARIO("Testing the Biquad filter class", "[Biquad]") {
    GIVEN("An input data that we want to filter") {
        std::vector<ereal> input;
        std::vector<ereal> output;
        filter::Biquad<float> biquad;

        WHEN("The input buffer is empty") {
            THEN("The biquad should run with no problem") {
                REQUIRE_NOTHROW(biquad.apply(std::cbegin(input), std::cend(input), std::begin(output)));
            }
        }

        WHEN("We want to filter with the default Biquad initializer") {
            const auto sz = std::size(hamming);
            input.resize(sz);
            output.resize(sz);

            std::copy(std::begin(hamming), std::end(hamming), std::begin(input));
            REQUIRE(meta::notempty(input));
            REQUIRE(std::size(input) == std::size(output));

            THEN("The biquad filter should not modify any imput") {
                REQUIRE(Approx(biquad.a0()).epsilon(0) == 1);
                REQUIRE(Approx(biquad.a1()).epsilon(0) == 0);
                REQUIRE(Approx(biquad.a2()).epsilon(0) == 0);
                REQUIRE(Approx(biquad.b0()).epsilon(0) == 1);
                REQUIRE(Approx(biquad.b1()).epsilon(0) == 0);
                REQUIRE(Approx(biquad.b2()).epsilon(0) == 0);
            }

            AND_WHEN("The data should be filtered with no problem") {
                REQUIRE_NOTHROW(biquad.apply(std::cbegin(input), std::cend(input), std::begin(output)));
                THEN("The filtered output should store the same data") {
                    for (std::size_t i = 0; i < std::size(output); ++i) {
                        REQUIRE(hamming[i] == Approx(output[i]).epsilon(0.00001));
                    }
                }
            }
        }

        WHEN("We want to filter the data with an existing Biquad") {
            constexpr auto a0 = 1.00f;
            constexpr auto a1 = 0.75f;
            constexpr auto a2 = 0.64f;
            constexpr auto b0 = 0.75f;
            constexpr auto b1 = 0.85f;
            constexpr auto b2 = 0.41f;

            biquad = filter::Biquad(a0, a1, a2, b0, b1, b2);

            THEN("The biquad is initialized correctly") {
                REQUIRE(Approx(biquad.a0()).margin(0.001) == a0);
                REQUIRE(Approx(biquad.a1()).margin(0.001) == a1);
                REQUIRE(Approx(biquad.a2()).margin(0.001) == a2);
                REQUIRE(Approx(biquad.b0()).margin(0.001) == b0);
                REQUIRE(Approx(biquad.b1()).margin(0.001) == b1);
                REQUIRE(Approx(biquad.b2()).margin(0.001) == b2);
            }

            AND_WHEN("We want to filter the data with the given biquad") {
                const auto sz = std::size(hamming);
                input.resize(sz);
                output.resize(sz);

                std::copy(std::begin(hamming), std::end(hamming), std::begin(input));
                REQUIRE(meta::notempty(input));
                REQUIRE(std::size(input) == std::size(output));

                THEN("The data should be filtered with no problem") {
                    REQUIRE_NOTHROW(biquad.apply(std::cbegin(input), std::cend(input), std::begin(output)));
                    AND_THEN("The filtered output should store the same data") {
                        for (std::size_t i = 0; i < std::size(output); ++i) {
                            REQUIRE(filtered_hamming[i] == Approx(output[i]).margin(0.00001));
                        }
                    }
                }
            }
        }
    }
}
