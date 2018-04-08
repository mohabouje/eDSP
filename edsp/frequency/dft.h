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
#ifndef EDSP_FREQUENCY_DFT_H
#define EDSP_FREQUENCY_DFT_H

#include "transform.h"
#include <complex>
EDSP_BEGIN_NAMESPACE

/**
 * @brief The DFT class computes a Discrete-Time Fourier Transform (DFT)
 *
 * The DFT converts a discrete-time data set in to a discrete-frequency representation.
 *
 * For a sequence of length N, the DFT is defined as such:
 * \f[
 *   \displaystyle X[k]=\sum _{n=0}^{N-1}x[n]e^{\frac {-j2\pi kn}{N}}}
 * \f]
 *
 * Define a number bigger than the input size N to increase the spectral resolution. In that case,
 * the buffer will be sufixed with zeros.
 *
 * For the best performance, N should be a power of two.
 */
class DFT : public Transform<edsp::real_t, std::complex<edsp::real_t>> {
    EDSP_DECLARE_MOVE_IMPLICITS(DFT)
public:
    /**
     * @brief Creates a DFT class with the given size
     * @param size Number of samples to compute in the FFT
     */
    explicit DFT(std::size_t size);
    ~DFT() EDSP_OVERRIDE;
private:
    EDSP_INLINE void build_plan() EDSP_OVERRIDE;
    EDSP_INLINE void execute_plan() EDSP_OVERRIDE;
};

DFT::DFT(std::size_t size) : Transform<edsp::real_t, std::complex<edsp::real_t>>(size) {
    build_plan();
}

DFT::~DFT() = default;

void DFT::build_plan() {
    auto plan = fftw_plan_dft_r2c_1d(static_cast<int>(size()), _input.data(),
                                      reinterpret_cast<fftw_complex *>(_output.data()), FFTW_ESTIMATE);
    make_plan(&plan);
}

void DFT::execute_plan() {
    fftw_execute_dft_r2c(*_plan, _input.data(),
                         reinterpret_cast<fftw_complex *>(_output.data()));
}

EDSP_END_NAMESPACE



#endif //EDSP_FREQUENCY_DFT_H
