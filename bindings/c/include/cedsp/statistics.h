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
* Filename: statistics.h
* Author: Mohammed Boujemaoui
* Date: 26/03/19
*/

#ifndef EDSP_BINDING_C_STATISTICS_H
#define EDSP_BINDING_C_STATISTICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

struct Peak {
    int index;
    real_t value;
};

/**
 * @brief Computes the kurtosis value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Kurtosis of the input array
 */
real_t kurtosis(const real_t* data, int size);

/**
 * @brief Computes the skewness value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Skewness of the input array
 */
real_t skewness(const real_t* data, int size);
/**
 * @brief Computes the nth-moment value of the input data
 * @param data Input array
 * @param size Length of the array
 * @param N Order of the moment.
 * @return Nth-Moment value of the input array
 */
real_t moment(const real_t* data, int size, int n);
/**
 * @brief Computes the geometric mean value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Geometric-Mean of the input array
 */
real_t geometric_mean(const real_t* data, int size);

/**
 * @brief Computes the generalized mean value of the input data
 * @param data Input array
 * @param size Length of the array
 * @param beta Exponent (\f$ \beta \f$).
 * @return Generalized-Mean of the input array
 */
real_t generalized_mean(const real_t* data, int size, int beta);

/**
 * @brief Computes the harmonic mean value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Harmonic-Mean of the input array
 */
real_t harmonic_mean(const real_t* data, int size);

/**
 * @brief Computes the maximum value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Maximum value of the input array
 */
real_t max(const real_t* data, int size);

/**
 * @brief Computes the minimum value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Minimum value of the input array
 */
real_t min(const real_t* data, int size);

/**
 * @brief Computes the peak value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Peak value of the input array
 */
struct Peak peak(const real_t* data, int size);

/**
 * @brief Computes the maximum absolute value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Maximum absolute value of the input array
 */
real_t max_abs(const real_t* data, int size);

/**
 * @brief Computes the minimum absolute value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Minimum absolute value of the input array
 */
real_t min_abs(const real_t* data, int size);

/**
 * @brief Computes the peak absolute value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Peak absolute value of the input array
 */
struct Peak peak_abs(const real_t* data, int size);

/**
 * @brief Computes the average value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Average value of the input array
 */
real_t mean(const real_t* data, int size);

/**
 * @brief Computes the median value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Median value of the input array
 */
real_t median(const real_t* data, int size);

/**
 * @brief Computes the variance value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Variance value of the input array
 */
real_t variance(const real_t* data, int size);

/**
 * @brief Computes the standard deviation value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return Standard deviation value of the input array
 */
real_t standard_deviation(const real_t* data, int size);

/**
 * @brief Computes the L2-Norm value of the input data
 * @param data Input array
 * @param size Length of the array
 * @return L2-Norm value of the input array
 */
real_t norm(const real_t* data, int size);


#ifdef __cplusplus
}
#endif
#endif //EDSP_BINDING_C_STATISTICS_H
