//
// Created by Mohammed Boujemaoui on 29/10/2017.
//

#ifndef EDSP_COMPLEX_H
#define EDSP_COMPLEX_H

#include "config.h"
#include "base/constants.h"

#include <algorithm>
#include <numeric>
#include <cmath>
#include <complex>
#include <vector>

EDSP_BEGING_NAMESPACE
    namespace math {
        namespace complex {
            template<typename T, typename = std::enable_if<std::is_arithmetic<T>::value>>
            constexpr std::pair<std::complex<T>, std::complex<T>> solve_quadratic(T a, T b, T c) {
                return std::pair<std::complex<T>, std::complex<T>>(
                        std::complex<T>((-b + std::sqrt(std::complex<T>(b * b - 4 * a * c, 0))) / (2 * a)),
                        std::complex<T>((-b + std::sqrt(std::complex<T>(b * b - 4 * a * c, 0))) / (2 * a))
                );
            };
        }
    }

EDSP_END_NAMESPACE

#endif //EDSP_COMPLEX_H
