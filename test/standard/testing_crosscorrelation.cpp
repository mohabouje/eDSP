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
 * Filename: testing_crosscorrelation.cpp
 * Created at: 10/06/18
 * Created by: Mohammed Boujemaoui
 */

#include <easy/dsp/standard/autocorrelation.hpp>
#include <easy/dsp/standard/crosscorrelation.hpp>
#include <catch/catch.hpp>

using namespace easy;
using namespace easy::dsp;

static constexpr std::array<float, 24> hamming = {{0.080000, 0.097058, 0.146967, 0.226026, 0.328370, 0.446410,
                                                   0.571392, 0.694045, 0.805273, 0.896827, 0.961917, 0.995716,
                                                   0.995716, 0.961917, 0.896827, 0.805273, 0.694045, 0.571392,
                                                   0.446410, 0.328370, 0.226026, 0.146967, 0.097058, 0.080000}};

SCENARIO("Testing CrossCorrelation", "[CrossCorrelation]") {
    GIVEN("An input buffer") {
        WHEN("We want to apply the CrossCorrelation with the same signal") {
            constexpr auto sz = std::size(hamming);
            std::vector<float> output_cross(sz), output_auto(sz);

            CrossCorrelation<float> cross_correlation(sz, CrossCorrelation<float>::ScaleOpt::None);
            cross_correlation.compute(std::cbegin(hamming), std::cend(hamming), std::cbegin(hamming),
                                      std::begin(output_cross));

            THEN("We should get the same output as with the AutoCorrelation class") {
                AutoCorrelation<float> auto_correlation(sz, AutoCorrelation<float>::ScaleOpt::None);
                auto_correlation.compute(std::cbegin(hamming), std::cend(hamming), std::begin(output_auto));
                for (std::size_t i = 0; i < sz; ++i) {
                    REQUIRE(Approx(output_cross[i]) == output_auto[i]);
                }
            }
        }
    }
}
