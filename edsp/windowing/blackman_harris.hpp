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
#ifndef EDSP_WINDOW_BLACKMAN_HARRIS_H
#define EDSP_WINDOW_BLACKMAN_HARRIS_H


#include "window.hpp"
#include "base/constants.h"
#include <cmath>

EDSP_BEGIN_NAMESPACE
/**
 * @brief Blackman-Harris %window implementation.
 *
 * See also: Blackman, BlackmanNuttall
 *
 */
class BlackmanHarris : Window {
    EDSP_DEFINE_IMPLICITS(BlackmanHarris)
public:

    /**
     * @brief Creates and computes a Blackman-Harris %window with the given size & type
     * @param size The number of elements to initially create.
     * @param type Window type.
     */
    BlackmanHarris(_In_ size_type size, _In_ WindowType type);

    /**
     * @brief Creates and computes a Blackman-Harris %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit BlackmanHarris(_In_ size_type size);

    ~BlackmanHarris() EDSP_OVERRIDE;

    EDSP_INLINE void initialize() EDSP_OVERRIDE;
};

BlackmanHarris::~BlackmanHarris() = default;

BlackmanHarris::BlackmanHarris(_In_ Window::size_type size) : Window(size) {

}

BlackmanHarris::BlackmanHarris(_In_ Window::size_type size, _In_ Window::WindowType type) : Window(size, type) {

}

void BlackmanHarris::initialize() {
    if (!empty()) {
        const value_type N = (type_ == WindowType::Symmetric) ? size() - 1 : size();
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            value_type tmp = constants<value_type>::pi * i / N;
            data_[i] = 0.35875
                        - 0.48829 * std::cos(2. * tmp)
                        + 0.14128 * std::cos(4. * tmp)
                        + 0.01168 * std::cos(6. * tmp);
        }
    }
}

EDSP_END_NAMESPACE


#endif //EDSP_WINDOW_BLACKMAN_HARRIS_H
