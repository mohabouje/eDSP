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
#ifndef EDSP_BLACKMAN_NUTTALL_H
#define EDSP_BLACKMAN_NUTTALL_H

#include "window.hpp"
#include "base/constants.h"
#include <cmath>

EDSP_BEGIN_NAMESPACE
/**
 * @brief Blackman-Nuttal %window implementation.
 *
 * See also: Blackman, BlackmanNuttall
 *
 */
class BlackmanNuttall : Window {
    EDSP_DECLARE_ALL_IMPLICITS(BlackmanNuttall)
public:

    /**
     * @brief Creates and computes a Blackman-Nuttall %window with the given size & type
     * @param size The number of elements to initially create.
     * @param type Window type.
     */
    BlackmanNuttall(_In_ size_type size, _In_ WindowType type);

    /**
     * @brief Creates and computes a Blackman-Nuttal %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit BlackmanNuttall(_In_ size_type size);

    ~BlackmanNuttall() EDSP_OVERRIDE;

    EDSP_INLINE void initialize() EDSP_OVERRIDE;
};

BlackmanNuttall::BlackmanNuttall(_In_ Window::size_type size) : Window(size) {

}

BlackmanNuttall::BlackmanNuttall(_In_ Window::size_type size, _In_ Window::WindowType type) : Window(size, type) {

}

void BlackmanNuttall::initialize() {
    if (!empty()) {
        const value_type N = (type_ == WindowType::Symmetric) ? size() - 1 : size();
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            value_type tmp = constants<value_type>::pi * i / N;
            data_[i] = 0.3635879
                       - 0.4891775 * std::cos(2. * tmp)
                       + 0.1365995 * std::cos(4. * tmp)
                       + 0.0106411 * std::cos(6. * tmp);
        }
    }
}

BlackmanNuttall::~BlackmanNuttall() = default;

EDSP_END_NAMESPACE


#endif //EDSP_BLACKMAN_NUTTALL_H
