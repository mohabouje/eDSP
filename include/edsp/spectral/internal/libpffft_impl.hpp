/*
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
 * File: libpffft_impl.hpp
 * Date: 09/06/18
 * Author: Mohammed Boujemaoui
 */
#ifndef EDSP_LIBPFFFT_IMPL_HPP
#define EDSP_LIBPFFFT_IMPL_HPP


#include <edsp/meta/is_null.hpp>
#include <edsp/meta/advance.hpp>
#include <edsp/meta/iterator.hpp>
#include <edsp/meta/expects.hpp>
#include <edsp/meta/data.hpp>
#include <edsp/spectral/types.hpp>

#include <complex>
#include <pffft.h>
#include <algorithm>

namespace edsp { inline namespace spectral {

    template <typename T>
    struct pffft_impl {};

    template <>
    struct pffft_impl<float> {
        using value_type   = float;
        using complex_type = std::complex<float>;
        using size_type    = int;

        pffft_impl() = default;
        ~pffft_impl() {
        }

        inline void dft(const complex_type* src, complex_type* dst, size_type nfft) {

        }

        inline void idft(const complex_type* src, complex_type* dst, size_type nfft) {

        }

        inline void dft(const value_type* src, complex_type* dst, size_type nfft) {

        }

        inline void idft(const complex_type* src, value_type* dst, size_type nfft) {

        }

        inline void dht(const value_type* src, value_type* dst, size_type nfft) {

        }

        inline void dct(const value_type* src, value_type* dst, size_type nfft, DCT_Type type) {

        }

        inline void idct(const value_type* src, value_type* dst, size_type nfft, DCT_Type type) {
        }

        inline void idft_scale(value_type* dst, size_type nfft) {
            const auto scaling = static_cast<value_type>(nfft);
            for (size_type i = 0; i < nfft; ++i) {
                dst[i] /= scaling;
            }
        }

        inline void idft_scale(complex_type* dst, size_type nfft) {
            const auto scaling = static_cast<value_type>(nfft);
            for (size_type i = 0; i < nfft; ++i) {
                dst[i] /= scaling;
            }
        }

        inline void idct_scale(value_type* dst, size_type nfft, DCT_Type type) {
            const auto scaling = (type == DCT_Type::Type_I) ? 2 * (nfft - 1) : 2 * nfft;
            for (size_type i = 0; i < nfft; ++i) {
                dst[i] /= scaling;
            }
        }

    private:
    };

}} // namespace edsp::spectral
#endif //EDSP_LIBPFFFT_IMPL_HPP
