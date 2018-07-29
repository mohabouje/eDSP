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
#include <array>
#include <easy/meta/empty.hpp>
#include <easy/meta/size.hpp>
#include <catch/catch.hpp>

using namespace easy;
using namespace easy::dsp;

constexpr std::array<float, 14> hamming = {
    {0.0800000000000000f, 0.1326902281995235f, 0.2786902165036683f, 0.4845531270825514f, 0.7031182480395664f,
     0.8843149441587066f, 0.9866332360159840f, 0.9866332360159840f, 0.8843149441587066f, 0.7031182480395666f,
     0.4845531270825514f, 0.2786902165036688f, 0.1326902281995234f, 0.0800000000000000f}};

constexpr std::array<float, 14> filtered_hamming = {
    {0.0600000000000000f, 0.1225176711496426f, 0.2243161029851142f, 0.4080561361272294f, 0.6038674248104523f,
     0.7454970053272414f, 0.8343232053689902f, 0.8383218172944669f, 0.7436858710921658f, 0.5892356489435457f,
     0.4057487890439693f, 0.2277438949872962f, 0.1045839910529946f, 0.0628555966544836f}};

SCENARIO("Testing the Biquad filter class", "[Biquad]") {
    GIVEN("An input data that we want to filter") {
        std::vector<float> input;
        std::vector<float> output;
        filter::Biquad<float> biquad;

        WHEN("The input buffer is empty") {
            THEN("The biquad should run with no problem") {
                REQUIRE_NOTHROW(biquad.apply(std::cbegin(input), std::cend(input), std::begin(output)));
            }
        }

        WHEN("We want to filter with the default Biquad initializer") {
            const auto sz = meta::size(hamming);
            input.resize(sz);
            output.resize(sz);

            std::copy(std::begin(hamming), std::end(hamming), std::begin(input));
            REQUIRE(!meta::empty(input));
            REQUIRE(meta::size(input) == meta::size(output));

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
                    for (std::size_t i = 0; i < meta::size(output); ++i) {
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
                REQUIRE(Approx(biquad.a0()).margin(0.001f) == a0);
                REQUIRE(Approx(biquad.a1()).margin(0.001f) == a1);
                REQUIRE(Approx(biquad.a2()).margin(0.001f) == a2);
                REQUIRE(Approx(biquad.b0()).margin(0.001f) == b0);
                REQUIRE(Approx(biquad.b1()).margin(0.001f) == b1);
                REQUIRE(Approx(biquad.b2()).margin(0.001f) == b2);
            }

            AND_WHEN("We want to filter the data with the given biquad") {
                const auto sz = meta::size(hamming);
                input.resize(sz);
                output.resize(sz);

                std::copy(std::begin(hamming), std::end(hamming), std::begin(input));
                REQUIRE(!meta::empty(input));
                REQUIRE(meta::size(input) == meta::size(output));

                THEN("The data should be filtered with no problem") {
                    REQUIRE_NOTHROW(biquad.apply(std::cbegin(input), std::cend(input), std::begin(output)));
                    AND_THEN("The filtered output should store the same data") {
                        for (std::size_t i = 0; i < meta::size(output); ++i) {
                            REQUIRE(filtered_hamming[i] == Approx(output[i]).margin(0.00001));
                        }
                    }
                }
            }
        }
    }
}
