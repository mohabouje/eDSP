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

#ifndef EDSP_WINDOW_HAMMING_H
#define EDSP_WINDOW_HAMMING_H

#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Hamming %window implementation.
     *
     * This %window was proposed by Richard W. Hammming. It's optimized to minimize the maximum
     * side lobe. The following equation generates the coefficients:
     *
     * \f[
     *    w(n)=\alpha -\beta \;\cos \left({\frac {2\pi n}{N-1}}\right),
     * \f]
     * with \f$ {\displaystyle \alpha =0.54,\;\beta =1-\alpha =0.46,} \f$
     *
     */
    class Hamming : Window {
    public:

        /**
         * @brief Creates and computes a Hamming %window with the given size & type
         * @param size The number of elements to initially create.
         * @param type Window type.
         */
        Hamming(size_type size, WindowType type);

        /**
         * @brief Creates and computes a Hamming %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Hamming(size_type size);

        ~Hamming() override;

        void compute() override;
    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_HAMMING_H
