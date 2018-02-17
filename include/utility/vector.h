//
// Created by Mohammed Boujemaoui on 01/12/2017.
//

#ifndef EDSP_VECTOR_UTIL_H
#define EDSP_VECTOR_UTIL_H

#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include "config.h"
#include "math/math.h"

EDSP_BEGIN_NAMESPACE
namespace utility {
    template <class InputIterator>
    constexpr std::pair<std::size_t, typename std::iterator_traits<InputIterator>::value_type>
    strong_peak(InputIterator first, InputIterator last) {
        const auto& it = std::max_element(first, last);
        return {static_cast<size_t>(std::distance(first, it)), *it};
    };

    template <class InputIterator>
    constexpr void set(InputIterator first, InputIterator last, typename std::iterator_traits<InputIterator>::value_type const& value) {
        std::fill(first, last, value);
    }

    template <class InputIterator>
    constexpr auto sum(InputIterator first, InputIterator last) {
        return std::accumulate(first, last, typename std::iterator_traits<InputIterator>::value_type());
    }

    template <class InputIterator>
    constexpr auto sum_squares(InputIterator first, InputIterator last) {
        return std::inner_product(first, last, first, typename std::iterator_traits<InputIterator>::value_type());
    }

    template <class InputIterator>
    constexpr void ceil(InputIterator first, InputIterator last) {
        std::for_each(first, last, [](auto& value) {
            value = std::ceil(value);
        });
    }

    template <class InputIterator>
    constexpr void floor(InputIterator first, InputIterator last) {
        std::for_each(first, last, [](auto& value) {
            value = std::floor(value);
        });
    }

    template <class InputIterator>
    constexpr void round(InputIterator first, InputIterator last) {
        std::for_each(first, last, [](auto& value) {
            value = std::round(value);
        });
    }

    template <class InputIterator>
    constexpr void ln(InputIterator first, InputIterator last) {
        std::for_each(first, last, [](auto& value) {
            value = std::log(value);
        });
    }

    template <class InputIterator>
    constexpr void log10(InputIterator first, InputIterator last) {
        std::for_each(first, last, [](auto& value) {
            value = std::log10(value);
        });
    }

    template <class InputIterator>
    constexpr void log2(InputIterator first, InputIterator last) {
        std::for_each(first, last, [](auto& value) {
            value = std::log2(value);
        });
    }


    template <class InputIterator>
    constexpr void square(InputIterator first, InputIterator last) {
        std::for_each(first, last, [](auto& value) {
            value *= value;
        });
    }

    template <class InputIterator>
    constexpr void inv(InputIterator first, InputIterator last) {
        std::for_each(first, last, [](auto& value) {
            value = 1.f / value;
        });
    }

    template <class InputIterator>
    constexpr void fract(InputIterator first, InputIterator last) {
        for (; first != last; ++first) {
            *first -= std::floor(*first);
        }
    }

    template <class InputIterator, typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    constexpr void linspace(InputIterator first, InputIterator last, value_type const& start, value_type const& end) {
        constexpr value_type increment = (end - start) / static_cast<value_type>(std::distance(first, last));
        for (auto tmp = start; first != last; ++first, tmp += increment)
            *first = tmp;
    }

    template <class InputIterator>
    constexpr void normalize(InputIterator first, InputIterator last) {
        constexpr auto pair = std::minmax_element(first, last);
        constexpr typename std::iterator_traits<InputIterator>::value_type inverse = 1.f / (pair.first - pair.second);
        std::for_each(first, last, [&](auto& value) {
            value = (value - pair.first) * inverse;
        });
    }

    template <class InputIterator, class OutputIterator>
    constexpr void element_wise_multiplication(InputIterator first, InputIterator last,
                                                 InputIterator first2, OutputIterator __out) {
        std::transform(first, last, first2, __out,
                       std::multiplies<typename std::iterator_traits<InputIterator>::value_type>());
    }

    template <class InputIterator, class OutputIterator>
    constexpr void element_wise_plus(InputIterator first, InputIterator last,
                                                 InputIterator first2, OutputIterator __out) {
        std::transform(first, last, first2, __out,
                       std::plus<typename std::iterator_traits<InputIterator>::value_type>());
    }

    template <class InputIterator, class OutputIterator>
    constexpr void element_wise_divides(InputIterator first, InputIterator last,
                                                 InputIterator first2, OutputIterator __out) {
        std::transform(first, last, first2, __out,
                       std::divides<typename std::iterator_traits<InputIterator>::value_type>());
    }

    template <class InputIterator, class OutputIterator>
    constexpr void element_wise_minus(InputIterator first, InputIterator last,
                                                 InputIterator first2, OutputIterator __out) {
        std::transform(first, last, first2, __out,
                       std::minus<typename std::iterator_traits<InputIterator>::value_type>());
    }

    template <class InputIterator>
    constexpr typename std::enable_if<std::is_arithmetic<typename std::iterator_traits<InputIterator>::value_type>::value, bool>::type
    has_negative(InputIterator first, InputIterator last) {
        return std::any_of(first, first, math::is_negative<typename std::iterator_traits<InputIterator>::value_type>);
    }

    template <class InputIterator>
    constexpr typename std::enable_if<std::is_arithmetic<typename std::iterator_traits<InputIterator>::value_type>::value, bool>::type
    has_zero(InputIterator first, InputIterator last) {
        return std::any_of(first, first, math::is_zero<typename std::iterator_traits<InputIterator>::value_type>);
    }
}
EDSP_END_NAMESPACE

#endif //EDSP_VECTOR_UTIL_H
