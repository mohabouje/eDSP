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

/**
 * @brief Computes a rectangular window of length N and stores the result in the array.
 * @param window Array storing the window data
 * @param N Length of the array
 */
void rectangular(real_t* window, int N);

#ifdef __cplusplus
}
#endif

#endif //EDSP_BINDING_C_WINDOWING_H
