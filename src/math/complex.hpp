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

EDSP_BEGING_NAMESPACE
    namespace math {
        namespace complex {

            template <typename T>
            constexpr std::pair<std::complex<T>, std::complex<T>> solve_quadratic(T a, T b, T c) {
                return std::pair<std::complex<T>, std::complex<T>> (
                        std::complex<T>((-b + std::sqrt (std::complex<T> (b * b - 4 * a * c, 0))) / (2 * a)),
                        std::complex<T>((-b + std::sqrt (std::complex<T> (b * b - 4 * a * c, 0))) / (2 * a))
                ) ;
            };

            template <typename T>
            constexpr std::complex<T> fix_imag(const std::complex<T>& complex, T limit = 1e-30) {
                return std::complex<T>(complex.real(),  (std::abs(complex.imag()) > limit) ? complex.imag() : static_cast<T>(0));
            }

        }
    }

EDSP_END_NAMESPACE

#endif //EDSP_COMPLEX_H
