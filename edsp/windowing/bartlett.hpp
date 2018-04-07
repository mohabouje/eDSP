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
#ifndef EDSP_BARTLETT_H
#define EDSP_BARTLETT_H

#include "window.hpp"
#include <cmath>

EDSP_BEGIN_NAMESPACE
/**
 * @brief Bartlett %window implementation.
 * The following equation defines the N–point Parzen window over the interval \f$ -\frac{N-1}{2} \leqslant  n \leqslant  \frac{N-1}{2}  \f$:
 *
 * \f[
        {\displaystyle w(n)=\left\{{\begin{array}{ll} \frac {2n}{N-1}, &0 \leqslant n < {\frac {N-1}{2}}
        \\2 - \frac {2n}{N-1},&{\frac {N-1}{2}}\leqslant n\leqslant N-1\\\end{array}}\right.}
 * \f]
 */
class Bartlett : Window {
public:

    /**
     * @brief Creates and computes a Bartlett %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Bartlett(_In_ size_type size);
    ~Bartlett() EDSP_OVERRIDE;

    EDSP_INLINE void initialize() EDSP_OVERRIDE;
};

Bartlett::Bartlett(Window::size_type size) : Window(size) {

}

Bartlett::~Bartlett() {

}

void Bartlett::initialize() {
    if (!empty()) {
        const value_type N = size() - 1;
        value_type half = 0;
        std::modf(N / 2., &half);
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            data_[i] = ((i <= half) ? 2 * i : (2 - 2 * i)) / N;
        }
    }
}

EDSP_END_NAMESPACE

#endif //EDSP_BARTLETT_H
