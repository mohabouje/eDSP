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
 * Filename: testing_fft.cpp
 * Author: Mohammed Boujemaoui
 * Date: 8/9/2018
 */

#include <easy/dsp/windowing/windowing.hpp>
#include <easy/dsp/spectral/dft.hpp>
#include <easy/dsp/utilities/real2complex.hpp>

#include <gtest/gtest.h>
#include <unordered_map>
#include <fstream>
#include <istream>
#include <boost/algorithm/string.hpp>

using namespace easy::dsp::windowing;
using namespace easy::dsp::spectral;

std::string data_path(const std::string filename) {
    std::string path = CURRENT_TEST_PATH;
    path += "/spectral/data/fft/";
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
    {WindowType::Blackman, data_path("fft_blackman.csv")},
    {WindowType::Hamming, data_path("fft_hamming.csv")},
    {WindowType::Hanning, data_path("fft_hanning.csv")},
};

TEST(TestingFFT, TransformHanningWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Hanning]);
    const auto size      = reference.size();
    std::vector<double> window(size);
    make_window<WindowType::Hanning>(std::begin(window), size);

    std::vector<std::complex<double>> transformed(easy::dsp::make_fft_size(size));
    easy::dsp::dft(std::begin(window), std::end(window), std::begin(transformed));

    const auto middle = transformed.size();
    for (auto i = 0ul; i < middle; ++i) {
        EXPECT_NEAR(reference[i].real(), transformed[i].real(), 0.01);
        EXPECT_NEAR(reference[i].imag(), transformed[i].imag(), 0.01);
    }
}

TEST(TestingFFT, TransformHammingWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Hamming]);
    const auto size      = reference.size();
    std::vector<double> window(size);
    make_window<WindowType::Hamming>(std::begin(window), size);

    std::vector<std::complex<double>> transformed(easy::dsp::make_fft_size(size));
    easy::dsp::dft(std::begin(window), std::end(window), std::begin(transformed));

    const auto middle = transformed.size();
    for (auto i = 0ul; i < middle; ++i) {
        EXPECT_NEAR(reference[i].real(), transformed[i].real(), 0.01);
        EXPECT_NEAR(reference[i].imag(), transformed[i].imag(), 0.01);
    }
}

TEST(TestingFFT, TransformBlackmanWindow) {
    const auto reference = read_vector<double>(AssociatedFile[WindowType::Blackman]);
    const auto size      = reference.size();
    std::vector<double> window(size);
    make_window<WindowType::Blackman>(std::begin(window), size);

    std::vector<std::complex<double>> transformed(easy::dsp::make_fft_size(size));
    easy::dsp::dft(std::begin(window), std::end(window), std::begin(transformed));

    const auto middle = transformed.size();
    for (auto i = 0ul; i < middle; ++i) {
        EXPECT_NEAR(reference[i].real(), transformed[i].real(), 0.01);
        EXPECT_NEAR(reference[i].imag(), transformed[i].imag(), 0.01);
    }
}

TEST(TestingIFFT, InverseTransformRealData) {
    const auto size = 512ul;
    std::vector<double> window(size);
    make_window<WindowType::Hamming>(std::begin(window), size);

    std::vector<std::complex<double>> transformed(easy::dsp::make_fft_size(size));
    std::vector<double> inverse(window.size());
    easy::dsp::dft(std::begin(window), std::end(window), std::begin(transformed));
    easy::dsp::idft(std::begin(transformed), std::end(transformed), std::begin(inverse));

    for (auto i = 0ul; i < window.size(); ++i) {
        EXPECT_NEAR(inverse[i], window[i], 0.001);
    }
}

TEST(TestingIFFT, InverseTransformComplexData) {
    const auto size = 512ul;
    std::vector<double> window(size);
    make_window<WindowType::Blackman>(std::begin(window), size);

    std::vector<std::complex<double>> input(window.size()), inverse(window.size()), transformed(window.size());
    easy::dsp::real2complex(window.begin(), window.end(), std::begin(input));
    easy::dsp::cdft(std::begin(input), std::end(input), std::begin(transformed));
    easy::dsp::cidft(std::begin(transformed), std::end(transformed), std::begin(inverse));
    for (auto i = 0ul; i < window.size(); ++i) {
        EXPECT_NEAR(inverse[i].real(), input[i].real(), 0.001);
        EXPECT_NEAR(inverse[i].imag(), input[i].imag(), 0.001);
    }
}
