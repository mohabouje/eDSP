/*
 * EasyMeta, Yet another header-only library for C++ meta-programming.
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
 * Filename: testing_fft.cpp
 * Created at: 08/09/18
 * Created by: Mohammed Boujemaoui
 */

#include <gtest/gtest.h>
#include <easy/dsp/windowing/windowing.hpp>
#include <unordered_map>
#include <fstream>

using namespace easy::dsp::windowing;

std::string data_path(const std::string filename) {
    std::string path = CURRENT_TEST_PATH;
    path += "/windowing/data/";
    path += filename;
    return path;
}

template <typename T>
std::vector<T> read_vector(const std::string& filename) {
    std::ifstream input(filename.c_str());
    if (!input.is_open()) {
        return {};
    }

    std::vector<T> data;
    std::string line;
    while (std::getline(input, line)) {
        data.push_back(static_cast<T>(std::stod(line)));
    }
    return data;
}

static std::unordered_map<WindowType, std::string> AssociatedFile = {
    {WindowType::Bartlett, data_path("bartlett.csv")},
    {WindowType::Blackman, data_path("blackman.csv")},
    {WindowType::BlackmanHarris, data_path("blackman_harris.csv")},
    {WindowType::BlackmanNuttall, data_path("blackman_nuttall.csv")},
    {WindowType::Bohman, data_path("bohman.csv")},
    {WindowType::Boxcar, data_path("boxcar.csv")},
    {WindowType::Hamming, data_path("hamming.csv")},
    {WindowType::Hanning, data_path("hanning.csv")},
    {WindowType::FlatTop, data_path("flattop.csv")}
};




TEST(TestingWindowing, CreatingHammingWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Hamming]);
    const auto size = reference.size();
    const auto window = make_window<double, WindowType::Hamming>(size);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], reference[i], 0.00001);
    }
}

TEST(TestingWindowing, CreatingHanningWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Hanning]);
    const auto size = reference.size();
    const auto window = make_window<double, WindowType::Hanning>(size);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], reference[i], 0.00001);
    }
}

TEST(TestingWindowing, CreatingBlackman) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Blackman]);
    const auto size = reference.size();
    const auto window = make_window<double, WindowType::Blackman>(size);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], reference[i], 0.00001);
    }
}

TEST(TestingWindowing, CreatingBlackmanHarris) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::BlackmanHarris]);
    const auto size = reference.size();
    const auto window = make_window<double, WindowType::BlackmanHarris>(size);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], reference[i], 0.00001);
    }
}

TEST(TestingWindowing, CreatingBlackmanNuttall) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::BlackmanNuttall]);
    const auto size = reference.size();
    const auto window = make_window<double, WindowType::BlackmanNuttall>(size);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], reference[i], 0.00001);
    }
}

TEST(TestingWindowing, CreatingBartlett) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Bartlett]);
    const auto size = reference.size();
    const auto window = make_window<double, WindowType::Bartlett>(size);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], reference[i], 0.00001);
    }
}

TEST(TestingWindowing, CreatingBohman) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Bohman]);
    const auto size = reference.size();
    const auto window = make_window<double, WindowType::Bohman>(size);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], reference[i], 0.00001);
    }
}

TEST(TestingWindowing, CreatingBoxcar) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Boxcar]);
    const auto size = reference.size();
    const auto window = make_window<double, WindowType::Boxcar>(size);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], reference[i], 0.00001);
    }
}

TEST(TestingWindowing, CreatingFlatTop) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::FlatTop]);
    const auto size = reference.size();
    const auto window = make_window<double, WindowType::FlatTop>(size);
    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(window[i], reference[i], 0.00001);
    }
}
