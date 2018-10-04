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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>

 * File: testing_algorithm.cpp
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
        EXPECT_EQ(math::sign(output[i]), math::sign(data[i]));
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
        EXPECT_EQ(math::sign(output[i]), math::sign(data[i]));
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
        EXPECT_EQ(math::sign(output[i]), math::sign(data[i]));
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
        EXPECT_EQ(math::sign(output[i]), math::sign(data[i]));
    }
}

TEST(TestingClipper, AllBiggerNumbers) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> data(size), output(size);

    const auto minimum = math::rand<double>(0, 1 << 20);
    const auto maximum = math::rand<double>(minimum, 2 * minimum);
    for (auto& element : data) {
        element = math::rand<double>(2 * maximum, 3 * maximum);
    }

    algorithm::clipper(std::cbegin(data), std::cend(data), std::begin(output), minimum, maximum);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_DOUBLE_EQ(output[i], maximum);
        EXPECT_EQ(math::sign(output[i]), math::sign(data[i]));
    }
}

TEST(TestingClipper, AllSmallerNumbers) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> data(size), output(size);

    const auto minimum = math::rand<double>(0, 1 << 20);
    const auto maximum = math::rand<double>(minimum, 2 * minimum);
    for (auto& element : data) {
        element = math::rand<double>(0, minimum - 1);
    }

    algorithm::clipper(std::cbegin(data), std::cend(data), std::begin(output), minimum, maximum);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_DOUBLE_EQ(output[i], minimum);
        EXPECT_EQ(math::sign(output[i]), math::sign(data[i]));
    }
}

TEST(TestingClipper, RandomNumbers) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> data(size), output(size);

    const auto minimum = math::rand<double>(0, 1 << 20);
    const auto maximum = math::rand<double>(minimum, 2 * minimum);
    for (auto& element : data) {
        element = math::rand<double>(minimum / 2, 2 * maximum);
    }

    algorithm::clipper(std::cbegin(data), std::cend(data), std::begin(output), minimum, maximum);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_LE(output[i], maximum);
        EXPECT_GE(output[i], minimum);
        EXPECT_EQ(math::sign(output[i]), math::sign(data[i]));
    }
}

TEST(TestingConcatenate, VectorsSameSizes) {
    const auto size1 = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    const auto size2 = size1;
    std::vector<double> input1(size1), input2(size2), output(size1 + size2);

    for (auto& element : input1) {
        element = math::rand<double>();
    }

    for (auto& element : input2) {
        element = math::rand<double>();
    }

    algorithm::concatenate(std::cbegin(input1), std::cend(input1), std::cbegin(input2), std::cend(input2),
                           std::begin(output));

    for (auto i = 0ul; i < size1; ++i) {
        EXPECT_EQ(input1[i], output[i]);
    }

    for (auto i = size1, limit = size1 + size2; i < limit; ++i) {
        EXPECT_EQ(input2[i - size1], output[i]);
    }
}

TEST(TestingConcatenate, VectorsDifferentSizes) {
    const auto size1 = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    const auto size2 = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    ;
    std::vector<double> input1(size1), input2(size2), output(size1 + size2);

    for (auto& element : input1) {
        element = math::rand<double>();
    }

    for (auto& element : input2) {
        element = math::rand<double>();
    }

    algorithm::concatenate(std::cbegin(input1), std::cend(input1), std::cbegin(input2), std::cend(input2),
                           std::begin(output));

    for (auto i = 0ul; i < size1; ++i) {
        EXPECT_EQ(input1[i], output[i]);
    }

    for (auto i = size1, limit = size1 + size2; i < limit; ++i) {
        EXPECT_EQ(input2[i - size1], output[i]);
    }
}

TEST(TestingEqual, AllElementsDifferent) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> input1(size), input2(size);

    for (auto& element : input1) {
        element = math::rand<double>();
    }

    for (auto& element : input2) {
        element = math::rand<double>();
    }

    EXPECT_FALSE(algorithm::equal(std::cbegin(input1), std::cend(input1), std::cbegin(input2), std::cend(input2)));
}

