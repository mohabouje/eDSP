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
#include <easy/meta/meta.hpp>
#include <catch/catch.hpp>

using namespace easy;

static constexpr std::array<ereal, 64> hamming = {{
    0.0800, 0.0823, 0.0891, 0.1004, 0.1161, 0.1360, 0.1599, 0.1876, 0.2188, 0.2532, 0.2904, 0.3301, 0.3719,
    0.4154, 0.4601, 0.5056, 0.5515, 0.5972, 0.6424, 0.6865, 0.7292, 0.7700, 0.8085, 0.8444, 0.8772, 0.9067,
    0.9325, 0.9544, 0.9723, 0.9858, 0.9949, 0.9994, 0.9994, 0.9949, 0.9858, 0.9723, 0.9544, 0.9325, 0.9067,
    0.8772, 0.8444, 0.8085, 0.7700, 0.7292, 0.6865, 0.6424, 0.5972, 0.5515, 0.5056, 0.4601, 0.4154, 0.3719,
    0.3301, 0.2904, 0.2532, 0.2188, 0.1876, 0.1599, 0.1360, 0.1161, 0.1004, 0.0891, 0.0823, 0.0800,
}};

static constexpr std::array<std::complex<ereal>, 64> hamming_fft = {
    {{34.1000, 0.0000}, {-14.8121, -0.7277}, {0.1589, 0.0157},  {0.0587, 0.0087},  {0.0309, 0.0061},  {0.0190, 0.0048},
     {0.0128, 0.0039},  {0.0091, 0.0033},    {0.0068, 0.0028},  {0.0052, 0.0024},  {0.0040, 0.0022},  {0.0032, 0.0019},
     {0.0026, 0.0017},  {0.0021, 0.0016},    {0.0017, 0.0014},  {0.0014, 0.0013},  {0.0011, 0.0011},  {0.0009, 0.0010},
     {0.0008, 0.0009},  {0.0006, 0.0009},    {0.0005, 0.0008},  {0.0004, 0.0007},  {0.0003, 0.0006},  {0.0003, 0.0005},
     {0.0002, 0.0005},  {0.0001, 0.0004},    {0.0001, 0.0003},  {0.0001, 0.0003},  {0.0000, 0.0002},  {0.0000, 0.0002},
     {0.0000, 0.0001},  {0.0000, 0.0001},    {0.0000, 0.0000},  {0.0000, -0.0001}, {0.0000, -0.0001}, {0.0000, -0.0002},
     {0.0000, -0.0002}, {0.0001, -0.0003},   {0.0001, -0.0003}, {0.0001, -0.0004}, {0.0002, -0.0005}, {0.0003, -0.0005},
     {0.0003, -0.0006}, {0.0004, -0.0007},   {0.0005, -0.0008}, {0.0006, -0.0009}, {0.0008, -0.0009}, {0.0009, -0.0010},
     {0.0011, -0.0011}, {0.0014, -0.0013},   {0.0017, -0.0014}, {0.0021, -0.0016}, {0.0026, -0.0017}, {0.0032, -0.0019},
     {0.0040, -0.0022}, {0.0052, -0.0024},   {0.0068, -0.0028}, {0.0091, -0.0033}, {0.0128, -0.0039}, {0.0190, -0.0048},
     {0.0309, -0.0061}, {0.0587, -0.0087},   {0.1589, -0.0157}, {-14.8121, 0.7277}}};

SCENARIO("Testing the integration with the FFTW library", "[FFT]") {
    GIVEN("A random input data") {
        constexpr auto sz = 1024;
        std::vector<std::complex<ereal>> input(sz), data_fft(sz), data_ifft(sz);

        for (std::size_t i = 0; i < sz; ++i) {
            input[i] = std::complex<ereal>(i, i);
        }

        REQUIRE(meta::notempty(input));
        REQUIRE(std::size(input) == std::size(data_fft));
        REQUIRE(std::size(input) == std::size(data_ifft));

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
        constexpr auto sz = std::size(hamming);
        std::vector<std::complex<ereal>> input(sz), data_fft(sz), data_ifft(sz);

        for (std::size_t i = 0; i < sz; ++i) {
            input[i] = std::complex<ereal>(hamming[i], 0);
        }

        REQUIRE(meta::notempty(input));
        REQUIRE(std::size(input) == std::size(data_fft));
        REQUIRE(std::size(input) == std::size(data_ifft));

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
        std::vector<ereal> input(sz), data_dct(sz), data_idct(sz);
        std::copy(std::begin(hamming), std::end(hamming), std::begin(input));

        REQUIRE(meta::notempty(input));
        REQUIRE(std::size(input) == std::size(data_dct));
        REQUIRE(std::size(input) == std::size(data_idct));

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
