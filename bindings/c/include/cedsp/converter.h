/**
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
* Filename: converter.h
* Author: Mohammed Boujemaoui
* Date: 2019-03-31
*/

#ifndef EDSP_BINDING_C_CONVERTER_H
#define EDSP_BINDING_C_CONVERTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cedsp/types.h"

/**
 * @brief Converts a range of complex numbers in to two separates arrays holding
 * the real and complex part
 */
void complex2real(const complex_t* complex, long size, real_t* real, real_t* imag);

/**
 * @brief Converts a range of scalar numbers in to an equivalent complex number
 * and stores the result in another range.
 */
void ri2complex(const real_t *real, const real_t *imag, long size, complex_t *complex);

/**
 * @brief Converts a range of scalar numbers in to an equivalent complex number
 * and stores the result in another range.
 */
void real2complex(const real_t* real, long size, complex_t* complex);

/**
 * @brief Converts decibels to magnitude.
 */
real_t db2mag(real_t db);

/**
 * @brief Converts decibels to power.
 */
real_t db2pow(real_t db);

/**
 * @brief Converts degrees to radians.
 */
real_t deg2rad(real_t deg);

/**
 * @brief Converts magnitudes to decibels.
 */
real_t mag2db(real_t mag);

/**
 * @brief Maximum-to-minimum difference in the input array
 */
real_t peak2peak(const real_t* data, long size);

/**
 * @param Maximum Peak-magnitude-to-RMS ratio in the input array
 */
real_t peak2rms(const real_t* data, long size);

/**
 * @brief Converts power to decibels
 */
real_t pow2db(real_t power);

/**
 * @brief Converts radians to degrees.
 */
real_t rad2deg(real_t rad);


#ifdef __cplusplus
}
#endif

#endif //EDSP_BINDING_C_CONVERTER_H