TEST(TestingEqual, OnlyOneDifferent) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> input1(size), input2(size);

    for (auto& element : input1) {
        element = math::rand<double>();
    }

    std::copy(std::cbegin(input1), std::cend(input1), std::begin(input2));
    const auto random_index = math::rand(0ul, size);
    input2[random_index]    = 2 * input2[random_index];

    EXPECT_FALSE(algorithm::equal(std::cbegin(input1), std::cend(input1), std::cbegin(input2), std::cend(input2)));
}

TEST(TestingEqual, SameVector) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> input1(size), input2(size);

    for (auto& element : input1) {
        element = math::rand<double>();
    }

    std::copy(std::cbegin(input1), std::cend(input1), std::begin(input2));

    EXPECT_TRUE(algorithm::equal(std::cbegin(input1), std::cend(input1), std::cbegin(input2), std::cend(input2)));
}

TEST(TestingNormalizer, PositiveValues) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> input(size), output(size);

    for (auto& element : input) {
        element = math::rand<double>(1 << 2, 1 << 20);
    }

    algorithm::normalizer(std::cbegin(input), std::cend(input), std::begin(output));
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_LE(output[i], 1);
        EXPECT_GE(output[i], -1);
        EXPECT_EQ(math::sign(output[i]), math::sign(input[i]));
    }
}

TEST(TestingNormalizer, NegativeValues) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> input(size), output(size);

    for (auto& element : input) {
        element = math::rand<double>(-(1 << 20), -(1 << 2));
    }

    algorithm::normalizer(std::cbegin(input), std::cend(input), std::begin(output));
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_LE(output[i], 1);
        EXPECT_GE(output[i], -1);
        EXPECT_EQ(math::sign(output[i]), math::sign(input[i]));
    }
}

TEST(TestingNormalizer, RandomValues) {
    const auto size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    std::vector<double> input(size), output(size);

    for (auto& element : input) {
        element = math::rand<double>();
    }

    algorithm::normalizer(std::cbegin(input), std::cend(input), std::begin(output));
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_LE(output[i], 1);
        EXPECT_GE(output[i], -1);
        EXPECT_EQ(math::sign(output[i]), math::sign(input[i]));
    }
}

TEST(TestingPadder, OutputBiggerThanInput) {
    const auto i_size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    const auto o_size = math::rand(i_size, MAXIMUM_SIZE);
    std::vector<double> input(i_size), output(o_size);
    for (auto& element : input) {
        element = math::rand<double>();
    }

    algorithm::padder(std::cbegin(input), std::cend(input), std::begin(output), std::end(output));
    for (auto i = 0ul; i < i_size; ++i) {
        EXPECT_LE(output[i], input[i]);
    }

    for (auto i = i_size; i < o_size; ++i) {
        EXPECT_LE(output[i], 0);
    }
}

TEST(TestingPadder, OutputSmallerThanInput) {
    const auto lambda = []() {
        const auto i_size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
        const auto o_size = math::rand(0ul, MINIMUM_SIZE);
        std::vector<double> input(i_size), output(o_size);
        algorithm::padder(std::cbegin(input), std::cend(input), std::begin(output), std::end(output));
    };
    ASSERT_DEBUG_DEATH(lambda(), "");
}

TEST(TestingPadder, OutputEqualThanInput) {
    const auto i_size = math::rand(MINIMUM_SIZE, MAXIMUM_SIZE);
    const auto o_size = i_size;
    std::vector<double> input(i_size), output(o_size);
    for (auto& element : input) {
        element = math::rand<double>();
    }

    algorithm::padder(std::cbegin(input), std::cend(input), std::begin(output), std::end(output));
    for (auto i = 0ul; i < i_size; ++i) {
        EXPECT_LE(output[i], input[i]);
    }

    for (auto i = i_size; i < o_size; ++i) {
        EXPECT_LE(output[i], 0);
    }
}

