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
 * File: binary_sequence_generator.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EDSP_BINARY_SEQUENCE_GENERATOR_HPP
#define EDSP_BINARY_SEQUENCE_GENERATOR_HPP

#include <random>
#include <chrono>

namespace edsp { namespace random {

    /**
    * @class binary_generator
    * @brief This class implements a binary generator according to the discrete probability function.
    *
    * This function uses a Bernoulli distribution internally.
    *
    * @see std::bernoulli_distribution
    */
    template <typename T, typename Engine = std::mt19937>
    struct binary_generator {
        using value_type = T;

        /**
         * @brief Creates a binary sequence generator.
         * @param probability The p distribution parameter (probability of generating true)
         */
        explicit binary_generator(value_type probability) :
            generator_(Engine(static_cast<std::size_t>(std::chrono::system_clock::now().time_since_epoch().count()))),
            distribution_(std::bernoulli_distribution(probability)) {}

        /**
         * @brief Generates a boolean value according to the discrete probability function.
         * @return The generated boolean value.
         */
        value_type operator()() {
            return static_cast<value_type>(distribution_(generator_));
        }

    private:
        Engine generator_;
        std::bernoulli_distribution distribution_;
    };

}} // namespace edsp::random

#endif // EDSP_BINARY_SEQUENCE_GENERATOR_HPP
