//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_UTIL_H
#define EDSP_UTIL_H

#include "config.h"
#include "base/types.h"

#include <type_traits>

EDSP_BEGING_NAMESPACE
    namespace math {

        template<typename T>
        constexpr int sign(const T &x) {
            return x > 0 ? 1 : 0;
        }

        template<typename T>
        constexpr bool is_odd(const T &x) {
            return (x % 2) == 0;
        }

        template<typename T>
        constexpr bool is_even(const T &x) {
            return !is_odd(x);
        }


        template<typename T>
        constexpr T square(const T &in) {
            return in * in;
        }

        template<typename T>
        constexpr T random() {
            return static_cast<T>(std::rand());
        }

        template<typename T>
        constexpr T random(const T &min, const T &max) {
            return min + random<T>() * (max - min);
        }


        template<typename T>
        constexpr bool is_negative(const T &x) {
            return x < 0;
        }

        template<typename T>
        constexpr bool is_zero(const T &x) {
            return x == 0;
        }

        template<typename T>
        constexpr bool is_power_two(const T &tmp) {
            auto x = static_cast<int32_t>(tmp);
            return x != 0 && !(x & (x - 1));
        }

        template<typename T>
        constexpr T next_power_two(T tmp) {
            if (is_negative(tmp)) return 0;
            else if (is_power_two(tmp)) return tmp;
            else {
                auto x = static_cast<int32_t>(tmp);
                --x;
                x |= x >> 1;
                x |= x >> 2;
                x |= x >> 4;
                x |= x >> 8;
                x |= x >> 16;
                return static_cast<T>(x + 1);
            }

        }
    }
EDSP_END_NAMESPACE

#endif //EDSP_UTIL_H
