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

#ifndef EDSP_WINDOW_TRIANGULAR_H
#define EDSP_WINDOW_TRIANGULAR_H

#include "window.hpp"
#include <cmath>

EDSP_BEGIN_NAMESPACE

/**
 * @brief Triangular %window implementation.
 *
 * Unlike the Bartlett %window, this %window does not go to zero at the edge of the %window.
 *
 * See also: Bartlett
 *
 */
class Triangular : Window {
public:

    /**
     * @brief Creates and computes a Triangular %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Triangular(_In_ size_type size);
    ~Triangular() EDSP_OVERRIDE;

    EDSP_INLINE void initialize() EDSP_OVERRIDE;
};

Triangular::Triangular(_In_ Window::size_type size) : Window(size) {

}

Triangular::~Triangular() = default;

void Triangular::initialize() {
    if (!empty()) {
        const size_type sz = size();
        const value_type rem = sz + std::remainder(sz, 2);
        value_type initial = -(sz - 1);
        for (size_type i = 0; i < sz; ++i) {
            data_[i] = 1 - std::abs(initial / rem);
            initial += 2;
        }
    }
}

EDSP_END_NAMESPACE
#endif //EDSP_TRIANGULAR_H
