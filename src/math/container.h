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

            template<typename T>
            constexpr T max(const std::vector<T>& array) {
                return *std::max_element(array.begin(), array.end());
            }

            template<typename T>
            constexpr T min(const std::vector<T>& array) {
                return *std::min_element(array.begin(), array.end());
            }

            template<typename T>
            constexpr std::vector<T> fract(const std::vector<T>& array) {
                std::vector<T> tmp(array);
                for (size_t i = 0, size = array.size(); i < size; i++) {
                    tmp[i] -= std::floor(array[i]);
                }
                return tmp;
            }

            template<typename T>
            constexpr bool hasNegative(const std::vector<T>& array) {
                return std::find_if(array.begin(), array.end(),  Util::isNegative<T>) != array.end();
            }

            template<typename T>
            constexpr bool hasZero(const std::vector<T>& array) {
                return std::find_if(array.begin(), array.end(), Util::isZero<T>) != array.end();
            }


            template<typename T>
            inline void set(std::vector<T>& array, const T& value) {
                std::fill(array.begin(), array.end(), value);
            }

            template<typename T>
            inline std::vector<T> zeros(const size_t& size) {
                std::vector<T> tmp(size);
                set(tmp, static_cast<T>(0));
                return tmp;
            }

            template<typename T>
            inline std::vector<T> ones(const size_t& size) {
                std::vector<T> tmp(size);
                set<double>(tmp, static_cast<T>(1));
                return tmp;
            }

            template<typename T>
            constexpr T sum(const std::vector<T>& array) {
                return static_cast<T>(std::accumulate(array.begin(), array.end(), T()));
            }

            template<typename T>
            constexpr T sum_squares(const std::vector<T>& array) {
                return std::inner_product(array.begin(), array.end(), array.begin(), static_cast<T>(0));
            }

            template<typename T>
            inline void ceil(std::vector<T>& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                   value = std::ceil(value);
                });
            }

            template<typename T>
            inline void floor(std::vector<T>& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                    value = std::floor(value);
                });
            }

            template<typename T>
            inline void round(std::vector<T>& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                    value = std::round(value);
                });
            }

            template<typename T>
            inline void ln(std::vector<T>& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                    value = std::log(value);
                });
            }

            template<typename T>
            inline void log10(std::vector<T>& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                    value = std::log10(value);
                });
            }

            template<typename T>
            inline void log2(std::vector<T>& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                    value = std::log2(value);
                });
            }


            template<typename T>
            inline void square(std::vector<T>& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                    value *= value;
                });
            }

            template<typename T>
            inline void inv(std::vector<T>& array) {
                std::for_each(array.begin(), array.end(), [](T& value) {
                    value = static_cast<T>(1) / value;
                });
            }

            template<typename T>
            inline void normalize(std::vector<T>& array) {
                const T x = max(array), y = min(array), invDiff = static_cast<T>(1) / (x - y);
                std::for_each(array.begin(), array.end(), [&invDiff, &y](T& value) {
                    value = (value - min) * invDiff;
                });
            }

        }
    }

EDSP_END_NAMESPCE


#endif //EDSP_VMATH_H
