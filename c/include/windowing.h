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
* Filename: windowing.h
* Author: Mohammed Boujemaoui
* Date: 26/03/19
*/

#ifndef EDSP_BINDING_C_WINDOWING_H
#define EDSP_BINDING_C_WINDOWING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/**
 * @brief Computes a Bartlett window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void bartlett(real_t* window, int N);

/**
 * @brief Computes a Blackman window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void blackman(real_t* window, int N);

/**
 * @brief Computes a Blackman-Harris window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void blackman_harris(real_t* window, int N);

/**
 * @brief Computes a Blackman-Nutall window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void blackman_nutall(real_t* window, int N);

/**
 * @brief Computes a Boxcar window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void boxcar(real_t* window, int N);

/**
 * @brief Computes a Flat-Top window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void flattop(real_t* window, int N);

/**
 * @brief Computes a Hamming window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void hamming(real_t* window, int N);

/**
 * @brief Computes a Hanning window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void hanning(real_t* window, int N);

/**
 * @brief Computes a Triangular window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void triangular(real_t* window, int N);

/**
 * @brief Computes a Welch window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void welch(real_t* window, int N);

#ifdef __cplusplus
}
#endif

#endif //EDSP_BINDING_C_WINDOWING_H
