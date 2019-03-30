
/*
* edsp, Yet another framework for building deep RNN networks written in modern C++.
*
* The 2-Clause BSD License
*
* Copyright (c) 2019 Mohammed Boujemaoui Boulaghmoudi,
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Filename: spectral.c
* Author: Mohammed Boujemaoui
* Date: 26/03/19
*/

#include "spectral.h"
#include <edsp/spectral/cepstrum.hpp>
#include <edsp/spectral/convolution.hpp>
#include <edsp/spectral/correlation.hpp>
#include <edsp/spectral/dct.hpp>
#include <edsp/spectral/dft.hpp>
#include <edsp/spectral/periodogram.hpp>
#include <edsp/spectral/hilbert.hpp>
#include <edsp/spectral/hartley.hpp>

void cepstrum(const real_t *data, int size, real_t *ceps) {
    edsp::cepstrum(data, data + size, ceps);
}

void conv(const real_t *first, const real_t *second, int size, real_t *conv) {
    edsp::conv(first, first + size, second, conv);
}

void xcorr(const real_t *first, const real_t *second, int size, real_t *corr) {
    edsp::xcorr(first, first + size, second, corr);
}

void dct(const real_t *input, int size, real_t *output) {
    edsp::dct(input, input + size, output);
}

void idct(const real_t *input, int size, real_t *output) {
    edsp::idct(input, input + size, output);
}

void hartley(const real_t *data, int size, real_t *output) {
    edsp::hartley(data, data + size, output);
}

void periodogram(const real_t *data, int size, real_t *period) {
    edsp::periodogram(data, data + size, period, edsp::spectral_scale::linear);
}

int get_fft_size(int real_data_size) {
    return edsp::make_fft_size(real_data_size);
}

int get_ifft_size(int complex_data_size) {
    return edsp::make_ifft_size(complex_data_size);
}

void hilbert(const real_t *data, int size, complex_t *output) {
    auto* out = reinterpret_cast<std::complex<real_t>*>(output);
    edsp::hilbert(data, data + size, out);
}

void fft(const real_t *input, int size, complex_t *output) {
    auto* out = reinterpret_cast<std::complex<real_t>*>(output);
    edsp::dft(input, input + size, out);
}

void ifft(const complex_t *input, int size, real_t *output) {
    const auto* in = reinterpret_cast<const std::complex<real_t>*>(input);
    edsp::idft(in, in + size, output);
}

void complex_fft(const complex_t *input, int size, complex_t *output) {
    const auto* in = reinterpret_cast<const std::complex<real_t>*>(input);
    auto* out = reinterpret_cast<std::complex<real_t>*>(output);
    edsp::cdft(in, in + size, out);
}

void complex_ifft(const complex_t *input, int size, complex_t *output) {
    const auto* in = reinterpret_cast<const std::complex<real_t>*>(input);
    auto* out = reinterpret_cast<std::complex<real_t>*>(output);
    edsp::cidft(in, in + size, out);
}
