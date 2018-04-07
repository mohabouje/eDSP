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

#ifndef EDSP_WINDOW_TUKEY_H
#define EDSP_WINDOW_TUKEY_H

#include "window.hpp"
#include "base/constants.h"
#include <cmath>

EDSP_BEGIN_NAMESPACE
/**
 * @brief Tukey %window implementation, equivalent to a Cosine-Tapered %window.
 *
 * This %window is also known as the Cosine-Tapered %window. The parameter %r defines the
 * the ratio between the constant section and the cosine section. The default value of r = 1/2
 */
class Tukey : Window {
    EDSP_DEFINE_IMPLICITS(Tukey)
public:
    /**
     * @brief Creates and computes a Tukey %window with the given size.
     * @param size The number of elements to initially create.
     */
    explicit Tukey(_In_ size_type size);

    /**
     * @brief Creates and computes a Tukey %window with the given size and ratio.
     * @param size The number of elements to initially create.
     * @param ratio The ratio between the constant section and the cosine section.
     */
    Tukey(_In_ size_type size, _In_ value_type ratio);
    ~Tukey() EDSP_OVERRIDE;


    EDSP_INLINE void initialize() EDSP_OVERRIDE;

    /**
     * @brief Set the ratio between the constant section and the cosine section.
     * @param ratio
     */
    EDSP_INLINE void set_ratio(_In_ value_type ratio) EDSP_NOEXCEPT;

    /**
     * @brief Returns the ratio between the constant section and the cosine section.
     * @return ratio
     */
    EDSP_INLINE value_type ratio() const EDSP_NOEXCEPT;
private:
    value_type _ratio = 0.5;
};

Tukey::Tukey(_In_ Window::size_type size) : Window(size) {

}

Tukey::Tukey(_In_ Window::size_type size, _In_ Window::value_type ratio) : Window(size), _ratio(ratio) {

}

Tukey::~Tukey() = default;

void Tukey::set_ratio(_In_ const Window::value_type ratio) EDSP_NOEXCEPT {
    _ratio = ratio;
}

Window::value_type Tukey::ratio() const EDSP_NOEXCEPT {
    return _ratio;
}

void Tukey::initialize() {
    if (!empty()) {
        const size_type sz = size();
        const size_type N = sz - 1;
        const size_type half = size() / 2;

        value_type increment = 1. / static_cast<value_type>(sz);
        for (size_type i = 0; i < half; ++i) {
            data_[i] = (1. + std::cos(constants<value_type>::pi * (2. * increment / _ratio - 1))) / 2.;
            ++increment;
        }

        const auto ratio_limit = static_cast<const size_type>(std::floor(_ratio * N / 2));
        std::fill(std::begin(data_) + ratio_limit + 2, std::end(data_), 1.);
        std::copy(std::crbegin(data_) + half + 1, std::crend(data_), std::begin(data_) + half);
    }
}
EDSP_END_NAMESPACE



#endif //EDSP_WINDOW_TUKEY_H
