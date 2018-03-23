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

#include "window.h"

EDSP_BEGIN_NAMESPACE
    /**
     * @brief Tukey %window implementation, equivalent to a Cosine-Tapered %window.
     *
     * This %window is also known as the Cosine-Tapered %window. The parameter %r defines the
     * the ratio between the constant section and the cosine section. The default value of r = 1/2
     *
     *
     */
    class Tukey : Window {
    public:

        /**
         * @brief Creates and computes a Tukey %window with the given size.
         * @param size The number of elements to initially create.
         */
        explicit Tukey(size_type size);

        /**
         * @brief Creates and computes a Tukey %window with the given size and ratio.
         * @param size The number of elements to initially create.
         * @param ratio The ratio between the constant section and the cosine section.
         */
        Tukey(size_type size, value_type ratio);
        ~Tukey() override;


        void compute() override;

        /**
         * @brief Set the ratio between the constant section and the cosine section.
         * @param ratio
         */
        void set_ratio(const value_type ratio) EDSP_NOEXCEPT;

        /**
         * @brief Returns the ratio between the constant section and the cosine section.
         * @return ratio
         */
        value_type ratio() const EDSP_NOEXCEPT;

    private:
        value_type ratio_{0.5};
    };
EDSP_END_NAMESPACE



#endif //EDSP_WINDOW_TUKEY_H
