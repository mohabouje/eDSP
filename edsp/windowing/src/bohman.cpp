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

#include "windowing/bohman.h"
#include "base/constants.h"
#include <cmath>
using namespace edsp;

Bohman::Bohman(Window::size_type size) : Window(size) {

}

Bohman::~Bohman() = default;

void Bohman::initialize() {
    if (!empty()) {
        const value_type N = size() - 1;
        value_type initial = -N / 2.0;
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            data_[i] = (1 - 2. * std::abs(initial) / N) * std::cos(2. * constants<value_type>::pi * std::abs(initial) / N)
                       + ( 1. / constants<value_type>::pi) * std::sin(2. * constants<value_type>::pi * std::abs(initial) / N);
            ++initial;
        }

        data_[0] = 0.;
        data_[N] = 0.;
    }
}