TEST(TestingLinspace, IncreasingOrder) {
    const auto size = 32ul;
    const auto min  = 10ul;
    const auto max  = 100ul;

    const std::vector<double> expected = {10.000, 12.903, 15.806, 18.710, 21.613, 24.516, 27.419, 30.323,
                                          33.226, 36.129, 39.032, 41.935, 44.839, 47.742, 50.645, 53.548,
                                          56.452, 59.355, 62.258, 65.161, 68.065, 70.968, 73.871, 76.774,
                                          79.677, 82.581, 85.484, 88.387, 91.290, 94.194, 97.097, 100.000};

    EXPECT_EQ(expected.size(), size);
    std::vector<double> computed(size);
    algorithm::linspace(std::begin(computed), size, min, max);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(computed[i], expected[i], 0.001);
    }
}

TEST(TestingLinspace, DecreaseOrder) {
    const auto size = 32ul;
    const auto min  = 10ul;
    const auto max  = 100ul;

    std::vector<double> expected = {10.000, 12.903, 15.806, 18.710, 21.613, 24.516, 27.419, 30.323,
                                    33.226, 36.129, 39.032, 41.935, 44.839, 47.742, 50.645, 53.548,
                                    56.452, 59.355, 62.258, 65.161, 68.065, 70.968, 73.871, 76.774,
                                    79.677, 82.581, 85.484, 88.387, 91.290, 94.194, 97.097, 100.000};
    std::reverse(std::begin(expected), std::end(expected));
    EXPECT_EQ(expected.size(), size);

    std::vector<double> computed(size);
    algorithm::linspace(std::begin(computed), size, max, min);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(computed[i], expected[i], 0.001);
    }
}

TEST(TestingLinspace, NegativeRangeIncrease) {
    const auto size = 32ul;
    const auto min  = -100;
    const auto max  = -10;

    const std::vector<double> expected = {-100.000, -97.097, -94.194, -91.290, -88.387, -85.484, -82.581, -79.677,
                                          -76.774,  -73.871, -70.968, -68.065, -65.161, -62.258, -59.355, -56.452,
                                          -53.548,  -50.645, -47.742, -44.839, -41.935, -39.032, -36.129, -33.226,
                                          -30.323,  -27.419, -24.516, -21.613, -18.710, -15.806, -12.903, -10.000};
    EXPECT_EQ(expected.size(), size);

    std::vector<double> computed(size);
    algorithm::linspace(std::begin(computed), size, min, max);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(computed[i], expected[i], 0.001);
    }
}

TEST(TestingLinspace, NegativeRangeDecrease) {
    const auto size = 32ul;
    const auto min  = -100;
    const auto max  = -10;

    std::vector<double> expected = {-100.000, -97.097, -94.194, -91.290, -88.387, -85.484, -82.581, -79.677,
                                    -76.774,  -73.871, -70.968, -68.065, -65.161, -62.258, -59.355, -56.452,
                                    -53.548,  -50.645, -47.742, -44.839, -41.935, -39.032, -36.129, -33.226,
                                    -30.323,  -27.419, -24.516, -21.613, -18.710, -15.806, -12.903, -10.000};
    std::reverse(std::begin(expected), std::end(expected));
    EXPECT_EQ(expected.size(), size);

    std::vector<double> computed(size);
    algorithm::linspace(std::begin(computed), size, max, min);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(computed[i], expected[i], 0.001);
    }
}

