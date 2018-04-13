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

#ifndef EDSP_WINDOW_BOHMAN_H
#define EDSP_WINDOW_BOHMAN_H

#include "window.hpp"
#include "base/constants.h"
#include <cmath>

EDSP_BEGIN_NAMESPACE
/**
 * @brief Bohman %window implementation.
 *
 * See also: Rectangular and Bartlett
 */
class Bohman : Window {
    EDSP_DECLARE_ALL_IMPLICITS(Bohman)
public:
    /**
     * @brief Creates and computes a Bohman %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Bohman(_In_ size_type size);

    ~Bohman() EDSP_OVERRIDE;

    EDSP_INLINE void initialize() EDSP_OVERRIDE;
};

Bohman::Bohman(Window::size_type size) : Window(size) {

}

void Bohman::initialize() {
    if (!empty()) {
        const value_type N = size() - 1;
        value_type initial = -N / 2.0;
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            data_[i] = (1 - 2. * std::abs(initial) / N) * std::cos(constants<value_type>::two_pi * std::abs(initial) / N)
                       + constants<value_type>::one_div_pi * std::sin(constants<value_type>::two_pi * std::abs(initial) / N);
            ++initial;
        }

        data_[0] = 0.;
        data_[size() - 1] = 0.;
    }
}

Bohman::~Bohman() = default;
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_BOHMAN_H
