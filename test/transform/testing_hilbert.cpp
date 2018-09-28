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
 * Filename: testing_hilbert.cpp
 * Author: Mohammed Boujemaoui
 * Date: 8/9/2018
 */

#include <easy/dsp/windowing/windowing.hpp>
#include <easy/dsp/transform/hilbert.hpp>
#include <easy/dsp/utilities/real2complex.hpp>

#include <gtest/gtest.h>
#include <unordered_map>
#include <fstream>
#include <istream>
#include <boost/algorithm/string.hpp>

using namespace easy::dsp::windowing;

namespace {
    std::string data_path(const std::string filename) {
        std::string path = CURRENT_TEST_PATH;
        path += "/transform/data/hilbert/";
        path += filename;
        return path;
    }

    template <typename T>
    std::vector<std::complex<T>> read_vector(const std::string& filename) {
        std::ifstream input(filename.c_str());
        if (!input.is_open()) {
            return {};
        }

        std::vector<std::complex<T>> data;
        std::string line;
        while (std::getline(input, line)) {
            std::vector<std::string> results;
            boost::split(results, line, [](char c) { return c == ','; });
            data.emplace_back(static_cast<T>(std::stod(results[0])), static_cast<T>(std::stod(results[1])));
        }
        return data;
    }

    static std::unordered_map<WindowType, std::string> AssociatedFile = {
        {WindowType::Blackman, data_path("hilbert_blackman.csv")},
        {WindowType::Hamming, data_path("hilbert_hamming.csv")},
        {WindowType::Hanning, data_path("hilbert_hanning.csv")},
    };
} // namespace

TEST(TestingHilbert, TransformHanningWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Hanning]);
    const auto size      = reference.size();
    std::vector<double> window(size);
    make_window<WindowType::Hanning>(std::begin(window), size);
    std::vector<std::complex<double>> transformed(size);
    easy::dsp::hilbert(std::begin(window), std::end(window), std::begin(transformed));

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(reference[i].real(), transformed[i].real(), 0.001);
        EXPECT_NEAR(reference[i].imag(), transformed[i].imag(), 0.001);
    }
}

TEST(TestingHilbert, TransformHammingWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Hamming]);
    const auto size      = reference.size();
    std::vector<double> window(size);
    make_window<WindowType::Hamming>(std::begin(window), size);
    std::vector<std::complex<double>> transformed(size);
    easy::dsp::hilbert(std::cbegin(window), std::cend(window), std::begin(transformed));

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(reference[i].real(), transformed[i].real(), 0.001);
        EXPECT_NEAR(reference[i].imag(), transformed[i].imag(), 0.001);
    }
}

TEST(TestingHilbert, TransformBlackmanWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Blackman]);
    const auto size      = reference.size();
    std::vector<double> window(size);
    make_window<WindowType::Blackman>(std::begin(window), size);
    std::vector<std::complex<double>> transformed(size);
    easy::dsp::hilbert(std::begin(window), std::end(window), std::begin(transformed));

    for (auto i = 0ul; i < size; ++i) {
        EXPECT_NEAR(reference[i].real(), transformed[i].real(), 0.001);
        EXPECT_NEAR(reference[i].imag(), transformed[i].imag(), 0.001);
    }
}
