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

#ifndef EDSP_WINDOW_WELCH_H
#define EDSP_WINDOW_WELCH_H

#include "window.hpp"

EDSP_BEGIN_NAMESPACE
/**
 * @brief Welch %window implementation.
 *
 * The Welch window is given by:
 * \f[
 *    w(n)=1-\left( \frac{n}{N-1} \right)
 * \f]
 *
 * This class implement two different approaches:
 *    - Symmetric: the %window has zero at each end and maximum in the middle. In this case: N = (m-1)/2
 *    - Periodic: the %window wraps around the cyclic interval. In this case: N = m/2
 *
 */
class Welch : Window {
    EDSP_DECLARE_ALL_IMPLICITS(Welch)
public:
    /**
     * @brief Creates and computes a Welch %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Welch(_In_ size_type size);

    /**
     * @brief Creates and computes a Welch %window with the given size and type.
     * @param size The number of elements to initially create.
     * @param type Window type.
     */
    Welch(_In_ size_type size, _In_ WindowType type_);

    ~Welch() EDSP_OVERRIDE;

    /**
     * @brief initialize Initialize the window
     * @throws Throues an std::runtime_error exception if the defined does not fit the minimum expected.
     */
    EDSP_INLINE void initialize() EDSP_OVERRIDE;
};


Welch::Welch(_In_ Window::size_type size) : Window(size) {}

Welch::Welch(_In_ Window::size_type size, _In_ WindowType type) : Window(size, type) {

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
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_WELCH_H
