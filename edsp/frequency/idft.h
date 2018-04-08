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
#ifndef EDSP_IFFT_H
#define EDSP_IFFT_H

#include "transform.h"
#include <complex>
EDSP_BEGIN_NAMESPACE

/**
 * @brief The IDFT class implements the Inverse DFT.
 *
 * The IDFT is defined as such:
 * \f[
 *    \displaystyle x_{n}={\frac {1}{N}}\sum _{k=0}^{N-1}X_{k}e^{{\frac {2\pi i}{N}}kn}\quad \quad n=0,\dots ,N-1.
 * \f]
 *
 * See @DFT for mor details.
 */
class IDFT : public Transform<std::complex<edsp::real_t>, edsp::real_t> {
    EDSP_DECLARE_MOVE_IMPLICITS(IDFT)
public:
    /**
     * @brief IDFT Creates a IDFT with the given size
     * @param size Number of samples to be used in the computation
     */
    IDFT(std::size_t size);
    ~IDFT() EDSP_OVERRIDE;

    /**
     * @brief scale_output Scale the output of the IDFT
     */
    EDSP_INLINE void scale_output();
protected:
    EDSP_INLINE void build_plan() EDSP_OVERRIDE;
    EDSP_INLINE void execute_plan() EDSP_OVERRIDE;
};

IDFT::IDFT(std::size_t size) : Transform<std::complex<edsp::real_t>, edsp::real_t>(size) {
    build_plan();
}

IDFT::~IDFT() = default;

void IDFT::scale_output() {
    auto sz =  static_cast<edsp::real_t>(size());
    for (auto& out : _output) {
        out /= sz;
    }
}

void IDFT::build_plan() {
    auto plan = fftw_plan_dft_c2r_1d(static_cast<int>(size()),
                                     reinterpret_cast<fftw_complex *>(_input.data()),
                                _output.data(),
                                FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
    make_plan(&plan);
}

void IDFT::execute_plan() {
    fftw_execute_dft_c2r(*_plan, reinterpret_cast<fftw_complex *>(_input.data()), _output.data());
}

EDSP_END_NAMESPACE

#endif //EDSP_IFFT_H
