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
 * Filename: oscillator.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EASYDSP_OSCILLATOR_HPP
#define EASYDSP_OSCILLATOR_HPP

#include "sawtooth.hpp"
#include "sine.hpp"
#include "square.hpp"
#include "triangular.hpp"

#include <iterator>
#include <type_traits>
#include <algorithm>

namespace easy { namespace dsp {
    enum class SignalType {
        Sine,
        Square,
        Sawtooth,
        Triangular
    };

    namespace {

        template <SignalType type>
        struct Generator;

        template <>
        struct Generator<SignalType::Sine> {
            template <typename OutputIterator, typename ...Args>
            constexpr void operator()(OutputIterator first, OutputIterator last, Args... arg) {
                using value_type = typename std::iterator_traits<OutputIterator>::value_type;
                std::generate(first, last, oscillators::SinOscillator<value_type>(std::forward(arg...)));
            }
        };

        template <>
        struct Generator<SignalType::Square> {
            template <typename OutputIterator, typename ...Args>
            constexpr void operator()(OutputIterator first, OutputIterator last, Args... arg) {
                using value_type = typename std::iterator_traits<OutputIterator>::value_type;
                std::generate(first, last, oscillators::SquareOscillator<value_type>(std::forward(arg...)));
            }
        };

        template <>
        struct Generator<SignalType::Sawtooth> {
            template <typename OutputIterator, typename ...Args>
            constexpr void operator()(OutputIterator first, OutputIterator last, Args... arg) {
                using value_type = typename std::iterator_traits<OutputIterator>::value_type;
                std::generate(first, last, oscillators::SawtoothOscillator<value_type>(std::forward(arg...)));
            }
        };

        template <>
        struct Generator<SignalType::Triangular> {
            template <typename OutputIterator, typename ...Args>
            constexpr void operator()(OutputIterator first, OutputIterator last, Args... arg) {
                using value_type = typename std::iterator_traits<OutputIterator>::value_type;
                std::generate(first, last, oscillators::TriangularOscillator<value_type>(std::forward(arg...)));
            }
        };

    }

    template <SignalType type, typename OutputIterator, typename ...Args>
    void oscillator(OutputIterator first, OutputIterator last, Args... arg) {
        Generator<type>{}(first, last, std::forward(arg...));
    }

}}


#endif // EASYDSP_OSCILLATOR_HPP
