/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
 * Filename: testing_dct.cpp
 * Author: Mohammed Boujemaoui
 * Date: 8/9/2018
 */

#include <edsp/windowing.hpp>
#include <edsp/spectral/dct.hpp>

#include <gtest/gtest.h>
#include <unordered_map>
#include <fstream>
#include <istream>

using namespace edsp::windowing;

TEST(TestingDCT, TransformHanningWindow) {
    const auto size = 128ul;
    std::vector<double> window(size);
    make_window<WindowType::Hanning>(std::begin(window), std::end(window));
    std::vector<double> transformed(size), inverse(size);
    edsp::dct(std::cbegin(window), std::cend(window), std::begin(transformed));
    edsp::idct(std::cbegin(transformed), std::cend(transformed), std::begin(inverse));

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], inverse[i], 0.001);
    }
}

TEST(TestingDCT, TransformHammingWindow) {
    const auto size = 128ul;
    std::vector<double> window(size);
    make_window<WindowType::Hamming>(std::begin(window), std::end(window));
    std::vector<double> transformed(size), inverse(size);
    edsp::dct(std::cbegin(window), std::cend(window), std::begin(transformed));
    edsp::idct(std::cbegin(transformed), std::cend(transformed), std::begin(inverse));

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], inverse[i], 0.001);
    }
}

TEST(TestingDCT, TransformHammingWindowDCT_I) {
    const auto size = 128ul;
    std::vector<double> window(size);
    make_window<WindowType::Hamming>(std::begin(window), std::end(window));
    std::vector<double> transformed(size), inverse(size);
    edsp::dct(std::cbegin(window), std::cend(window), std::begin(transformed), edsp::DCT_Type::Type_I);
    edsp::idct(std::cbegin(transformed), std::cend(transformed), std::begin(inverse), edsp::DCT_Type::Type_I);

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], inverse[i], 0.001);
    }
}

TEST(TestingDCT, TransformHammingWindowDCT_III) {
    const auto size = 128ul;
    std::vector<double> window(size);
    make_window<WindowType::Hamming>(std::begin(window), std::end(window));
    std::vector<double> transformed(size), inverse(size);
    edsp::dct(std::cbegin(window), std::cend(window), std::begin(transformed), edsp::DCT_Type::Type_III);
    edsp::idct(std::cbegin(transformed), std::cend(transformed), std::begin(inverse), edsp::DCT_Type::Type_III);

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], inverse[i], 0.001);
    }
}

TEST(TestingDCT, TransformHammingWindowDCT_IV) {
    const auto size = 128ul;
    std::vector<double> window(size);
    make_window<WindowType::Hamming>(std::begin(window), std::end(window));
    std::vector<double> transformed(size), inverse(size);
    edsp::dct(std::cbegin(window), std::cend(window), std::begin(transformed), edsp::DCT_Type::Type_IV);
    edsp::idct(std::cbegin(transformed), std::cend(transformed), std::begin(inverse), edsp::DCT_Type::Type_IV);

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], inverse[i], 0.001);
    }
}

TEST(TestingDCT, TransformBlackmanWindow) {
    const auto size = 128ul;
    std::vector<double> window(size);
    make_window<WindowType::Blackman>(std::begin(window), std::end(window));
    std::vector<double> transformed(size), inverse(size);
    edsp::dct(std::cbegin(window), std::cend(window), std::begin(transformed));
    edsp::idct(std::cbegin(transformed), std::cend(transformed), std::begin(inverse));

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], inverse[i], 0.001);
    }
}
