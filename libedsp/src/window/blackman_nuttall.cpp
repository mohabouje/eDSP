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
#include "window/blackman_nuttall.h"
#include "base/constants.h"
#include <cmath>
using namespace edsp;

BlackmanNuttall::BlackmanNuttall(Window::size_type size) : Window(size) {

}

BlackmanNuttall::BlackmanNuttall(Window::size_type size, Window::WindowType type) : Window(size, type) {

}

BlackmanNuttall::~BlackmanNuttall() = default;

void BlackmanNuttall::initialize() {
    if (!empty()) {
        const value_type N = (type_ == WindowType::Symmetric) ? size() - 1 : size();
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            value_type tmp = Constants<value_type>::pi * i / N;
            data_[i] = 0.3635879
                       - 0.4891775 * std::cos(2. * tmp)
                       + 0.1365995 * std::cos(4. * tmp)
                       + 0.0106411 * std::cos(6. * tmp);
        }
    }
}