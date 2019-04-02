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
 * File: white_noise.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EDSP_WHITE_NOISE_HPP
#define EDSP_WHITE_NOISE_HPP

#include <random>
#include <chrono>

namespace edsp { namespace random {

    /**
    * @class white_noise_generator
    * @brief This class implements a white noise generator.
    */
    template <typename T, typename Engine = std::mt19937>
    struct white_noise_generator {
        using value_type = T;

        /**
         * @brief Creates a white noise sequence generator.
         */
        inline white_noise_generator(value_type min, value_type max) :
            generator_(Engine(static_cast<std::size_t>(std::chrono::system_clock::now().time_since_epoch().count()))),
            distribution_(std::uniform_int_distribution<T>(min, max)) {}

        /**
        * @brief Generates a random number following the noise distribution.
        * @return The generated random number.
        */
        inline value_type operator()() {
            return static_cast<value_type>(distribution_(generator_));
        }

    private:
        Engine generator_;
        std::uniform_int_distribution<T> distribution_;
    };

}} // namespace edsp::random

#endif // EDSP_WHITE_NOISE_HPP
