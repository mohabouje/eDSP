//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_VMATH_H
#define EDSP_VMATH_H

#include "config.h"
#include "math_util.hpp"
#include "base/template_util.hpp"

#include <algorithm>
#include <numeric>
#include <cmath>

EDSP_BEGING_NAMESPACE
    namespace math {
        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        max(const Container & array) {
            return *std::max_element(array.begin(), array.end());
        }

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        min(const Container& array) {
            return *std::min_element(array.begin(), array.end());
        }

        TEMPLATE_CONTAINER(Container, Container)
        fract(const Container& array) {
            Container tmp(array);
            for (size_t i = 0, size = array.size(); i < size; i++) {
                tmp[i] -= std::floor(array[i]);
            }
            return tmp;
        }

        TEMPLATE_CONTAINER(Container, bool)
        hasNegative(const Container& array) {
            return std::find_if(array.begin(), array.end(),  isNegative<typename Container::value_type>) != array.end();
        }

        TEMPLATE_CONTAINER(Container, bool)
        hasZero(const Container& array) {
            return std::find_if(array.begin(), array.end(), isZero<typename Container::value_type>) != array.end();
        }


        TEMPLATE_CONTAINER(Container, void)
        set(Container& array, typename Container::value_type const& value) {
            std::fill(array.begin(), array.end(), value);
        }

        TEMPLATE_CONTAINER(Container, Container)
        zeros(const std::size_t& size) {
            Container tmp(size);
            set(tmp, static_cast<typename Container::value_type>(0));
            return tmp;
        }

        TEMPLATE_CONTAINER(Container, Container)
        ones(const std::size_t& size) {
            Container tmp(size);
            set<std::vector<double>>(tmp, static_cast<typename Container::value_type>(1));
            return tmp;
        }

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        sum(const Container& array) {
            return static_cast<typename Container::value_type>(std::accumulate(array.begin(), array.end(), typename Container::value_type()));
        }

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        sum_squares(const Container& array) {
            return std::inner_product(array.begin(), array.end(), array.begin(), static_cast<typename Container::value_type>(0));
        }

        TEMPLATE_CONTAINER(Container, void)
        ceil(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
               value = std::ceil(value);
            });
        }

        TEMPLATE_CONTAINER(Container, void)
        floor(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::floor(value);
            });
        }

        TEMPLATE_CONTAINER(Container, void)
        round(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::round(value);
            });
        }

        TEMPLATE_CONTAINER(Container, void)
        ln(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::log(value);
            });
        }

        TEMPLATE_CONTAINER(Container, void)
        log10(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::log10(value);
            });
        }

        TEMPLATE_CONTAINER(Container, void)
        log2(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = std::log2(value);
            });
        }


        TEMPLATE_CONTAINER(Container, void)
        square(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value *= value;
            });
        }

        TEMPLATE_CONTAINER(Container, void)
        inv(Container& array) {
            std::for_each(array.begin(), array.end(), [](typename Container::value_type& value) {
                value = static_cast<typename Container::value_type&>(1.f / value);
            });
        }

        TEMPLATE_CONTAINER(Container, void)
        normalize(Container& array) {
            typename Container::value_type x = max(array),
                    y = min(array),
                    invDiff = static_cast<typename Container::value_type>(1.f / (x - y));
            std::for_each(array.begin(), array.end(), [&invDiff, &y](typename Container::value_type& value) {
                value = (value - min) * invDiff;
            });
        }
    }

EDSP_END_NAMESPACE


#endif //EDSP_VMATH_H
