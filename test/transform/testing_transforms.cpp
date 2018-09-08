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
 * Filename: testing_transforms.cpp
 * Created at: 10/06/18
 * Created by: Mohammed Boujemaoui
 */

#include <easy/dsp/transform/dct.hpp>
#include <easy/dsp/transform/dft.hpp>
#include <easy/dsp/utilities/real2complex.hpp>
#include <easy/meta/empty.hpp>
#include <easy/meta/size.hpp>
#include <catch/catch.hpp>

using namespace easy;

static constexpr std::array<float, 64> hamming = {{
    0.0800f, 0.0823f, 0.0891f, 0.1004f, 0.1161f, 0.1360f, 0.1599f, 0.1876f, 0.2188f, 0.2532f, 0.2904f, 0.3301f, 0.3719f,
    0.4154f, 0.4601f, 0.5056f, 0.5515f, 0.5972f, 0.6424f, 0.6865f, 0.7292f, 0.7700f, 0.8085f, 0.8444f, 0.8772f, 0.9067f,
    0.9325f, 0.9544f, 0.9723f, 0.9858f, 0.9949f, 0.9994f, 0.9994f, 0.9949f, 0.9858f, 0.9723f, 0.9544f, 0.9325f, 0.9067f,
    0.8772f, 0.8444f, 0.8085f, 0.7700f, 0.7292f, 0.6865f, 0.6424f, 0.5972f, 0.5515f, 0.5056f, 0.4601f, 0.4154f, 0.3719f,
    0.3301f, 0.2904f, 0.2532f, 0.2188f, 0.1876f, 0.1599f, 0.1360f, 0.1161f, 0.1004f, 0.0891f, 0.0823f, 0.0800f,
}};

static constexpr std::array<std::complex<float>, 64> hamming_fft = {
    {{34.1000f, 0.0000f}, {-14.8121f, -0.7277f}, {0.1589f, 0.0157f},  {0.0587f, 0.0087f},  {0.0309f, 0.0061f},
     {0.0190f, 0.0048f},  {0.0128f, 0.0039f},    {0.0091f, 0.0033f},  {0.0068f, 0.0028f},  {0.0052f, 0.0024f},
     {0.0040f, 0.0022f},  {0.0032f, 0.0019f},    {0.0026f, 0.0017f},  {0.0021f, 0.0016f},  {0.0017f, 0.0014f},
     {0.0014f, 0.0013f},  {0.0011f, 0.0011f},    {0.0009f, 0.0010f},  {0.0008f, 0.0009f},  {0.0006f, 0.0009f},
     {0.0005f, 0.0008f},  {0.0004f, 0.0007f},    {0.0003f, 0.0006f},  {0.0003f, 0.0005f},  {0.0002f, 0.0005f},
     {0.0001f, 0.0004f},  {0.0001f, 0.0003f},    {0.0001f, 0.0003f},  {0.0000f, 0.0002f},  {0.0000f, 0.0002f},
     {0.0000f, 0.0001f},  {0.0000f, 0.0001f},    {0.0000f, 0.0000f},  {0.0000f, -0.0001f}, {0.0000f, -0.0001f},
     {0.0000f, -0.0002f}, {0.0000f, -0.0002f},   {0.0001f, -0.0003f}, {0.0001f, -0.0003f}, {0.0001f, -0.0004f},
     {0.0002f, -0.0005f}, {0.0003f, -0.0005f},   {0.0003f, -0.0006f}, {0.0004f, -0.0007f}, {0.0005f, -0.0008f},
     {0.0006f, -0.0009f}, {0.0008f, -0.0009f},   {0.0009f, -0.0010f}, {0.0011f, -0.0011f}, {0.0014f, -0.0013f},
     {0.0017f, -0.0014f}, {0.0021f, -0.0016f},   {0.0026f, -0.0017f}, {0.0032f, -0.0019f}, {0.0040f, -0.0022f},
     {0.0052f, -0.0024f}, {0.0068f, -0.0028f},   {0.0091f, -0.0033f}, {0.0128f, -0.0039f}, {0.0190f, -0.0048f},
     {0.0309f, -0.0061f}, {0.0587f, -0.0087f},   {0.1589f, -0.0157f}, {-14.8121f, 0.7277f}}};

