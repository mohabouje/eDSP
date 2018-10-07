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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: testing_filter.cpp
 * Author: Mohammed Boujemaoui
 * Date: 05/10/2018
 */

#include <edsp/filter.hpp>
#include <edsp/windowing.hpp>
#include <gtest/gtest.h>

using namespace edsp::windowing;
using namespace edsp::filter;

template struct edsp::filter::designer<float, edsp::filter::DesignerType::RBJ, 10>;
template struct edsp::filter::designer<float, edsp::filter::DesignerType::Zolzer, 10>;
template struct edsp::filter::designer<float, edsp::filter::DesignerType::Butterworth, 10>;
template struct edsp::filter::designer<float, edsp::filter::DesignerType::ChebyshevI, 10>;
template struct edsp::filter::designer<float, edsp::filter::DesignerType::ChebyshevII, 10>;
template class edsp::filter::moving_median<float>;
template class edsp::filter::moving_average<float>;
template class edsp::filter::moving_rms<float>;

template class edsp::filter::biquad<float>;
template class edsp::filter::biquad_cascade<float, 10>;

TEST(TestingBiquad, InitializeDefault) {
    biquad<float> b{};

    EXPECT_EQ(b.a0(), 1);
    EXPECT_EQ(b.a1(), 0);
    EXPECT_EQ(b.a2(), 0);
    EXPECT_EQ(b.b0(), 1);
    EXPECT_EQ(b.b1(), 0);
    EXPECT_EQ(b.b2(), 0);

    constexpr auto N = 128ul;
    std::array<float, N> input{}, output{};

    hamming(std::begin(input), std::end(input));
    b.filter(std::cbegin(input), std::cend(input), std::begin(output));

    for (auto i = 0ul; i < N; ++i) {
        EXPECT_EQ(input[i], output[i]);
    }
}