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
    struct pffft_impl {
        using value_type   = T;
        using complex_type = std::complex<T>;
        using size_type    = int;

        explicit pffft_impl(size_type nfft) : nfft_(nfft) {
            work_ = (float*) pffft_aligned_malloc(2 * nfft * sizeof(float));
            meta::expects(nfft_ % 16 == 0,
                    "Unfortunately, the fft size must be a multiple of 16 for complex FFTs  and 32 for real FFTs");
        }

        ~pffft_impl() {
            if (!meta::is_null(plan_)) {
                pffft_destroy_setup(plan_);
            }
            pffft_aligned_free(work_);
        }

        inline void dft(const complex_type* src, complex_type* dst) {
            if (meta::is_null(plan_)) {
                input_complex.resize(static_cast<unsigned long>(nfft_));
                output_complex.resize(static_cast<unsigned long>(nfft_));
                plan_ = pffft_new_setup(nfft_, PFFFT_COMPLEX);
            }
            std::copy(src, src + nfft_, std::begin(input_complex));
            pffft_transform_ordered(plan_, reinterpret_cast<const float*>(meta::data(input_complex)),
                                    reinterpret_cast<float*>(meta::data(output_complex)), work_, PFFFT_FORWARD);
            std::copy(std::cbegin(output_complex), std::cend(output_complex), dst);
        }

        inline void idft(const complex_type* src, complex_type* dst) {
            if (meta::is_null(plan_)) {
                input_complex.resize(static_cast<unsigned long>(nfft_));
                output_complex.resize(static_cast<unsigned long>(nfft_));
                plan_ = pffft_new_setup(nfft_, PFFFT_COMPLEX);
            }
            std::copy(src, src + nfft_, std::begin(input_complex));
            pffft_transform_ordered(plan_, reinterpret_cast<const float*>(meta::data(input_complex)),
                                    reinterpret_cast<float*>(meta::data(output_complex)), work_, PFFFT_BACKWARD);
            std::copy(std::cbegin(output_complex), std::cend(output_complex), dst);
        }

        inline void dft(const value_type* src, complex_type* dst) {
            const auto c_size = std::floor(nfft_ / 2) + 1;
            if (meta::is_null(plan_)) {
                input_real.resize(static_cast<unsigned long>(nfft_));
                output_complex.resize((unsigned long) c_size);
                plan_ = pffft_new_setup(nfft_, PFFFT_REAL);
            }

            std::copy(src, src + nfft_, std::begin(input_real));
            pffft_transform_ordered(plan_, meta::data(input_real),
                                    reinterpret_cast<float*>(meta::data(output_complex)), work_, PFFFT_FORWARD);
            std::copy(std::cbegin(output_complex), std::cend(output_complex), dst);
        }

        inline void idft(const complex_type* src, value_type* dst) {
            const auto c_size = std::floor(nfft_ / 2) + 1;
            if (meta::is_null(plan_)) {
                input_complex.resize(static_cast<unsigned long>(c_size));
                output_real.resize((unsigned long) nfft_);
                plan_ = pffft_new_setup(nfft_, PFFFT_REAL);
            }
            std::copy(src, src + (int) c_size, std::begin(input_complex));
            pffft_transform_ordered(plan_, reinterpret_cast<const float*>(meta::data(input_complex)),
                    meta::data(output_real), work_, PFFFT_BACKWARD);
            std::copy(std::cbegin(output_real), std::cend(output_real), dst);
        }

        inline void dht(const value_type* src, value_type* dst) {
            meta::unused(src);
            meta::unused(dst);
        }

        inline void dct(const value_type* src, value_type* dst,  DCT_Type type) {
            meta::unused(src);
            meta::unused(dst);
            meta::unused(type);
        }

        inline void idct(const value_type* src, value_type* dst,  DCT_Type type) {
            meta::unused(src);
            meta::unused(dst);
            meta::unused(type);
        }

        inline void idft_scale(value_type* dst) {
            const auto scaling = static_cast<value_type>(nfft_);
            for (size_type i = 0; i < nfft_; ++i) {
                dst[i] /= scaling;
            }
        }

        inline void idft_scale(complex_type* dst) {
            const auto scaling = static_cast<value_type>(nfft_);
            for (size_type i = 0; i < nfft_; ++i) {
                dst[i] /= scaling;
            }
        }

        inline void idct_scale(value_type* dst, DCT_Type type) {
            const auto scaling = (type == DCT_Type::Type_I) ? 2 * (nfft_ - 1) : 2 * nfft_;
            for (size_type i = 0; i < nfft_; ++i) {
                dst[i] /= scaling;
            }
        }

    private:
        PFFFT_Setup* plan_{nullptr};
        float*        work_{nullptr};
        size_type nfft_;
        std::vector<std::complex<float>> input_complex;
        std::vector<std::complex<float>> output_complex;
        std::vector<float> input_real;
        std::vector<float> output_real;
    };


    template <>
    struct pffft_impl<float> {
        using value_type   = float;
        using complex_type = std::complex<float>;
        using size_type    = int;

        explicit pffft_impl(size_type nfft) : nfft_(nfft) {
            work_ = (float*) pffft_aligned_malloc(2 * nfft * sizeof(float));
            meta::expects(nfft_ % 16 == 0,
                          "Unfortunately, the fft size must be a multiple of 16 for complex FFTs  and 32 for real FFTs");
        }

        ~pffft_impl() {
            if (!meta::is_null(plan_)) {
                pffft_destroy_setup(plan_);
            }
            pffft_aligned_free(work_);
        }

        inline void dft(const complex_type* src, complex_type* dst) {
            if (meta::is_null(plan_)) {
                plan_ = pffft_new_setup(nfft_, PFFFT_COMPLEX);
            }
            pffft_transform_ordered(plan_, reinterpret_cast<const float*>(src),
                                    reinterpret_cast<float*>(dst), work_, PFFFT_FORWARD);
        }

        inline void idft(const complex_type* src, complex_type* dst) {
            if (meta::is_null(plan_)) {
                plan_ = pffft_new_setup(nfft_, PFFFT_COMPLEX);
            }
            pffft_transform_ordered(plan_, reinterpret_cast<const float*>(src),
                                    reinterpret_cast<float*>(dst), work_, PFFFT_BACKWARD);
        }

        inline void dft(const value_type* src, complex_type* dst) {
            if (meta::is_null(plan_)) {
                plan_ = pffft_new_setup(nfft_, PFFFT_REAL);
            }
            pffft_transform_ordered(plan_, src, reinterpret_cast<float*>(dst), work_, PFFFT_FORWARD);
        }

        inline void idft(const complex_type* src, value_type* dst) {
            if (meta::is_null(plan_)) {
                plan_ = pffft_new_setup(nfft_, PFFFT_REAL);
            }
            pffft_transform_ordered(plan_, reinterpret_cast<const float*>(src), dst, work_, PFFFT_BACKWARD);
        }

        inline void dht(const value_type* src, value_type* dst) {
            meta::unused(src);
            meta::unused(dst);
        }

        inline void dct(const value_type* src, value_type* dst,  DCT_Type type) {
            meta::unused(src);
            meta::unused(dst);
            meta::unused(type);
        }

        inline void idct(const value_type* src, value_type* dst,  DCT_Type type) {
            meta::unused(src);
            meta::unused(dst);
            meta::unused(type);
        }

        inline void idft_scale(value_type* dst) {
            const auto scaling = static_cast<value_type>(nfft_);
            for (size_type i = 0; i < nfft_; ++i) {
                dst[i] /= scaling;
            }
        }

        inline void idft_scale(complex_type* dst) {
            const auto scaling = static_cast<value_type>(nfft_);
            for (size_type i = 0; i < nfft_; ++i) {
                dst[i] /= scaling;
            }
        }

        inline void idct_scale(value_type* dst, DCT_Type type) {
            const auto scaling = (type == DCT_Type::Type_I) ? 2 * (nfft_ - 1) : 2 * nfft_;
            for (size_type i = 0; i < nfft_; ++i) {
                dst[i] /= scaling;
            }
        }

    private:
        PFFFT_Setup* plan_{nullptr};
        float*        work_{nullptr};
        size_type nfft_;
    };

}} // namespace edsp::spectral
#endif //EDSP_LIBPFFFT_IMPL_HPP
