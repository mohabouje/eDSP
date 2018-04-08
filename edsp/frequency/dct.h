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
#ifndef EDSP_FREQUENCY_DCT_H
#define EDSP_FREQUENCY_DCT_H

#include "transform.h"
EDSP_BEGIN_NAMESPACE

/**
 * @brief The DCT_Type enum Type of implementation to be used in the DCT & IDCT class.
 */
enum class DCT_Type { Type_I = 0, Type_II, Type_III, Type_IV};

/**
 * @brief The DCT class implements a Discrete Cosine Transform (DCT)
 *
 * The Discrete Cosine Transform (DCT) expresses a finite sequence of data points
 * in terms of a sum of cosine functions oscillating at different frequencies.
 *
 * There are several implementations:
 *
 *  DCT-I
 *  DCT-II
 *  DCT-III
 *  DCT-IV
 *
 *  By default the class uses DCT-I type.
 *
 *  The main difference with the DFT: the DCT use only real numbers.
 */
class DCT : public Transform<edsp::real_t, edsp::real_t> {
    EDSP_DECLARE_MOVE_IMPLICITS(DCT)
public:
    /**
     * @brief DCT Creates a DCT object with the given size and implementation
     * @param size Number of samples to be used in the computation
     * @param type Type of implementation: DCT-I, DCT-II, DCT-III or DCT-IV
     */
    explicit DCT(std::size_t size, DCT_Type type = DCT_Type::Type_I);
    ~DCT() EDSP_OVERRIDE;

    /**
     * @brief Returns the current implementation that is used for the computations
     * @return Current type: DCT-I, DCT-II, DCT-III or DCT-IV
     */
    EDSP_INLINE DCT_Type type() const EDSP_NOEXCEPT;

    /**
     * @brief setType Set the type of implementations to be computed
     * @param type Type to be used: DCT-I, DCT-II, DCT-III or DCT-IV
     */
    EDSP_INLINE void setType(DCT_Type type) EDSP_NOEXCEPT;
protected:
    EDSP_INLINE virtual fftw_r2r_kind format() const EDSP_NOEXCEPT;
    EDSP_INLINE void build_plan() EDSP_OVERRIDE;
    EDSP_INLINE void execute_plan() EDSP_OVERRIDE;
private:
    DCT_Type _type{DCT_Type::Type_I};
};


DCT::DCT(std::size_t size, edsp::DCT_Type type) :
    Transform<edsp::real_t, edsp::real_t>(size),
    _type(type)
{
    build_plan();
}

DCT::~DCT() = default;

DCT_Type DCT::type() const EDSP_NOEXCEPT {
    return _type;
}

void DCT::setType(DCT_Type type) EDSP_NOEXCEPT {
    _type = type;
}

fftw_r2r_kind DCT::format() const EDSP_NOEXCEPT {
    switch(_type) {
        case DCT_Type::Type_I: return FFTW_REDFT00;
        case DCT_Type::Type_II: return FFTW_REDFT10;
        case DCT_Type::Type_III: return FFTW_REDFT01;
        case DCT_Type::Type_IV: return FFTW_REDFT11;
    }
}

void DCT::build_plan() {
    auto plan = fftw_plan_r2r_1d(static_cast<int>(size()),
                                 _input.data(),
                                 _output.data(),
                                 format(),
                                 FFTW_ESTIMATE);
    make_plan(&plan);
}

void DCT::execute_plan() {
    fftw_execute_r2r(*_plan, _input.data(), _output.data());
}


EDSP_END_NAMESPACE

#endif //EDSP_FREQUENCY_DCT_H