TEST(TestingLinspace, MixedIncrease) {
    const auto size = 32ul;
    const auto min  = -10;
    const auto max  = 10;

    const std::vector<double> expected = {
        -10.00000, -9.35484, -8.70968, -8.06452, -7.41935, -6.77419, -6.12903, -5.48387, -4.83871, -4.19355, -3.54839,
        -2.90323,  -2.25806, -1.61290, -0.96774, -0.32258, 0.32258,  0.96774,  1.61290,  2.25806,  2.90323,  3.54839,
        4.19355,   4.83871,  5.48387,  6.12903,  6.77419,  7.41935,  8.06452,  8.70968,  9.35484,  10.00000};
    EXPECT_EQ(expected.size(), size);

    std::vector<double> computed(size);
    algorithm::linspace(std::begin(computed), size, min, max);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(computed[i], expected[i], 0.001);
    }
}

TEST(TestingLinspace, MixedDecrease) {
    const auto size = 32ul;
    const auto min  = -10;
    const auto max  = 10;

    std::vector<double> expected = {-10.00000, -9.35484, -8.70968, -8.06452, -7.41935, -6.77419, -6.12903, -5.48387,
                                    -4.83871,  -4.19355, -3.54839, -2.90323, -2.25806, -1.61290, -0.96774, -0.32258,
                                    0.32258,   0.96774,  1.61290,  2.25806,  2.90323,  3.54839,  4.19355,  4.83871,
                                    5.48387,   6.12903,  6.77419,  7.41935,  8.06452,  8.70968,  9.35484,  10.00000};
    std::reverse(std::begin(expected), std::end(expected));
    EXPECT_EQ(expected.size(), size);

    std::vector<double> computed(size);
    algorithm::linspace(std::begin(computed), size, max, min);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(computed[i], expected[i], 0.001);
    }
}

TEST(TestingLogspace, IncreaseOrder) {
    const auto size = 32ul;
    const auto min  = 1;
    const auto max  = 3;

    const std::vector<double> expected = {10.0000000000000,  11.6015530173997,  13.4596032415536,  15.6152300600050,
                                          18.1160919420041,  21.0174801133249,  24.3835409826883,  28.2886943462597,
                                          32.8192787251147,  38.0754602122237,  44.1734470314007,  51.2480587696093,
                                          59.4557070854439,  68.9778537938765,  80.0250227816105,  92.8414544519474,
                                          107.7105056036769, 124.9609141291987, 144.9740670372632, 168.1924324880869,
                                          195.1293422635962, 226.3803409521446, 262.6363527653332, 304.6989570903508,
                                          353.4981105030106, 410.1127070551300, 475.7944314009409, 551.9954321281573,
                                          640.4004271197283, 742.9639507594950, 861.9535664753032, 1000.0000000000000};
    EXPECT_EQ(expected.size(), size);

    std::vector<double> computed(size);
    algorithm::logspace(std::begin(computed), size, min, max);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(computed[i], expected[i], 0.001);
    }
}

TEST(TestingLogspace, DecreaseOrder) {
    const auto size = 32ul;
    const auto min  = 1;
    const auto max  = 3;

    std::vector<double> expected = {10.0000000000000,  11.6015530173997,  13.4596032415536,  15.6152300600050,
                                    18.1160919420041,  21.0174801133249,  24.3835409826883,  28.2886943462597,
                                    32.8192787251147,  38.0754602122237,  44.1734470314007,  51.2480587696093,
                                    59.4557070854439,  68.9778537938765,  80.0250227816105,  92.8414544519474,
                                    107.7105056036769, 124.9609141291987, 144.9740670372632, 168.1924324880869,
                                    195.1293422635962, 226.3803409521446, 262.6363527653332, 304.6989570903508,
                                    353.4981105030106, 410.1127070551300, 475.7944314009409, 551.9954321281573,
                                    640.4004271197283, 742.9639507594950, 861.9535664753032, 1000.0000000000000};
    std::reverse(std::begin(expected), std::end(expected));
    EXPECT_EQ(expected.size(), size);

    std::vector<double> computed(size);
    algorithm::logspace(std::begin(computed), size, max, min);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(computed[i], expected[i], 0.001);
    }
}