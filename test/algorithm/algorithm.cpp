/* 
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (c) 2018  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 * File: algorithm.cpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 04/10/18.
 */

#include <easy/dsp/algorithm.hpp>
#include <easy/dsp/math/numeric.hpp>
#include <gtest/gtest.h>

static const auto MINIMUM_SIZE = 16ul;
static const auto MAXIMUM_SIZE = 2048ul;

using namespace easy::dsp;

TEST(TestingAmplifier, TestingAttenuation) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> data(size), output(size);
    for (auto& element : data) {
        element = math::rand<double>(0, 1 << 20);
    }

    const auto attenuation_factor = math::rand<double>(0.1, 0.9);
    algorithm::amplifier(std::cbegin(data), std::cend(data), std::begin(output), attenuation_factor);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_LT(output[i], data[i]);
        EXPECT_DOUBLE_EQ(output[i], attenuation_factor * data[i]);
    }
}

TEST(TestingAmplifier, TestingAmplification) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> data(size), output(size);
    for (auto& element : data) {
        element = math::rand<double>(0, 1 << 20);
    }

    const auto attenuation_factor = math::rand<double>(2, 10);
    algorithm::amplifier(std::cbegin(data), std::cend(data), std::begin(output), attenuation_factor);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_GT(output[i], data[i]);
        EXPECT_DOUBLE_EQ(output[i], attenuation_factor * data[i]);
    }
}

TEST(TestingCeil, FloatingData) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> data(size), output(size);
    for (auto& element : data) {
        element = math::rand<double>(0, 1 << 20);
    }

    algorithm::ceil(std::cbegin(data), std::cend(data), std::begin(output));
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_DOUBLE_EQ(output[i], std::ceil(data[i]));
    }
}

TEST(TestingFix, FloatingData) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> data(size), output(size);
    for (auto& element : data) {
        element = math::rand<double>(0, 1 << 20);
    }

    algorithm::fix(std::cbegin(data), std::cend(data), std::begin(output));
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_DOUBLE_EQ(output[i], std::trunc(data[i]));
    }
}

TEST(TestingFloor, FloatingData) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> data(size), output(size);
    for (auto& element : data) {
        element = math::rand<double>(0, 1 << 20);
    }

    algorithm::floor(std::cbegin(data), std::cend(data), std::begin(output));
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_DOUBLE_EQ(output[i], std::floor(data[i]));
    }
}

TEST(TestingRound, FloatingData) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> data(size), output(size);
    for (auto& element : data) {
        element = math::rand<double>(0, 1 << 20);
    }

    algorithm::round(std::cbegin(data), std::cend(data), std::begin(output));
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_DOUBLE_EQ(output[i], std::round(data[i]));
    }
}