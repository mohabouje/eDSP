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

#include "window/parzen.h"
#include "utility/vector.h"
using namespace edsp;
Parzen::Parzen(edsp::Window::size_type size) : Window(size) {

}

Parzen::~Parzen() = default;

void Parzen::initialize() {
    if (!empty()) {
        const value_type half = (size() - 1) / 2.;
        const value_type quarter = half / 2.;
        value_type initial = -half;
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            auto abs_initial = std::abs(initial);
            auto factor = abs_initial / half;
            if (abs_initial <= quarter) {
                auto tmp = factor * factor;
                data_[i] = 6. * (tmp + tmp * factor);
            } else if ((abs_initial > quarter) && (abs_initial <= half)) {
                auto tmp = 1 - factor;
                data_[i] = 2 * tmp * tmp * tmp;
            }
            ++initial;
        }
    }
}