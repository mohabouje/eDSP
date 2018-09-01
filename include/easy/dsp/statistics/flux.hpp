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
 * Filename: flux.hpp
 * Author: Mohammed Boujemaoui
 * Date: 17/6/2018
 */
#ifndef EASYDSP_STATISTICAL_FLUX_HPP
#define EASYDSP_STATISTICAL_FLUX_HPP

#include <easy/dsp/math/math.hpp>
#include <type_traits>
#include <iterator>
#include <cmath>

namespace easy { namespace dsp { namespace statistics {

    enum FluxType { ManhattanDistance, EuclideanDistance, Logarithmic };

    template <FluxType Type>
    struct Flux {};

    template <>
    struct Flux<FluxType::ManhattanDistance> {
        template <typename Iterator>
        constexpr auto operator()(Iterator first_1, Iterator last_1, Iterator first_2) ->
            typename std::iterator_traits<Iterator>::value_type {
            using value_type       = typename std::iterator_traits<Iterator>::value_type;
            value_type accumulated = static_cast<value_type>(0);
            for (; first_1 != last_1; ++first_1, ++first_2) {
                accumulated += math::manhattan_distance(*first_1, *first_2);
            }
            return std::sqrt(accumulated) / static_cast<value_type>(std::distance(first_1, last_1));
        }
    };

    template <>
    struct Flux<FluxType::EuclideanDistance> {
        template <typename Iterator>
        constexpr auto operator()(Iterator first_1, Iterator last_1, Iterator first_2) ->
            typename std::iterator_traits<Iterator>::value_type {
            using value_type       = typename std::iterator_traits<Iterator>::value_type;
            value_type accumulated = static_cast<value_type>(0);
            for (; first_1 != last_1; ++first_1, ++first_2) {
                accumulated += math::euclidean_distance(*first_1, *first_2);
            }
            return std::sqrt(accumulated) / static_cast<value_type>(std::distance(first_1, last_1));
        }
    };

    template <>
    struct Flux<FluxType::Logarithmic> {
        template <typename Iterator>
        constexpr auto operator()(Iterator first_1, Iterator last_1, Iterator first_2) ->
            typename std::iterator_traits<Iterator>::value_type {
            using value_type       = typename std::iterator_traits<Iterator>::value_type;
            value_type accumulated = static_cast<value_type>(0);
            for (; first_1 != last_1; ++first_1, ++first_2) {
                accumulated += math::logarithmic_distance(*first_1, *first_2);
            }
            return std::sqrt(accumulated) / static_cast<value_type>(std::distance(first_1, last_1));
        }
    };

}}} // namespace easy::dsp::statistics

#endif // EASYDSP_STATISTICAL_FLUX_HPP
