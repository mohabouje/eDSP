/*
 * eDSP, A cross-platform DSP framework written in C++.
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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef EDSP_FREQUENCY_IDCT_H
#define EDSP_FREQUENCY_IDCT_H

#include "dct.h"
EDSP_BEGIN_NAMESPACE

/**
 * @brief The IDCT class implemented the Inverse DCT
 *
 * See @DCT for more details.
 */
class IDCT : public DCT {
    EDSP_DECLARE_MOVE_IMPLICITS(IDCT)
public:
    /**
     * @brief IDCT Creates a IDCT object with the given size and implementation
     * @param size Number of samples to be used in the computation
     * @param type Type of implementation: DCT-I, DCT-II, DCT-III or DCT-IV
     */
    explicit IDCT(std::size_t size, DCT_Type type = DCT_Type::Type_I);
    ~IDCT() EDSP_OVERRIDE;
private:
    EDSP_INLINE fftw_r2r_kind format() const EDSP_NOEXCEPT EDSP_OVERRIDE;
};

IDCT::IDCT(std::size_t size, DCT_Type type) : DCT(size, type) {
    build_plan();
}

fftw_r2r_kind IDCT::format() const EDSP_NOEXCEPT {
    switch(type()) {
        case DCT_Type::Type_I: return FFTW_REDFT00;
        case DCT_Type::Type_II: return FFTW_REDFT10;
        case DCT_Type::Type_III: return FFTW_REDFT01;
        case DCT_Type::Type_IV: return FFTW_REDFT11;
    }
}

EDSP_END_NAMESPACE
#endif //EDSP_FREQUENCY_IDCT_H