SCENARIO("Testing the integration with the FFTW library", "[FFT]") {
    GIVEN("A random input data") {
        // TODO: check why it is crashing with the normal required size
        constexpr auto sz        = 1024;
        constexpr auto fft_size  = sz; //easy::dsp::make_fft_size(sz);
        constexpr auto ifft_size = sz; //easy::dsp::make_ifft_size(fft_size);
        std::vector<std::complex<float>> input(sz);
        std::vector<std::complex<float>> data_fft(fft_size);
        std::vector<std::complex<float>> data_ifft(ifft_size);
        for (std::size_t i = 0; i < sz; ++i) {
            input[i] = std::complex<float>(i, i);
        }

        REQUIRE(!meta::empty(input));
        REQUIRE(meta::size(input) == meta::size(data_ifft));

        WHEN("We want to compute the fft and ifft to restore the original signal") {
            dsp::complex_dft<float>(input, data_fft);
            AND_WHEN("We compute the inverse fft") {
                dsp::complex_idft<float>(data_fft, data_ifft);
                THEN("The output data should be same as the original signal") {
                    for (std::size_t i = 0; i < sz; ++i) {
                        REQUIRE(input[i].real() == Approx(data_ifft[i].real()).margin(1));
                    }
                }
            }
        }
    }

    GIVEN("An input buffer storing a Hamming Window") {
        // TODO: check why it is crashing with the normal required size
        constexpr auto sz    = meta::size(hamming);
        const auto fft_size  = easy::dsp::make_fft_size(sz);
        const auto ifft_size = easy::dsp::make_ifft_size(fft_size);
        std::vector<std::complex<float>> input(sz);
        std::vector<std::complex<float>> data_fft(fft_size);
        std::vector<std::complex<float>> data_ifft(ifft_size);
        easy::dsp::real2complex(std::cbegin(hamming), std::cend(hamming), std::begin(input));

        REQUIRE(!meta::empty(input));
        REQUIRE(meta::size(input) == meta::size(data_ifft));

        WHEN("We want to compute the fft and ifft to restore the original signal") {
            dsp::complex_dft<float>(input, data_fft);
            AND_WHEN("We compute the inverse fft") {
                dsp::complex_idft<float>(data_fft, data_ifft);
                THEN("The output data should be same as the original signal") {
                    for (std::size_t i = 0; i < sz; ++i) {
                        REQUIRE(input[i].real() == Approx(data_ifft[i].real()));
                    }
                }
            }
        }

        WHEN("We want to compute the fft") {
            dsp::complex_dft<float>(input, data_fft);
            THEN("The output data should be same as the expected fft") {
                for (std::size_t i = 0; i < sz; ++i) {
                    REQUIRE(hamming_fft[i].real() == Approx(data_fft[i].real()).margin(0.01));
                    REQUIRE(hamming_fft[i].imag() == Approx(data_fft[i].imag()).margin(0.01));
                }
            }
        }
    }
}

SCENARIO("Testing the DCT implementation", "[DCT]") {
    GIVEN("A random input data") {
        constexpr auto sz = 1024;
        std::vector<float> input(sz), data_dct(sz), data_idct(sz);
        std::copy(std::begin(hamming), std::end(hamming), std::begin(input));

        REQUIRE(!meta::empty(input));
        REQUIRE(meta::size(input) == meta::size(data_dct));
        REQUIRE(meta::size(input) == meta::size(data_idct));

        WHEN("We want to compute the DCT-Type I") {
            dsp::dct(input, data_dct, dsp::DCT_Type::Type_I);
            AND_WHEN("We compute the inverse fft") {
                dsp::idct(data_dct, data_idct, dsp::DCT_Type::Type_I);
                THEN("The output data should be same as the original signal") {
                    for (std::size_t i = 0; i < sz; ++i) {
                        REQUIRE(input[i] == Approx(data_idct[i]).margin(0.01));
                    }
                }
            }
        }

        WHEN("We want to compute the DCT-Type II") {
            dsp::dct(input, data_dct, dsp::DCT_Type::Type_II);
            AND_WHEN("We compute the inverse fft") {
                dsp::idct(data_dct, data_idct, dsp::DCT_Type::Type_II);
                THEN("The output data should be same as the original signal") {
                    for (std::size_t i = 0; i < sz; ++i) {
                        REQUIRE(input[i] == Approx(data_idct[i]).margin(0.01));
                    }
                }
            }
        }

        WHEN("We want to compute the DCT-Type III") {
            dsp::dct(input, data_dct, dsp::DCT_Type::Type_III);
            AND_WHEN("We compute the inverse fft") {
                dsp::idct(data_dct, data_idct, dsp::DCT_Type::Type_III);
                THEN("The output data should be same as the original signal") {
                    for (std::size_t i = 0; i < sz; ++i) {
                        REQUIRE(input[i] == Approx(data_idct[i]).margin(0.01));
                    }
                }
            }
        }

        WHEN("We want to compute the DCT-Type IV") {
            dsp::dct(input, data_dct, dsp::DCT_Type::Type_IV);
            AND_WHEN("We compute the inverse fft") {
                dsp::idct(data_dct, data_idct, dsp::DCT_Type::Type_IV);
                THEN("The output data should be same as the original signal") {
                    for (std::size_t i = 0; i < sz; ++i) {
                        REQUIRE(input[i] == Approx(data_idct[i]).margin(0.01));
                    }
                }
            }
        }
    }
}
