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
 * Filename: testing_correlation.cpp
 * Author: Mohammed Boujemaoui
 * Date: 04/10/2018
 */

#include <easy/dsp/windowing.hpp>
#include <easy/dsp/spectral/correlation.hpp>

#include <gtest/gtest.h>
#include <unordered_map>
#include <fstream>
#include <istream>
#include <boost/algorithm/string.hpp>

using namespace easy::dsp::windowing;

namespace {
    std::string data_path(const std::string filename) {
        std::string path = CURRENT_TEST_PATH;
        path += "/spectral/data/xcorr/";
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
            data.emplace_back(static_cast<T>(std::stod(line)));
        }
        return data;
    }

    static std::unordered_map<WindowType, std::string> AssociatedFile = {
        {WindowType::Blackman, data_path("xcorr_blackman.csv")},
        {WindowType::Hamming, data_path("xcorr_hamming.csv")},
        {WindowType::Hanning, data_path("xcorr_hanning.csv")},
    };
} // namespace

TEST(TestingCorrelation, CorrelationHanningWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Hanning]);
    const auto size      = reference.size();
    std::vector<double> window(size);
    make_window<WindowType::Hanning>(std::begin(window), size);
    std::vector<double> transformed(size);
    easy::dsp::xcorr(std::begin(window), std::end(window), std::begin(transformed));

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(transformed[i], reference[i], 0.01);
    }
}

TEST(TestingCorrelation, CorrelationHammingWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Hamming]);
    const auto size      = reference.size();
    std::vector<double> window(size);
    make_window<WindowType::Hamming>(std::begin(window), size);
    std::vector<double> transformed(size);
    easy::dsp::xcorr(std::begin(window), std::end(window), std::begin(window), std::begin(transformed));

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(transformed[i], reference[i], 0.01);
    }
}

TEST(TestingCorrelation, CorrelationBlackmanWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Blackman]);
    const auto size      = reference.size();
    std::vector<double> window(size);
    make_window<WindowType::Blackman>(std::begin(window), size);
    std::vector<double> transformed(size);
    easy::dsp::xcorr(std::begin(window), std::end(window), std::begin(transformed));

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(transformed[i], reference[i], 0.01);
    }
}
