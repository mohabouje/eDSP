//
// Created by Mohammed Boujemaoui on 09/10/2017.
//

#ifndef EDSP_TRIG_H
#define EDSP_TRIG_H

#include "config.h"
#include "base/constants.h"

#include <algorithm>
#include <numeric>
#include <cmath>

EDSP_BEGING_NAMESPACE
    namespace math {
        namespace trigonometry {

            template<typename T>
            EDSP_EXPORT constexpr T asinh(const T &x) {
                return static_cast<T>(
                        std::log(x + std::sqrt(x * x + 1)));
            }

            template<typename T>
            EDSP_EXPORT constexpr T acosh(const T &x) {
                return static_cast<T>(
                        std::log(x + std::sqrt(x * x - 1)));
            }

            template<typename T>
            EDSP_EXPORT constexpr T deg_to_rad(const T &x) {
                return static_cast<T>( x * Constants<T>::pi / 180 );
            }

            template<typename T>
            EDSP_EXPORT constexpr T rad_to_deg(const T &x) {
                return static_cast<T>( x * Constants<T>::pi * 180 );
            }
        }
    }

EDSP_END_NAMESPACE

#endif //EDSP_TRIG_H
