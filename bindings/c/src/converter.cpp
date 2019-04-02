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
* Filename: converter.cpp
* Author: Mohammed Boujemaoui
* Date: 2019-03-31
*/

#include "cedsp/converter.h"
#include <edsp/converter.hpp>

real_t rad2deg(real_t rad) {
    return edsp::rad2deg(rad);
}

real_t pow2db(real_t power) {
    return edsp::pow2db(power);
}

real_t peak2rms(const real_t* data, long size) {
    return edsp::peak2rms(data, data + size);
}

real_t peak2peak(const real_t *data, long size) {
    return edsp::peak2peak(data, data + size);
}

real_t mag2db(real_t mag) {
    return edsp::mag2db(mag);
}

real_t deg2rad(real_t deg) {
    return edsp::deg2rad(deg);
}

real_t db2pow(real_t db) {
    return edsp::db2pow(db);
}

real_t db2mag(real_t db) {
    return edsp::db2mag(db);
}

void real2complex(const real_t *real, long size, complex_t *complex) {
    auto* iter = reinterpret_cast<std::complex<real_t>*>(complex);
    edsp::real2complex(real, real + size, iter);
}

void complex2real(const complex_t *complex, long size, real_t *real, real_t *imag) {
    auto* iter = reinterpret_cast<const std::complex<real_t>*>(complex);
    edsp::complex2real(iter, iter + size, real, imag);
}

void ri2complex(const real_t *real, const real_t *imag, long size, complex_t *complex) {
    auto* iter = reinterpret_cast<std::complex<real_t>*>(complex);
    edsp::real2complex(real, real + size, imag, iter);
}
