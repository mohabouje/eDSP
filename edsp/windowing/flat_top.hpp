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
#ifndef EDSP_FLAT_TOP_H
#define EDSP_FLAT_TOP_H

#include "window.hpp"
#include "base/constants.h"
#include <cmath>

EDSP_BEGIN_NAMESPACE
/**
 * @brief Flat Top %window implementation.
 *
 * The Flat Function has a low pass-band ripple, but high bandwidth. It cans be defined by:
 *
 * \f[
 *  w(n) = 1 - - 1.93 \cos(2 \pi \frac{n}{N-1})
 *  + 1.29 \cos(4 \pi \frac{n}{N-1})
 *  - 0.388 \cos(6 \pi \frac{n}{N-1})
 *  + 0.0322 \cos(8 \pi \frac{n}{N-1})
 * \f]
 *
 **/
class FlatTop : Window {
    EDSP_DECLARE_ALL_IMPLICITS(FlatTop)
public:

    /**
     * @brief Creates and computes a FlatTop %window with the given size & type
     * @param size The number of elements to initially create.
     * @param type Window type.
     */
    FlatTop(_In_ size_type size, _In_ WindowType type);

    /**
     * @brief Creates and computes a FlatTop %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit FlatTop(_In_ size_type size);

    ~FlatTop() EDSP_OVERRIDE;

    EDSP_INLINE void initialize() EDSP_OVERRIDE;
};

FlatTop::FlatTop(Window::size_type size) : Window(size) {

}

FlatTop::FlatTop(Window::size_type size, Window::WindowType type) : Window(size, type) {

}

void FlatTop::initialize() {
    if (!empty()) {
        const value_type N = (type_ == WindowType::Symmetric) ? size() - 1 : size();
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            value_type tmp = constants<value_type>::pi * i / N;
            data_[i] = 1
                       - 1.9300 * std::cos(2. * tmp)
                       + 1.2900 * std::cos(4. * tmp)
                       - 0.3880 * std::cos(6. * tmp)
                       + 0.0322 * std::cos(8. * tmp);

        }
    }
}

FlatTop::~FlatTop() = default;
EDSP_END_NAMESPACE


#endif //EDSP_FLAT_TOP_H
