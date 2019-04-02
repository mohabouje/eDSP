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
* Filename: algorithm.h
* Author: Mohammed Boujemaoui
* Date: 26/03/19
*/

#ifndef EDSP_BINDING_C_ALGORITHM_H
#define EDSP_BINDING_C_ALGORITHM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/**
 * @brief Amplifies or attenuates the elements in the input array and stores the result in the output array.
 *
 * This function increases the amplitude of the input signal defined in the range [first, last). The output signal is a
 * proportionally amplitude signal dependent of the scale factor (\f$ \alpha \f$):
 *
 * \f[
 *      y(n) = \alpha x(n)
 * \f]
 * @param input Input array
 * @param size Length of the input array
 * @param output Output array
 * @param factor Scale factor (\f$ \alpha \f$).
 */
void array_scale(const real_t *input, int size, real_t *output, real_t factor);


/**
 * @brief Amplifies or attenuates the elements in the input array and stores the result in the output array.
 * @note This function clips the input elements in the range [min, max]
 * @param input Input array
 * @param size Length of the input array
 * @param output Output array
 * @param factor Scale factor (\f$ \alpha \f$).
 * @param min Minimum threshold value.
 * @param max Maximum threshold value.
 */
void array_scale_clip(const real_t *input, int size, real_t *output, real_t factor, real_t min, real_t max);

/**
 * @brief Limits the values of the elements in the input array once it exceeds a threshold [min, max],
 * and stores the result in another array.
 *
 * @param input Input array
 * @param size Length of the input array
 * @param output Output array
 * @param min Minimum threshold value.
 * @param max Maximum threshold value.
 */

void array_clip(const real_t *input, int size, real_t *output, real_t min, real_t max);

/**
 * @brief Concatenates the elements defined in the left input and right output,
 * and stores the result in another output array.
 * @param left First input array
 * @param size_left Length of the first input array
 * @param right  Second input array
 * @param size_right Length of the second input array
 * @param output Output array of size size_left + size_right
 */
void array_concatenate(const real_t *left, int size_left, const real_t *right, int size_right, real_t *output);

/**
 * @brief For each element in the input array computes the smallest integer value not less than the element's value
 * and stores the result in the output array.
 * @param input Input array
 * @param size Length of the input array
 * @param output Output array
 */
void array_ceil(const real_t* input, int size, real_t* output);

/**
 * @brief For each element in the input array computes the largest integer value not greater than the element's value,
 * and stores the result in the output array.
 * @param input Input array
 * @param size Length of the input array
 * @param output Output array
 */
void array_floor(const real_t* input, int size, real_t* output);

/**
 * @brief For each element in the input array computes the nearest integer value to the element's value rounding
 * halfway cases away from zero, and stores the result in the output array.
 * @param input Input array
 * @param size Length of the input array
 * @param output Output array
 */
void array_round(const real_t* input, int size, real_t* output);

/**
 * @brief For each element in the input array computes the smallest integer value not less than the element's value
 * and stores the result in the output array.
 * @param input Input array
 * @param size Length of the input array
 * @param output Output array
 */
void array_trunc(const real_t* input, int size, real_t* output);

/**
 * @brief For each element in the input array computes the nearest integer not greater in magnitude than the element's
 * value and stores the result in the output array.
 * @param input Input array
 * @param size Length of the input array
 * @param output Output array
 */
void array_abs(const real_t *input, int size, real_t *output);

/**
 * @brief Generate N linearly spaced values between the range [x1,x2] and stores the result in the output array
 * @param output Output array
 * @param x1 Defines the beginning of the interval over which linspace generates points.
 * @param x2 Defines the ending of the interval over which linspace generates points.
 * @param N Number of points to generate.
 */
void array_linspace(real_t* output, int size, real_t x1, real_t x2);

/**
 * @brief Generate N logarithmic spaced values between the range [x1,x2] and stores the result in the output array
 * @param output Output array
 * @param x1 Defines the beginning of the interval over which logspace generates points.
 * @param x2 Defines the ending of the interval over which logspace generates points.
 * @param N Number of points to generate.
 */
void array_logspace(real_t* output, int size, real_t x1, real_t x2);

/**
 * @brief Extends the signal defined in the input array with zeros and stores the result in the output array.
 * @param input Input array
 * @param input_size Length of the input array
 * @param output Output array
 * @param output_size Length of the output array
 */
void array_padder(const real_t* input, int input_size, real_t* output, int output_size);

/**
 * @brief Normalizes the elements in the input array and stores the result in the output array.
 *
 * The denominator is the maximum absolute value of the signal.
 * \f[
 *      y = \frac{x}{\frac{\sum_{n=1}^{N}x(n)}{N}}
 * \f]
 * @param input Input array
 * @param size Length of the input array
 * @param output Output array
 */
void array_normalize(const real_t* input, int size, real_t* output);

/**
 * @brief Returns true if the elements of the inputs are equal, and false otherwise.
 * @param left First input range
 * @param size Length of the inputs
 * @param right Second input range
 * @return a positive integer if the arrays are equal, and false otherwise.
 */
int equal(const real_t *left, int size, const real_t *right);

/**
 * @brief Checks if an element equivalent to value appears within the range of the input buffer and returns the index.
 * @note This function assumes that the input array is sorted.
 * @param input Input array
 * @param size Length of the input array.
 * @param value Value to compare the elements to.
 * @return Index of the element if the element is found, -1 otherwise.
 */
int binary_search(const real_t* input, int size, real_t value);

/**
 * @brief Checks if an element equivalent to value appears within the range of the input buffer and returns the index.
 * @param input Input array
 * @param size Length of the input array.
 * @param value Value to compare the elements to.
 * @return Index of the element if the element is found, -1 otherwise.
 */
int linear_search(const real_t* input, int size, real_t value);

/**
 * @brief Checks if an element equivalent to value appears within the range of the input buffer and returns the index.
 * @param input Input array
 * @param size Length of the input array.
 * @param value Value to compare the elements to.
 * @return Index of the element if the element is found, -1 otherwise.
 */
int index_of(const real_t* input, int size, real_t value);

/**
 * @brief Checks if an element equivalent to value appears within the range of the input buffer.
 * @param input Input array
 * @param size Length of the input array.
 * @param value Value to compare the elements to.
 * @return A positive integer if the element is found, zero otherwise.
 */
int contains(const real_t* input, int size, real_t value);

#ifdef __cplusplus
}
#endif
#endif //EDSP_BINDING_C_ALGORITHM_H
