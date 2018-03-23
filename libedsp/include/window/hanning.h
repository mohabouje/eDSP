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

#ifndef EDSP_WINDOW_HANNING_H
#define EDSP_WINDOW_HANNING_H

#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Hanning %window implementation.
     *
     * This %window was proposed by Julius Von Han. The advantage of the Hann window is very low aliasing,
     * and the tradeoff slightly is a decreased resolution (widening of the main lobe).The following
     * equation generates the coefficients:
     *
     * \f[
     *    w(n)=\alpha -\beta \;\cos \left({\frac {2\pi n}{N-1}}\right),
     * \f]
     * with \f$ {\displaystyle \alpha =0.5,\;\beta =1-\alpha =0.5} \f$
     *
     */
    class Hanning : Window {
    public:

        /**
         * @brief Creates and computes a Hanning %window with the given size & type
         * @param size The number of elements to initially create.
         * @param type Window type.
         */
        Hanning(size_type size, WindowType type);

        /**
         * @brief Creates and computes a Hanning %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Hanning(size_type size);
        ~Hanning() override;

        void compute() override;
    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_HANNING_H
