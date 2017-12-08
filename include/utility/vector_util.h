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
    namespace vector {
        template <class Container>
        constexpr typename Container::value_type max(const Container & array) {
            return *std::max_element(array.begin(), array.end());
        }

        template <class Container>
        constexpr typename Container::value_type min(const Container& array) {
            return *std::min_element(array.begin(), array.end());
        }

        template <class Container>
        constexpr std::pair<typename Container::value_type, typename Container::value_type> minmax(const Container& array) {
            return std::minmax_element(array.begin(), array.end());
        }

        template <class Container>
        constexpr std::pair<std::size_t, typename Container::value_type> strong_peak(const Container& data) {
            const auto& it = max(data.begin());
            return {static_cast<size_t>(std::distance(data.begin(), it)), *it};
        };

        template <class Container, typename = std::enable_if<std::is_arithmetic<typename Container::value_type>::value>>
        constexpr bool has_negative(const Container &array) {
            return std::any_of(array.begin(), array.end(), math::is_negative<typename Container::value_type>) != array.end();
        }

        template <class Container, typename = std::enable_if<std::is_arithmetic<typename Container::value_type>::value>>
        constexpr bool has_zero(const Container &array) {
            return std::find_if(array.begin(), array.end(), math::is_zero<typename Container::value_type>) != array.end();
        }


        template <class Container>
        constexpr void set(Container& array, typename Container::value_type const& value) {
            std::fill(array.begin(), array.end(), value);
        }

        template <typename Container>
        constexpr Container zeros(const std::size_t& size) {
            Container tmp(size);
            set(tmp, static_cast<typename Container::value_type>(0));
            return tmp;
        }

        template <typename Container>
        constexpr Container ones(const std::size_t& size) {
            Container tmp(size);
            set<std::vector<double>>(tmp, static_cast<typename Container::value_type>(1));
            return tmp;
        }

        template <typename Container>
        constexpr typename Container::value_type sum(const Container& array) {
            return static_cast<typename Container::value_type>(std::accumulate(array.begin(), array.end(), typename Container::value_type()));
        }

        template <typename Container>
        constexpr typename Container::value_type sum_squares(const Container& array) {
            return std::inner_product(array.begin(), array.end(), array.begin(), static_cast<typename Container::value_type>(0));
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
                value = static_cast<typename InputIterator::value_type>(1.f / value);
            });
        }

        template <class InputIterator>
        constexpr void fract(InputIterator __first, InputIterator __last) {
            for (; __first != __last; ++__first) {
                *__first -= std::floor(*__first);
            }
        }

        template <class Container>
        constexpr Container linspace(typename Container::value_type const& start,
                                     typename Container::value_type const& end,
                                     std::size_t N) {
            Container tmp (N);
            const typename Container::value_type increment = (end - start) / static_cast<typename Container::value_type>(N);
            std::iota(std::begin(tmp), std::end(tmp), increment);
            return tmp;
        }

        template <typename Container>
        constexpr void normalize(Container& array) {
            typename Container::value_type x = max(array),
                    y = min(array),
                    invDiff = static_cast<typename Container::value_type>(1.f / (x - y));
            std::for_each(array.begin(), array.end(), [&invDiff, &y](typename Container::value_type& value) {
                value = (value - min) * invDiff;
            });
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
    }
}
EDSP_END_NAMESPACE

#endif //EDSP_VECTOR_UTIL_H
