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

EDSP_BEGING_NAMESPACE
namespace utility {
    template <class InputIterator>
    constexpr std::pair<std::size_t, typename std::iterator_traits<InputIterator>::value_type>
    strong_peak(InputIterator __first, InputIterator __last) {
        const auto& it = std::max_element(__first, __last);
        return {static_cast<size_t>(std::distance(__first, it)), *it};
    };

    template <class InputIterator>
    constexpr void set(InputIterator __first, InputIterator __last, typename std::iterator_traits<InputIterator>::value_type const& value) {
        std::fill(__first, __last, value);
    }

    template <class InputIterator>
    constexpr auto sum(InputIterator __first, InputIterator __last) {
        return std::accumulate(__first, __last, typename std::iterator_traits<InputIterator>::value_type());
    }

    template <class InputIterator>
    constexpr auto sum_squares(InputIterator __first, InputIterator __last) {
        return std::inner_product(__first, __last, __first, typename std::iterator_traits<InputIterator>::value_type());
    }

    template <class InputIterator>
    constexpr void ceil(InputIterator __first, InputIterator __last) {
        std::for_each(__first, __last, [](auto& value) {
            value = std::ceil(value);
        });
    }

    template <class InputIterator>
    constexpr void floor(InputIterator __first, InputIterator __last) {
        std::for_each(__first, __last, [](auto& value) {
            value = std::floor(value);
        });
    }

    template <class InputIterator>
    constexpr void round(InputIterator __first, InputIterator __last) {
        std::for_each(__first, __last, [](auto& value) {
            value = std::round(value);
        });
    }

    template <class InputIterator>
    constexpr void ln(InputIterator __first, InputIterator __last) {
        std::for_each(__first, __last, [](auto& value) {
            value = std::log(value);
        });
    }

    template <class InputIterator>
    constexpr void log10(InputIterator __first, InputIterator __last) {
        std::for_each(__first, __last, [](auto& value) {
            value = std::log10(value);
        });
    }

    template <class InputIterator>
    constexpr void log2(InputIterator __first, InputIterator __last) {
        std::for_each(__first, __last, [](auto& value) {
            value = std::log2(value);
        });
    }


    template <class InputIterator>
    constexpr void square(InputIterator __first, InputIterator __last) {
        std::for_each(__first, __last, [](auto& value) {
            value *= value;
        });
    }

    template <class InputIterator>
    constexpr void inv(InputIterator __first, InputIterator __last) {
        std::for_each(__first, __last, [](auto& value) {
            value = 1.f / value;
        });
    }

    template <class InputIterator>
    constexpr void fract(InputIterator __first, InputIterator __last) {
        for (; __first != __last; ++__first) {
            *__first -= std::floor(*__first);
        }
    }

    template <class InputIterator>
    constexpr void linspace(InputIterator __first,
                            InputIterator __last,
                            typename std::iterator_traits<InputIterator>::value_type const& start,
                            typename std::iterator_traits<InputIterator>::value_type const& end
                            ) {
        const auto size = std::distance(__first, __last);
        typename std::iterator_traits<InputIterator>::value_type const increment = (end - start) /
                static_cast<typename std::iterator_traits<InputIterator>::value_type>(size);
        std::iota(__first, __last, increment);
    }

    template <class InputIterator>
    constexpr void normalize(InputIterator __first, InputIterator __last) {
        const auto pair = std::minmax_element(__first, __last);
        typename std::iterator_traits<InputIterator>::value_type const inverse = 1.f / (pair.first - pair.second);
        std::for_each(__first, __last, [&](auto& value) {
            value = (value - pair.first) * inverse;
        });
    }

    template <class Container>
    constexpr Container linspace(typename Container::value_type const& start,
                                 typename Container::value_type const& end,
                                 std::size_t N) {
        Container tmp (N);
        linspace(std::begin(tmp), std::end(tmp), start, end);
        return tmp;
    }

    template <typename Container>
    constexpr void normalize(Container& array) {
        normalize(std::begin(array), std::end(array));
    }

    template <class Container>
    constexpr Container down_sampling(const Container& input, std::size_t OUT) {
        Container res(OUT);
        auto IN = input.size();
        for (std::size_t i = 0; i != OUT - 1; ++i) {
            const auto index = i * (IN - 1) / (OUT - 1);
            const auto p = i * (IN - 1) % (OUT - 1);
            res[i] = ((p * input[index + 1]) + (((OUT - 1) - p) * input[index])) / (OUT - 1);
        }
        res[OUT - 1] = input[IN - 1];
        return res;
    }

    template <class Container>
    constexpr auto max(const Container & array) {
        return *std::max_element(array.begin(), array.end());
    }

    template <class Container>
    constexpr auto min(const Container& array) {
        return *std::min_element(array.begin(), array.end());
    }

    template <class Container>
    constexpr auto minmax(const Container& array) {
        return std::minmax_element(array.begin(), array.end());
    }

    template <class Container, typename = std::enable_if<std::is_arithmetic<typename Container::value_type>::value>>
    constexpr bool has_negative(const Container &array) {
        return std::any_of(array.begin(), array.end(), math::is_negative<typename Container::value_type>) != array.end();
    }

    template <class Container, typename = std::enable_if<std::is_arithmetic<typename Container::value_type>::value>>
    constexpr bool has_zero(const Container &array) {
        return std::any_of(array.begin(), array.end(), math::is_zero<typename Container::value_type>) != array.end();
    }

    template <typename Container>
    constexpr Container zeros(const std::size_t& size) {
        Container tmp(size);
        set(std::begin(tmp), std::end(tmp), static_cast<typename Container::value_type>(0));
        return tmp;
    }

    template <typename Container>
    constexpr Container ones(const std::size_t& size) {
        Container tmp(size);
        set(std::begin(tmp), std::end(tmp), static_cast<typename Container::value_type>(1));
        return tmp;
    }
}
EDSP_END_NAMESPACE

#endif //EDSP_VECTOR_UTIL_H
