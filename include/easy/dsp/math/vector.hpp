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
 * Filename: vector.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_VECTOR_HPP
#define EASYDSP_VECTOR_HPP

#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include "easy/dsp/math/math.hpp"

namespace easy { namespace dsp { namespace math {

    template <class BiIterator>
    constexpr std::pair<std::size_t, typename std::iterator_traits<BiIterator>::value_type>
        strong_peak(BiIterator first, BiIterator last) {
        const auto& it = std::max_element(first, last);
        return {static_cast<size_t>(std::distance(first, it)), *it};
    };

    template <class BiIterator>
    constexpr void set(BiIterator first, BiIterator last,
                       typename std::iterator_traits<BiIterator>::value_type const& value) {
        std::fill(first, last, value);
    }

    template <class BiIterator>
    constexpr auto sum(BiIterator first, BiIterator last) {
        return std::accumulate(first, last, typename std::iterator_traits<BiIterator>::value_type());
    }

    template <class BiIterator>
    constexpr auto sum_squares(BiIterator first, BiIterator last) {
        return std::inner_product(first, last, first, typename std::iterator_traits<BiIterator>::value_type());
    }

    template <class BiIterator>
    constexpr void ceil(BiIterator first, BiIterator last) {
        std::for_each(first, last, [](auto& value) { value = std::ceil(value); });
    }

    template <class BiIterator>
    constexpr void floor(BiIterator first, BiIterator last) {
        std::for_each(first, last, [](auto& value) { value = std::floor(value); });
    }

    template <class BiIterator>
    constexpr void round(BiIterator first, BiIterator last) {
        std::for_each(first, last, [](auto& value) { value = std::round(value); });
    }

    template <class BiIterator>
    constexpr void ln(BiIterator first, BiIterator last) {
        std::for_each(first, last, [](auto& value) { value = std::log(value); });
    }

    template <class BiIterator>
    constexpr void log10(BiIterator first, BiIterator last) {
        std::for_each(first, last, [](auto& value) { value = std::log10(value); });
    }

    template <class BiIterator>
    constexpr void log2(BiIterator first, BiIterator last) {
        std::for_each(first, last, [](auto& value) { value = std::log2(value); });
    }

    template <class BiIterator>
    constexpr void square(BiIterator first, BiIterator last) {
        std::for_each(first, last, [](auto& value) { value *= value; });
    }

    template <class BiIterator>
    constexpr void inv(BiIterator first, BiIterator last) {
        std::for_each(first, last, [](auto& value) { value = 1.f / value; });
    }

    template <class BiIterator>
    constexpr void fract(BiIterator first, BiIterator last) {
        for (; first != last; ++first) {
            *first -= std::floor(*first);
        }
    }

    template <class BiIterator, typename value_type = typename std::iterator_traits<BiIterator>::value_type>
    constexpr void linspace(BiIterator first, BiIterator last, value_type const& start, value_type const& end) {
        const value_type increment = (end - start) / static_cast<value_type>(std::distance(first, last));
        for (auto tmp = start; first != last; ++first, tmp += increment)
            *first = tmp;
    }

    template <class BiIterator>
    constexpr void normalize(BiIterator first, BiIterator last) {
        constexpr auto pair                                                     = std::minmax_element(first, last);
        constexpr typename std::iterator_traits<BiIterator>::value_type inverse = 1.f / (pair.first - pair.second);
        std::for_each(first, last, [&](auto& value) { value = (value - pair.first) * inverse; });
    }

    template <class InputIterator, class OutputIterator>
    constexpr void element_wise_multiplication(InputIterator first, InputIterator last, InputIterator first2,
                                               OutputIterator out) {
        std::transform(first, last, first2, out,
                       std::multiplies<typename std::iterator_traits<InputIterator>::value_type>());
    }

    template <class InputIterator, class OutputIterator>
    constexpr void element_wise_plus(InputIterator first, InputIterator last, InputIterator first2,
                                     OutputIterator out) {
        std::transform(first, last, first2, out, std::plus<typename std::iterator_traits<InputIterator>::value_type>());
    }

    template <class InputIterator, class OutputIterator>
    constexpr void element_wise_divides(InputIterator first, InputIterator last, InputIterator first2,
                                        OutputIterator out) {
        std::transform(first, last, first2, out,
                       std::divides<typename std::iterator_traits<InputIterator>::value_type>());
    }

    template <class InputIterator, class OutputIterator>
    constexpr void element_wise_minus(InputIterator first, InputIterator last, InputIterator first2,
                                      OutputIterator out) {
        std::transform(first, last, first2, out,
                       std::minus<typename std::iterator_traits<InputIterator>::value_type>());
    }

    template <class BiIterator>
    constexpr typename std::enable_if<std::is_arithmetic<typename std::iterator_traits<BiIterator>::value_type>::value,
                                      bool>::type
        has_negative(BiIterator first, BiIterator last) {
        return std::any_of(first, last, math::is_negative<typename std::iterator_traits<BiIterator>::value_type>);
    }

    template <class BiIterator>
    constexpr typename std::enable_if<std::is_arithmetic<typename std::iterator_traits<BiIterator>::value_type>::value,
                                      bool>::type
        has_zero(BiIterator first, BiIterator last) {
        return std::any_of(first, last, math::is_zero<typename std::iterator_traits<BiIterator>::value_type>);
    }

}}} // namespace easy::dsp::math

#endif // EASYDSP_VECTOR_HPP
