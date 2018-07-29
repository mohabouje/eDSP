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
 * Filename: mixer.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_MIXER_HPP
#define EASYDSP_MIXER_HPP


#include <numeric>

namespace easy { namespace dsp {

    template <typename InputIterator, typename OutputIterator, typename Integer>
    constexpr void mixer(InputIterator first, InputIterator last, OutputIterator out, Integer channels) {
        static_assert(std::is_integral<Integer>::value, "Expecting an integer type");
        using value_type = typename std::iterator_traits<InputIterator>::value_type;

        for (; first < last; first += channels, out++) {
            *out = std::accumulate(first, first + channels, static_cast<value_type>(0)) /
                   static_cast<value_type>(channels);
        }
    };

    template <typename InputIterator, typename OutputIterator, typename Integer>
    constexpr void mixer(InputIterator first, InputIterator last, OutputIterator out, Integer channels,
                           Integer desired_channel) {
        static_assert(std::is_integral<Integer>::value, "Expecting an integer type");
        for (; first < last; first += channels, out++) {
            *out = *(first + desired_channel);
        }
    };

    template <typename Container, typename Integer>
    constexpr void mixer(const Container& input, Container& output, Integer channels) {
        mixer(std::cbegin(input), std::cend(input), channels, std::begin(output));
    }

    template <typename Container, typename Integer>
    constexpr void mixer(const Container& input, Container& output, Integer channels, Integer desired_channel) {
        mixer(std::cbegin(input), std::cend(input), channels, desired_channel, std::begin(output));
    }

}} // namespace easy::dsp

#endif // EASYDSP_MIXER_HPP
