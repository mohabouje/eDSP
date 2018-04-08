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

#ifndef EDSP_WINDOW_RECTANGULAR_H
#define EDSP_WINDOW_RECTANGULAR_H

#include "window.hpp"

EDSP_BEGIN_NAMESPACE
/**
 * @brief Rectangular %window implementation.
 */
class Rectangular : Window {
    EDSP_DECLARE_ALL_IMPLICITS(Rectangular)
public:
    /**
     * @brief Creates and computes a Rectangular %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Rectangular(_In_ size_type size);
    ~Rectangular() EDSP_OVERRIDE;

    EDSP_INLINE void initialize() EDSP_OVERRIDE;
};

Rectangular::Rectangular(edsp::Window::size_type size) : Window(size) {

}

Rectangular::~Rectangular() = default;

void Rectangular::initialize() {
    std::fill(begin(), end(), 1.);
}
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_RECTANGULAR_H
