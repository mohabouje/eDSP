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

#ifndef EDSP_WINDOW_GAUSSIAN_H
#define EDSP_WINDOW_GAUSSIAN_H

#include "window.hpp"
#include "base/constants.h"
#include <cmath>

EDSP_BEGIN_NAMESPACE
/**
 * @brief Gaussian %window implementation.
 *
 * The Fourier transform of a Gaussian is also a Gaussian (it is an eigenfunction of the Fourier Transform).
 * Since the Gaussian function extends to infinity, it must either be truncated at the ends of the window, or
 * itself windowed with another zero-ended window. The size of the window is inversely proportional to the
 * parameter %alpha, proportional factor to the standard deviation.
 *
 * \f[
    {\displaystyle w(n)=e^{-\frac{1}{2} \left( \ælpha * n \right)^{2}}}
 * \f]
 *
 * By default: \f$ \alpha = 2.5 \f$
 */
class Gaussian : Window {
    EDSP_DEFINE_IMPLICITS(Gaussian)
public:
    /**
     * @brief Creates a Gaussian %window with the given size and a factor alpha
     * @param size The number of elements to initially create
     * @param alpha The proportional factor to the standard deviation.
     *
     * Note: Use larger %alpha for a narrow window.  Use larger %size for a smoother
     */
    Gaussian(_In_ size_type size, _In_ value_type alpha);

    /**
     * @brief Creates and computes a Gaussian %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Gaussian(_In_ size_type size);

    ~Gaussian() EDSP_OVERRIDE;

    EDSP_INLINE void initialize() EDSP_OVERRIDE;

    /**
     * @brief Set the proportional factor to the standard deviation
     * @param alpha proportional to the reciprocal of the standard deviation
     */
    EDSP_INLINE void set_alpha(_In_ value_type alpha) EDSP_NOEXCEPT;

    /**
     * @brief Returns the proportional factor to the standard deviation
     * @return the proportional factor to the reciprocal of the standard deviation
     */
    EDSP_INLINE value_type alpha() const EDSP_NOEXCEPT;
private:
    value_type alpha_ = 2.5;
};

Gaussian::Gaussian(_In_ Window::size_type size) : Window(size) {

}

Gaussian::Gaussian(_In_ Window::size_type size, _In_ Window::value_type alpha) : Window(size), alpha_(alpha) {

}

void Gaussian::initialize() {
    if (!empty()) {
        value_type initial = -(size() - 1);
        for (size_type i = 0, sz = size(); i < sz; ++i) {
            auto tmp = alpha_ / static_cast<value_type >(sz) * initial;
            data_[i] = std::exp(-0.5 * tmp * tmp);
            initial += 2;
        }
    }
}

void Gaussian::set_alpha(_In_ double alpha) EDSP_NOEXCEPT {
    alpha_ = alpha;
}

double Gaussian::alpha() const EDSP_NOEXCEPT {
    return alpha_;
}

Gaussian::~Gaussian() = default;

EDSP_END_NAMESPACE
#endif //EDSP_WINDOW_GAUSSIAN_H
