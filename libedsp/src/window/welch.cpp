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

#include "window/welch.h"
#include <stdexcept>

using namespace edsp;


Welch::Welch(Window::size_type size) : Window(size) {}

Welch::Welch(Window::size_type size, WindowType type) : Window(size, type) {

}

Welch::~Welch() = default;

void Welch::initialize() {
    if (!empty()) {
        const size_type minimum_size = (type_ == WindowType::Symmetric) ? 3 : 2;
        if (size() < minimum_size)
            throw std::runtime_error("The size must be an integer greater than " + std::to_string(minimum_size));

        const value_type N = (type_ == WindowType::Symmetric) ? (size() - 1) / 2. : size() / 2.;
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            auto tmp = ((i - N) / N);
            data_[i] = 1 - tmp * tmp;
        }
    }
}
