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

#include <easy/meta/math.hpp>
#include <type_traits>
#include <iterator>
#include <cmath>

namespace easy { namespace dsp { namespace statistics {

    enum FluxType { ManhattanDistance, EuclideanDistance, Logarithmic };

    // TODO: implement it in a template metaprogramming way, avoid if statements
    template <FluxType Type>
    struct Flux {
        template <typename InputIterator,
                  typename value_type = typename std::iterator_traits<InputIterator>::value_type>
        inline value_type operator()(InputIterator first, InputIterator last, InputIterator first_other) const {
            const auto size = std::distance(first, last);
            if (Type == FluxType::ManhattanDistance) {
                value_type accumulated = static_cast<value_type>(0);
                for (; first != last; ++first, ++first_other) {
                    accumulated += meta::manhattan_distance(*first, *first_other);
                }
                return std::sqrt(accumulated) / static_cast<value_type>(size);

            } else if (Type == FluxType::EuclideanDistance) {
                value_type accumulated = static_cast<value_type>(0);
                for (; first != last; ++first, ++first_other) {
                    accumulated += meta::euclidean_distance(*first, *first_other);
                }
                return accumulated / static_cast<value_type>(size);
            } else if constexpr (Type ==  FluxType::Logarithmic) {
                value_type accumulated = static_cast<value_type>(0);
                for (; first != last; ++first, ++first_other) {
                    accumulated += std::log(std::abs(*first) / std::abs(*first_other));
                }
                return accumulated / static_cast<value_type>(size);
            }
        }
    };
}}} // namespace easy::feature::statistical

#endif // EASYDSP_STATISTICAL_FLUX_HPP
