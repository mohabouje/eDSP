//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_UTIL_H
#define EDSP_UTIL_H

#include "config.h"
#include "base/types.h"

#include <type_traits>

EDSP_BEGING_NAMESPACE
    namespace Math {
        namespace Util {

            template<typename T>
            constexpr int compare(const T &x, const T &y) {
                return (x > y) - (x < y);
            }

            template<typename T>
            inline void swap(T &x, T &y) {
                const T tmp = x;
                x = y;
                y = tmp;
            }

            template<typename T, ENABLE_IF_ARITHMETIC(T)>
            constexpr bool isNaN(const T &x) {
                return (x) != (x);
            }

            template<typename T, ENABLE_IF_ARITHMETIC(T)>
            constexpr int sign(const T &x) {
                return x > 0 ? 1 : 0;
            }

            template<typename T, ENABLE_IF_ARITHMETIC(T)>
            constexpr bool isOdd(const T &x) {
                return (x % 2) == 0;
            }

            template<typename T, ENABLE_IF_ARITHMETIC(T)>
            constexpr bool isEven(const T &x) {
                return !isOdd(x);
            }


            template<typename T, ENABLE_IF_ARITHMETIC(T)>
            constexpr T square(const T &in) {
                return in * in;
            }

            template<typename T, ENABLE_IF_ARITHMETIC(T)>
            constexpr T random() {
                return static_cast<T>(std::rand());
            }

            template<typename T, ENABLE_IF_ARITHMETIC(T)>
            constexpr T random(const T &min, const T &max) {
                return min + random<T>() * (max - min);
            }


            template<typename T, ENABLE_IF_ARITHMETIC(T)>
            constexpr bool isNegative(const T &x) {
                return x < 0;
            }

            template<typename T, ENABLE_IF_ARITHMETIC(T)>
            constexpr bool isZero(const T &x) {
                return x == 0;
            }

            template<typename T, ENABLE_IF_INTEGER(T)>
            constexpr bool isPowerOfTwo(const T &x) {
                return x != 0 && !(x & (x - 1));
            }

            template<typename T, ENABLE_IF_INTEGER(T)>
            constexpr T nextPowerOfTwo(T x) {
                if (x < 0)
                    return 0;
                if (isPowerOfTwo(x))
                    return x;

                --x;
                x |= x >> 1;
                x |= x >> 2;
                x |= x >> 4;
                x |= x >> 8;
                x |= x >> 16;
                return x + 1;
            }
        }

    }
EDSP_END_NAMESPCE

#endif //EDSP_UTIL_H
