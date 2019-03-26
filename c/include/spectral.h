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
* Filename: spectral.h
* Author: Mohammed Boujemaoui
* Date: 26/03/19
*/

#ifndef EDSP_BINDING_C_SPECTRAL_H
#define EDSP_BINDING_C_SPECTRAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/**
 * @brief Computes the expected FFT size for a real-to-complex FFT transform
 * @returns Size of the FFT
 */
int get_fft_size(int real_data_size);

/**
 * @brief Computes the expected IFFT size for a complex-to-real IFFT transform
 * @returns Size of the IFFT
 */
int get_ifft_size(int complex_data_size);

/**
 * @brief Computes the cepstrum of the input range
 * @param data Input array
 * @param size Length of the input array
 * @param ceps Output array storing the cepstrum
 */
void cepstrum(const real_t* data, int size, real_t* ceps);

/**
 * @brief Computes the convolution between the first and second input
 * @param first First input array
 * @param second Second input array
 * @param size Length of the input array
 * @param con Convolution between both inputs
 */
void conv(const real_t* first, const real_t* second, int size, real_t* conv);

/**
 * @brief Computes the correlation between the first and second input
 * @param first First input array
 * @param second Second input array
 * @param size Length of the input array
 * @param corr Correlation between both inputs
 */
void xcorr(const real_t* first, const real_t* second, int size, real_t* corr);

/**
 * @brief Computes the Hartley transform of the input buffer
 * @param data Input array
 * @param size Length of the input array
 * @param hart Output array storing the Hartley transform
 */
void hartley(const real_t* data, int size, real_t* hart);

/**
 * @brief Computes the Hilbert transform of the input buffer
 * @param data Input array
 * @param size Length of the input array
 * @param hilb Output array storing the Hilbert transform
 */
void hilbert(const real_t* data, int size, real_t* hilb);

/**
 * @brief Computes the spectrogram of the input buffer
 * @param data Input array
 * @param size Length of the input array
 * @param period Output array storing the spectrogram transform
 */
void periodogram(const real_t* data, int size, real_t* period);

/**
 * @brief Computes the DCT transform of the input buffer
 * @param data Input array
 * @param size Length of the input array
 * @param output Output array storing the DCT transform
 */
void dct(const real_t* input, int size, real_t* output);

/**
 * @brief Computes the inverse DCT transform of the input buffer
 * @param data Input array
 * @param size Length of the input array
 * @param output Output array storing the inverse DCT transform
 */
void idct(const real_t* input, int size, real_t* output);

/**
 * @brief Computes the real-FFT transform of the input buffer
 * @param data Input array
 * @param size Length of the input array
 * @param output Output array storing the real-FFT transform
 */
void fft(const real_t* input, int size, complex_t* output);

/**
 * @brief Computes the inverse real-FFT transform of the input buffer
 * @param data Input array
 * @param size Length of the input array
 * @param output Output array storing the inverse real-FFT transform
 */
void ifft(const complex_t* input, int size, real_t* output);

/**
 * @brief Computes the complex-FFT transform of the input buffer
 * @param data Input array
 * @param size Length of the input array
 * @param output Output array storing the complex-FFT transform
 */
void complex_fft(const complex_t* input, int size, complex_t* output);

/**
 * @brief Computes the inverse complex-FFT transform of the input buffer
 * @param data Input array
 * @param size Length of the input array
 * @param output Output array storing the inverse complex-FFT transform
 */
void complex_ifft(const complex_t* input, int size, complex_t* output);


#ifdef __cplusplus
}
#endif

#endif //EDSP_BINDING_C_SPECTRAL_H
