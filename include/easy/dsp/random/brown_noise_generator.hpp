/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: brown_noise.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EASYDSP_BROWN_NOISE_HPP
#define EASYDSP_BROWN_NOISE_HPP

#include "white_noise_generator.hpp"

namespace easy { namespace dsp { namespace random {

    template <typename T, typename Engine = std::mt19937>
    struct BrownNoiseGenerator {
        using result_type = T;
        inline BrownNoiseGenerator(result_type mean, result_type std_dev) :
            generator_(WhiteNoiseGenerator<result_type>(mean, std_dev)) {

        }

        inline result_type operator()() {
            result_type white = generator_();
            last_output_ += (0.02 *  white);
            last_output_ /= 1.02;
            return 3.5 * last_output_;
        }
    private:
        result_type last_output_{0};
        WhiteNoiseGenerator<T, Engine> generator_;
    };

}}}

#endif // EASYDSP_BROWN_NOISE_HPP
