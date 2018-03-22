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

#include "window/tukey.h"
#include "base/constants.h"
#include <cmath>
#include <stdexcept>

using namespace edsp;

Tukey::Tukey(Window::size_type size) : Window(size) {

}

Tukey::Tukey(Window::size_type size, Window::value_type ratio_) : Window(size), ratio_(ratio_) {

}

Tukey::~Tukey() = default;

void Tukey::set_ratio(const edsp::Window::value_type ratio) EDSP_NOEXCEPT {
    ratio_ = ratio;
}

Window::value_type Tukey::ratio() const EDSP_NOEXCEPT {
    return ratio_;
}


void Tukey::initialize() {
    if (!empty()) {
        const size_type sz = size();
        const size_type N = sz - 1;
        const size_type half = size() / 2;

        value_type increment = 1. / static_cast<value_type>(sz);
        for (size_type i = 0; i < half; ++i) {
            data_[i] = (1. + std::cos(Constants<value_type>::pi * (2. * increment / ratio_ - 1))) / 2.;
            ++increment;
        }

        const auto ratio_limit = static_cast<const size_type>(std::floor(ratio_ * N / 2));
        std::fill(std::begin(data_) + ratio_limit + 2, std::end(data_), 1.);
        std::copy(std::crbegin(data_) + half + 1, std::crend(data_), std::begin(data_) + half);
    }
}