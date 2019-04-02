/*
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
 * You should have received a copy of the GNU General Public License along width
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * File: brown_noise.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EDSP_BROWN_NOISE_HPP
#define EDSP_BROWN_NOISE_HPP

#include <edsp/random/noise/white_noise_generator.hpp>

namespace edsp { namespace random {

    /**
    * @class brown_noise_generator
    * @brief This class implements a brown noise generator.
    */
    template <typename T, typename Engine = std::mt19937>
    struct brown_noise_generator {
        using value_type = T;

        /**
         * @brief Creates a brown noise sequence generator.
         */
        inline brown_noise_generator(value_type min, value_type max) :
            generator_(white_noise_generator<value_type>(min, max)) {}

        /**
        * @brief Generates a random number following the noise distribution.
        * @return The generated random number.
        */
        inline value_type operator()() {
            value_type white = generator_();
            last_output_ += (0.02 * white);
            last_output_ /= 1.02;
            return 3.5 * last_output_;
        }

    private:
        value_type last_output_{0};
        white_noise_generator<T, Engine> generator_;
    };

}} // namespace edsp::random

#endif // EDSP_BROWN_NOISE_HPP
