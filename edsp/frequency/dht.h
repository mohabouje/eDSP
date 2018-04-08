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
#ifndef EDSP_FREQUENCY_DHT_H
#define EDSP_FREQUENCY_DHT_H

#include "transform.h"
EDSP_BEGIN_NAMESPACE
/**
 * @brief The DHT class implements a Discrete Hilbert Transform (DHT)
 *
 * This is an special transform function that can be considered to be a filter which simply shifts phases
 * of all frequency components of its input by \$[ - \pi / 2 \$] radians.
 */
class DHT : public Transform<edsp::real_t, edsp::real_t> {
    EDSP_DECLARE_MOVE_IMPLICITS(DHT)
public:
    /**
     * @brief DHT Creates a DHT with the given size
     * @param size Number of samples to be computed
     */
    explicit DHT(std::size_t size);
    ~DHT() EDSP_OVERRIDE;
private:
    EDSP_INLINE void build_plan() EDSP_OVERRIDE;
    EDSP_INLINE void execute_plan() EDSP_OVERRIDE;
};

DHT::DHT(std::size_t size) : Transform<edsp::real_t, edsp::real_t>(size) {
    build_plan();
}

DHT::~DHT() = default;

void DHT::build_plan() {
    auto plan = fftw_plan_r2r_1d(static_cast<int>(size()),
                                 _input.data(),
                                 _output.data(),
                                 FFTW_DHT,
                                 FFTW_MEASURE);
    make_plan(&plan);
}

void DHT::execute_plan() {
    fftw_execute_r2r(*_plan, _input.data(), _output.data());

}

EDSP_END_NAMESPACE
#endif //EDSP_FREQUENCY_DHT_H
