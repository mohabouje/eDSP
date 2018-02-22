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
#include "windowing/bartlett.h"
#include <cmath>

using namespace edsp;
Bartlett::Bartlett(edsp::Window::size_type size) : Window(size) {

}

Bartlett::~Bartlett() = default;

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
