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
 * Filename: padder.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_PADDER_HPP
#define EASYDSP_PADDER_HPP

#include "easy/dsp/random/constant_generator.hpp"
#include <easy/meta/expects.hpp>
#include <easy/meta/advance.hpp>
#include <algorithm>
#include <functional>

namespace easy { namespace dsp {

    template <typename InputIterator, typename OutputIterator, typename Generator>
    constexpr void padder(InputIterator first, InputIterator last, OutputIterator first_out, OutputIterator last_out,
                          Generator generator) {
        const auto input_size  = std::distance(first, last);
        const auto output_size = std::distance(first_out, last_out);
        meta::expects(output_size >= input_size, "Output size should be greather or equal than the input size");
        std::copy(first, last, first_out);
        std::generate(meta::advance(first_out, input_size), last_out, generator);
    };

    template <typename InputIterator, 
              typename OutputIterator>
    constexpr void padder(InputIterator first, InputIterator last, OutputIterator first_out, OutputIterator last_out,
                          typename std::iterator_traits<InputIterator>::value_type value) {
        padder(first, last, first_out, last_out,
               random::ConstantGenerator<typename std::iterator_traits<InputIterator>::value_type>(value));
    };

    template <typename Container>
    constexpr void padder(const Container& input, Container& output, typename Container::value_type value) {
        padder(std::cbegin(input), std::cend(input), std::begin(output), std::end(output), value);
    };

    template <typename Container, typename Generator>
    constexpr void padder(const Container& input, Container& output, Generator generator) {
        padder(std::cbegin(input), std::cend(input), std::begin(output), std::end(output), std::ref(generator));
    };
}} // namespace easy::dsp

#endif // EASYDSP_PADDER_HPP
