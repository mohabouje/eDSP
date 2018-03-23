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

#ifndef EDSP_WINDOW_BLACKMAN_H
#define EDSP_WINDOW_BLACKMAN_H

#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Blackman %window implementation.
     *
     * It was designed to have close to the minimal leakage possible. It is close to optimal, only slightly worse than a Kaiser window.
     *
     * \f[
     * w(n)=a_{0}-a_{1}\cos \left({\frac {2\pi n}{N-1}}\right)+a_{2}\cos \left({\frac {4\pi n}{N-1}}\right)
     * \f]
     * with \f$ {\displaystyle a_{0}={\frac {1-\alpha }{2}};\quad a_{1}={\frac {1}{2}};\quad a_{2}={\frac {\alpha }{2}}\,}
     * a_{0}={\frac {1-\alpha }{2}};\quad a_{1}={\frac {1}{2}};\quad a_{2}={\frac {\alpha }{2}}\
     * \f$
     *
     * By common convention, the unqualified term Blackman is \f$ \alpha = 0.16 \f$
     *
     */
    class Blackman : Window {
    public:

        /**
         * @brief Creates and computes a Blackman %window with the given size & type
         * @param size The number of elements to initially create.
         * @param type Window type.
         */
        Blackman(size_type size, WindowType type);

        /**
         * @brief Creates and computes a Blackman %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Blackman(size_type size);
        ~Blackman() override;

        void compute() override;
    };
EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_BLACKMAN_H
