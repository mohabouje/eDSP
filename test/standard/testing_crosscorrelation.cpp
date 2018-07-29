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
#include <easy/meta/size.hpp>
#include <catch/catch.hpp>

using namespace easy;
using namespace easy::dsp;

static constexpr std::array<float, 24> hamming = {{0.080000f, 0.097058f, 0.146967f, 0.226026f, 0.328370f, 0.446410f,
                                                   0.571392f, 0.694045f, 0.805273f, 0.896827f, 0.961917f, 0.995716f,
                                                   0.995716f, 0.961917f, 0.896827f, 0.805273f, 0.694045f, 0.571392f,
                                                   0.446410f, 0.328370f, 0.226026f, 0.146967f, 0.097058f, 0.080000f}};

SCENARIO("Testing CrossCorrelation", "[CrossCorrelation]") {
    GIVEN("An input buffer") {
        WHEN("We want to apply the CrossCorrelation with the same signal") {
            constexpr auto sz = meta::size(hamming);
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
