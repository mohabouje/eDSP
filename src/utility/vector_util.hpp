//
// Created by Mohammed Boujemaoui on 01/12/2017.
//

#ifndef EDSP_VECTOR_UTIL_H
#define EDSP_VECTOR_UTIL_H

#include <algorithm>
#include <numeric>
#include <cmath>
#include "config.h"
#include "math/math.hpp"
EDSP_BEGING_NAMESPACE
namespace utility {
    namespace vector {
        template <typename Container>
        constexpr typename Container::value_type max(const Container & array) {
            return *std::max_element(array.begin(), array.end());
        }

        template <typename Container>
        constexpr typename Container::value_type min(const Container& array) {
            return *std::min_element(array.begin(), array.end());
        }

        template <typename Container>
        constexpr Container fract(const Container& array) {
            Container tmp(array);
            for (size_t i = 0, size = array.size(); i < size; i++) {
                tmp[i] -= std::floor(array[i]);
            }
            return tmp;
        }

        template <typename Container>
        constexpr bool has_negative(const Container &array) {
            return std::find_if(array.begin(), array.end(), math::is_negative<typename Container::value_type>) != array.end();
        }

        template <typename Container>
        constexpr bool has_zero(const Container &array) {
            return std::find_if(array.begin(), array.end(), math::is_zero<typename Container::value_type>) != array.end();
        }


        template <typename Container>
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

        template <typename Container>
        constexpr void ceil(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::ceil(value);
            });
        }

        template <typename Container>
        constexpr void floor(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::floor(value);
            });
        }

        template <typename Container>
        constexpr void round(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::round(value);
            });
        }

        template <typename Container>
        constexpr void ln(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::log(value);
            });
        }

        template <typename Container>
        constexpr void log10(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::log10(value);
            });
        }

        template <typename Container>
        constexpr void log2(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::log2(value);
            });
        }


        template <typename Container>
        constexpr void square(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value *= value;
            });
        }

        template <typename Container>
        constexpr void inv(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = static_cast<typename Container::value_type&>(1.f / value);
            });
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
        Container down_sampling(const Container& input, std::size_t OUT) {
            Container res(OUT);
            auto IN = input.size();
            for (std::size_t i = 0; i != OUT - 1; ++i) {
                auto index = i * (IN - 1) / (OUT - 1);
                auto p = i * (IN - 1) % (OUT - 1);
                res[i] = ((p * input[index + 1]) + (((OUT - 1) - p) * input[index])) / (OUT - 1);
            }
            res[OUT - 1] = input[IN - 1]; // done outside of loop to avoid out of bound access (0 * a[IN])
            return res;
        }

        template <class Container>
        Container linspace(typename Container::value_type const& start,
                           typename Container::value_type const& end,
                           std::size_t N) {
            Container tmp (N);
            typename Container::value_type val = start, increment = (end - start) / static_cast<typename Container::value_type>(N);
            for (typename Container::iterator it = tmp.begin(), until = tmp.end();
                 it != until; ++it, val += increment) {
                *it = val;
            }
            return tmp;
        }


    }
}
EDSP_END_NAMESPACE

#endif //EDSP_VECTOR_UTIL_H
