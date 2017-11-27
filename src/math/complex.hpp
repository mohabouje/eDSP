//
// Created by Mohammed Boujemaoui on 29/10/2017.
//

#ifndef EDSP_COMPLEX_H
#define EDSP_COMPLEX_H

#include "config.h"
#include "base/constants.h"
#include "base/template_util.hpp"

#include <algorithm>
#include <numeric>
#include <cmath>
#include <complex>
#include <vector>

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

            EDSP_FTEMPLATE_ARITHMETIC_CONTAINER(Container, std::vector<std::complex<typename Container::value_type>>)
            real_to_complex(const Container& data) {
                std::vector<std::complex<typename Container::value_type>> tmp(data.size());
                std::transform(data.begin(), data.end(), tmp.begin(),  [](const double& da) {
                    return std::complex<double>( da, 0.);
                } );
                return tmp;
            }

        }
    }

EDSP_END_NAMESPACE

#endif //EDSP_COMPLEX_H
