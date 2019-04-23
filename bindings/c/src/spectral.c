/*
* eDSP, A cross-platform Digital Signal Processing library written in modern C++.
* Copyright (C) 2019 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
* You should have received a copy of the GNU General Public License along width
* this program.  If not, see <http://www.gnu.org/licenses/>
*
* Filename: spectral.c
* Author: Mohammed Boujemaoui
* Date: 26/03/19
*/

#include "cedsp/spectral.h"
#include <edsp/spectral/cepstrum.hpp>
#include <edsp/spectral/convolution.hpp>
#include <edsp/spectral/correlation.hpp>
#include <edsp/spectral/dct.hpp>
#include <edsp/spectral/dft.hpp>
#include <edsp/spectral/spectrum.hpp>
#include <edsp/spectral/hilbert.hpp>
#include <edsp/spectral/hartley.hpp>

void cepstrum(const real_t* data, int size, real_t* ceps) {
    edsp::cepstrum(data, data + size, ceps);
}

void conv(const real_t* first, const real_t* second, int size, real_t* conv) {
    edsp::conv(first, first + size, second, conv);
}

void xcorr(const real_t* first, const real_t* second, int size, real_t* corr) {
    edsp::xcorr(first, first + size, second, corr);
}

void dct(const real_t* input, int size, real_t* output) {
    edsp::dct(input, input + size, output);
}

void idct(const real_t* input, int size, real_t* output) {
    edsp::idct(input, input + size, output);
}

void hartley(const real_t* data, int size, real_t* output) {
    edsp::hartley(data, data + size, output);
}

void spectrum(const real_t* data, int size, real_t* period) {
    edsp::spectrum(data, data + size, period);
}

int get_fft_size(int real_data_size) {
    return edsp::make_fft_size(real_data_size);
}

int get_ifft_size(int complex_data_size) {
    return edsp::make_ifft_size(complex_data_size);
}

void hilbert(const real_t* data, int size, complex_t* output) {
    auto* out = reinterpret_cast<std::complex<real_t>*>(output);
    edsp::hilbert(data, data + size, out);
}

void fft(const real_t* input, int size, complex_t* output) {
    auto* out = reinterpret_cast<std::complex<real_t>*>(output);
    edsp::dft(input, input + size, out);
}

void ifft(const complex_t* input, int size, real_t* output) {
    const auto* in = reinterpret_cast<const std::complex<real_t>*>(input);
    edsp::idft(in, in + size, output);
}

void complex_fft(const complex_t* input, int size, complex_t* output) {
    const auto* in = reinterpret_cast<const std::complex<real_t>*>(input);
    auto* out      = reinterpret_cast<std::complex<real_t>*>(output);
    edsp::cdft(in, in + size, out);
}

void complex_ifft(const complex_t* input, int size, complex_t* output) {
    const auto* in = reinterpret_cast<const std::complex<real_t>*>(input);
    auto* out      = reinterpret_cast<std::complex<real_t>*>(output);
    edsp::cidft(in, in + size, out);
}
