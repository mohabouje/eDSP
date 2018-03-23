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

#include "window/hanning.h"
#include "base/constants.h"
#include <cmath>
using namespace edsp;
Hanning::Hanning(edsp::Window::size_type size) : Window(size) {

}

Hanning::Hanning(Window::size_type size, Window::WindowType type) : Window(size, type) {

}

Hanning::~Hanning() = default;

void Hanning::initialize() {
    if (!empty()) {
        const value_type N = (type_ == WindowType::Symmetric) ? size() - 1 : size();
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            data_[i] = 0.5 * (1 - std::cos(2 * Constants<value_type>::pi * i / (N)));
        }
    }
}