//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_VMATH_H
#define EDSP_VMATH_H

#include "config.h"
#include "math_util.h"

#include <algorithm>
#include <numeric>
#include <cmath>

EDSP_BEGING_NAMESPACE
    namespace Math {
        namespace Container {

            template <typename T>
            constexpr int size(const T* array) {
                return (array == nullptr) ? 0 : (sizeof(array) / sizeof(T));
            }

            template<TEMPLATE_CONTAINER(T)>
            constexpr T max(const Container& array) {
                return *std::max_element(array.begin(), array.end());
            }

            template<TEMPLATE_CONTAINER(T)>
            constexpr T min(const Container& array) {
                return *std::min_element(array.begin(), array.end());
            }

            template <TEMPLATE_CONTAINER(T),  typename T>
            inline void set(const Container& array, const T& value) {
                std::memset(array.begin(), array.end(), value);
            }

            template<TEMPLATE_CONTAINER(T), ENABLE_IF_ARITHMETIC(T)>
            constexpr T sum(const Container& array) {
                return std::accumulate(array.begin(), array.end(), T());
            }

            template<TEMPLATE_CONTAINER(T), ENABLE_IF_ARITHMETIC(T)>
            inline T sum_squares(const Container& array) {
                return std::inner_product(array.begin(), array.end(), array.begin(), static_cast<T>(0));
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

            template<TEMPLATE_CONTAINER(T), ENABLE_IF_ARITHMETIC(T)>
            inline bool hasNegative(Container& array) {
                return std::find_if(array.begin(), array.end(),  Util::isNegative<T>) != array.end();
            }

            template<TEMPLATE_CONTAINER(T), ENABLE_IF_ARITHMETIC(T)>
            inline bool hasZero(Container& array) {
                return std::find_if(array.begin(), array.end(), Util::isZero<T>) != array.end();
            }


        }
    }
};

EDSP_END_NAMESPCE


#endif //EDSP_VMATH_H
