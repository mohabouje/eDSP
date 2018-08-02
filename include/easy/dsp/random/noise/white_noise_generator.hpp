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
 * Filename: white_noise.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EASYDSP_WHITE_NOISE_HPP
#define EASYDSP_WHITE_NOISE_HPP

#include <random>
#include <chrono>

namespace easy { namespace dsp { namespace random {

    template <typename T, typename Engine = std::mt19937>
    struct WhiteNoiseGenerator {
        using result_type = T;
        inline WhiteNoiseGenerator(result_type min, result_type max) :
            generator_(Engine(static_cast<std::size_t>(std::chrono::system_clock::now().time_since_epoch().count()))),
            distribution_(std::uniform_int_distribution<T>(min, max)) {}

        inline result_type operator()() {
            return static_cast<result_type>(distribution_(generator_));
        }

    private:
        Engine generator_;
        std::uniform_int_distribution<T> distribution_;
    };

}}} // namespace easy::dsp::random

#endif // EASYDSP_WHITE_NOISE_HPP
