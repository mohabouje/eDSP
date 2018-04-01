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

#include "window/gaussian.h"
#include "base/constants.h"
#include <cmath>
using namespace edsp;
Gaussian::Gaussian(edsp::Window::size_type size) : Window(size) {

}

Gaussian::Gaussian(Window::size_type size, Window::value_type alpha) : Window(size), alpha_(alpha) {

}

Gaussian::~Gaussian() = default;

void Gaussian::initialize() {
    if (!empty()) {
        value_type initial = -(size() - 1);
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            auto tmp = alpha_ / static_cast<value_type >(sz) * initial;
            data_[i] = std::exp(-0.5 * tmp * tmp);
            initial += 2;
        }
    }
}

void Gaussian::set_alpha(double alpha) EDSP_NOEXCEPT {
    alpha_ = alpha;
}

double Gaussian::alpha() const EDSP_NOEXCEPT {
    return alpha_;
}

