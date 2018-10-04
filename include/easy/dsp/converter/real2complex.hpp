/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: real2complex.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/9/2018
 */
#ifndef EASYDSP_REAL2COMPLEX_HPP
#define EASYDSP_REAL2COMPLEX_HPP

#include <easy/meta/iterator.hpp>
#include <algorithm>
#include <complex>

namespace easy { namespace dsp { inline namespace converter {

    /**
     * @brief Converts a real scalar to an equivalent complex number.
     * @param real Scalar number representing the real part of the complex number.
     * @param imag Scalar number representing the imaginary part of the complex number.
     * @returns Returns the complex-valued.
     */
    template <typename T>
    constexpr std::complex<T> real2complex(T real, T imag = static_cast<T>(0)) noexcept {
        return std::complex<T>(real, imag);
    }

    /**
     * @brief Converts a range of scalar numbers in to an equivalent complex number
     * and stores the result in another range.
     *
     * @note Use this function when the output range does not have an imaginary part.
     * @param first Input iterator defining the beginning of the range representing the real part.
     * @param last Input iterator defining the ending of the range representing the real part.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename InputIt, typename OutputIt>
    constexpr void real2complex(InputIt first, InputIt last, OutputIt d_first) {
        using input_t  = meta::value_type_t<InputIt>;
        using output_t = meta::value_type_t<OutputIt>;
        std::transform(first, last, d_first, [](const input_t value) -> output_t { return value; });
    }

    /**
     * @brief Converts a range of scalar numbers in to an equivalent complex number
     * and stores the result in another range.
     *
     * @param first1 Input iterator defining the beginning of the range representing the real part.
     * @param last1 Input iterator defining the ending of the range representing the real part.
     * @param first2 Input iterator defining the beginning of the range representing the imaginary part.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <typename InputIt, typename OutputIt>
    constexpr void real2complex(InputIt first1, InputIt last1, InputIt first2, OutputIt d_first) {
        using input_t  = meta::value_type_t<InputIt>;
        using output_t = meta::value_type_t<OutputIt>;
        std::transform(first1, last1, first2, d_first, [](const input_t real, const input_t imag) -> output_t {
            return {real, imag};
        });
    }

}}} // namespace easy::dsp::converter

#endif // EASDY_REAL2COMPLEX_HPP
