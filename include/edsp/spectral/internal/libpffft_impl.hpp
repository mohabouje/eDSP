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
 * You should have received a copy of the GNU General Public License along width
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

#include <complex>
#include <pffft.h>
#include <algorithm>

namespace edsp { inline namespace spectral {

    namespace internal {

        inline void forward_transform(float* vec, float* temp, size_t len) {
            if (len == 1)
                return;
            size_t halfLen = len / 2;
            for (size_t i = 0; i < halfLen; i++) {
                float x           = vec[i];
                float y           = vec[len - 1 - i];
                temp[i]           = x + y;
                temp[i + halfLen] = (x - y) / (std::cos((i + 0.5f) * math::constants<float>::pi / len) * 2);
            }
            forward_transform(temp, vec, halfLen);
            forward_transform(&temp[halfLen], vec, halfLen);
            for (size_t i = 0; i < halfLen - 1; i++) {
                vec[i * 2 + 0] = temp[i];
                vec[i * 2 + 1] = temp[i + halfLen] + temp[i + halfLen + 1];
            }
            vec[len - 2] = temp[halfLen - 1];
            vec[len - 1] = temp[len - 1];
        }

        inline void inverse_transform(float* vec, float* temp, size_t len) {
            if (len == 1)
                return;
            size_t halfLen = len / 2;
            temp[0]        = vec[0];
            temp[halfLen]  = vec[1];
            for (size_t i = 1; i < halfLen; i++) {
                temp[i]           = vec[i * 2];
                temp[i + halfLen] = vec[i * 2 - 1] + vec[i * 2 + 1];
            }
            inverse_transform(temp, vec, halfLen);
            inverse_transform(&temp[halfLen], vec, halfLen);
            for (size_t i = 0; i < halfLen; i++) {
                float x          = temp[i];
                float y          = temp[i + halfLen] / (std::cos((i + 0.5f) * math::constants<float>::pi / len) * 2);
                vec[i]           = x + y;
                vec[len - 1 - i] = x - y;
            }
        }

        // DCT type II, unscaled. Algorithm by Byeong Gi Lee, 1984.
        // See: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.118.3056&rep=rep1&type=pdf#page=34
        inline void dct(float* vec, size_t len) {
            std::vector<float> temp(len);
            forward_transform(vec, temp.data(), len);
            for (size_t i = 0; i < len; ++i) {
                vec[i] *= 2;
            }
        }

        // DCT type III, unscaled. Algorithm by Byeong Gi Lee, 1984.
        // See: http://tsp7.snu.ac.kr/int_jour/IJ_2.pdf
        inline void idct(float* vec, size_t len) {
            for (size_t i = 0; i < len; ++i) {
                vec[i] *= 2;
            }
            vec[0] /= 2;
            std::vector<float> temp(len);
            inverse_transform(vec, temp.data(), len);
        }

        template <typename T, typename R>
        void useless_idct(const T* input, T* dst, R N) {
            for (auto k = 0; k < N; ++k) {
                dst[k] = 0;
                for (auto j = 1; j < N; ++j) {
                    dst[k] += input[j] * std::cos(math::constants<T>::pi * j * (k + 0.5) / static_cast<T>(N));
                }
                dst[k] = input[0] + 2 * dst[k];
            }
        }

        template <typename T, typename R>
        void useless_dht(const T* input, T* dst, R N) {
            for (auto k = 0; k < N; ++k) {
                dst[k] = 0;
                for (auto j = 1; j < N; ++j) {
                    const auto factor = math::constants<T>::two_pi * j * k / static_cast<T>(N);
                    dst[k] += input[j] * (std::cos(factor) + std::sin(factor));
                }
            }
        }

    } // namespace internal

    template <typename T>
    struct pffft_impl {};

    template <>
    struct pffft_impl<float> {
        using value_type   = float;
        using complex_type = std::complex<float>;
        using size_type    = int;

        explicit pffft_impl(size_type nfft) : nfft_(nfft) {
            work_ = (float*) pffft_aligned_malloc(2 * nfft * sizeof(float));
            meta::expects(
                nfft_ % 16 == 0,
                "Unfortunately, the fft_engine size must be a multiple of 16 for complex FFTs  and 32 for real FFTs");
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
            pffft_transform_ordered(plan_, reinterpret_cast<const float*>(src), reinterpret_cast<float*>(dst), work_,
                                    PFFFT_FORWARD);
        }

        inline void idft(const complex_type* src, complex_type* dst) {
            if (meta::is_null(plan_)) {
                plan_ = pffft_new_setup(nfft_, PFFFT_COMPLEX);
            }
            pffft_transform_ordered(plan_, reinterpret_cast<const float*>(src), reinterpret_cast<float*>(dst), work_,
                                    PFFFT_BACKWARD);
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
            internal::useless_dht(src, dst, nfft_);
        }

        inline void dct(const value_type* src, value_type* dst) {
            if (meta::is_null(plan_)) {
                plan_ = pffft_new_setup(nfft_, PFFFT_REAL);
            }
            std::copy(src, src + nfft_, dst);
            internal::dct(dst, nfft_);
        }

        inline void idct(const value_type* src, value_type* dst) {
            std::copy(src, src + nfft_, dst);
            internal::idct(dst, nfft_);
        }

        inline void idft_scale(value_type* dst) const {
            const auto scaling = static_cast<value_type>(nfft_);
            for (size_type i = 0; i < nfft_; ++i) {
                dst[i] /= scaling;
            }
        }

        inline void idft_scale(complex_type* dst) const {
            const auto scaling = static_cast<value_type>(nfft_);
            for (size_type i = 0; i < nfft_; ++i) {
                dst[i] /= scaling;
            }
        }

        inline void idct_scale(value_type* dst) const {
            const auto scaling = 2 * nfft_;
            for (size_type i = 0; i < nfft_; ++i) {
                dst[i] /= scaling;
            }
        }

    private:
        PFFFT_Setup* plan_{nullptr};
        float* work_{nullptr};
        size_type nfft_;
    };

}}     // namespace edsp::spectral
#endif //EDSP_LIBPFFFT_IMPL_HPP
