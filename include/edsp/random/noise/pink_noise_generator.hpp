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
 * File: pink_noise.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EDSP_PINK_NOISE_HPP
#define EDSP_PINK_NOISE_HPP

#include <edsp/random/noise/white_noise_generator.hpp>

namespace edsp { namespace random {

    /**
    * @class pink_noise_generator
    * @brief This class implements a pink noise generator.
    */
    template <typename T, typename Engine = std::mt19937>
    struct pink_noise_generator {
        using value_type = T;

        /**
         * @brief Creates a pink noise sequence generator.
         */
        inline pink_noise_generator(value_type min, value_type max) :
            generator_(white_noise_generator<value_type>(min, max)) {}

        /**
        * @brief Generates a random number following the noise distribution.
        * @return The generated random number.
        */
        inline value_type operator()() {
            value_type white  = generator_();
            b0                = 0.99886 * b0 + white * 0.0555179;
            b1                = 0.99332 * b1 + white * 0.0750759;
            b2                = 0.96900 * b2 + white * 0.1538520;
            b3                = 0.86650 * b3 + white * 0.3104856;
            b4                = 0.55000 * b4 + white * 0.5329522;
            b5                = -0.7616 * b5 - white * 0.0168980;
            value_type output = (b0 + b1 + b2 + b3 + b4 + b5 + b6 + white * 0.5362) * 0.11;
            b6                = white * 0.115926;
            return output;
        }

    private:
        value_type b0{0};
        value_type b1{0};
        value_type b2{0};
        value_type b3{0};
        value_type b4{0};
        value_type b5{0};
        value_type b6{0};
        white_noise_generator<T, Engine> generator_;
    };

}} // namespace edsp::random

#endif // EDSP_PINK_NOISE_HPP
