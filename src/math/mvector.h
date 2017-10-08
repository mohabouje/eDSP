//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_VMATH_H
#define EDSP_VMATH_H

#include "config.h"

#include <algorithm>
#include <numeric>
#include <cmath>

EDSP_BEGING_NAMESPACE
    namespace Math {
        namespace Vector {

            template<TEMPLATE_CONTAINER(T), ENABLE_IF_ARITHMETIC(T)>
            constexpr T max(const Container& array) {
                return *std::max_element(array.begin(), array.end());
            }


            template<TEMPLATE_CONTAINER(T), ENABLE_IF_ARITHMETIC(T)>
            constexpr T min(const Container& array) {
                return *std::min_element(array.begin(), array.end());
            }

            template<TEMPLATE_CONTAINER(T), ENABLE_IF_ARITHMETIC(T)>
            constexpr T sum(const Container& array) {
                return std::accumulate(array.begin(), array.end(), T());
            }

            template<TEMPLATE_CONTAINER(T), ENABLE_IF_ARITHMETIC(T)>
            void ceil(Container& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                   value = std::ceil(value);
                });
            }

            template<TEMPLATE_CONTAINER(T), ENABLE_IF_ARITHMETIC(T)>
            void floor(Container& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                    value = std::floor(value);
                });
            }


            template<TEMPLATE_CONTAINER(T), ENABLE_IF_ARITHMETIC(T)>
            void round(Container& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                    value = std::round(value);
                });
            }

        }
    }
};

EDSP_END_NAMESPCE


#endif //EDSP_VMATH_H
