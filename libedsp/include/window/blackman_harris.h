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


#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Blackman-Harris %window implementation.
     *
     * See also: Blackman, BlackmanNuttall
     *
     */
    class BlackmanHarris : Window {
    public:

        /**
         * @brief Creates and computes a Blackman-Harris %window with the given size & type
         * @param size The number of elements to initially create.
         * @param type Window type.
         */
        BlackmanHarris(size_type size, WindowType type);

        /**
         * @brief Creates and computes a Blackman-Harris %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit BlackmanHarris(size_type size);
        ~BlackmanHarris() override;

        void compute() override;
    };

EDSP_END_NAMESPACE


#endif //EDSP_WINDOW_BLACKMAN_HARRIS_H
