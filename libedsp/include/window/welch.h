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

#include "window.h"

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
    public:

        /**
         * @brief Creates and computes a Welch %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Welch(size_type size);

        /**
         * @brief Creates and computes a Welch %window with the given size and type.
         * @param size The number of elements to initially create.
         * @param type Window type.
         */
        Welch(size_type size, WindowType type_);

        ~Welch() override;


        void compute() override;

    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_WELCH_H
