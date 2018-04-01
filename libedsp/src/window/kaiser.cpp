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

#include "window/kaiser.h"
using namespace edsp;

Kaiser::Kaiser(Window::size_type size) : Window(size) {

}

Kaiser::Kaiser(Window::size_type size, Window::value_type beta) : Window(size), beta_(beta) {

}

Kaiser::~Kaiser() = default;

void Kaiser::initialize() {

}

void Kaiser::set_beta(Window::value_type beta) EDSP_NOEXCEPT {
    beta_ = beta;
}

Window::value_type Kaiser::beta() const EDSP_NOEXCEPT {
    return beta_;
}
