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
 * File: fftw_impl.hpp
 * Date: 09/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_FFTW_IMPL_HPP
#define EDSP_FFTW_IMPL_HPP

#include <edsp/meta/is_null.hpp>
#include <edsp/meta/advance.hpp>
#include <edsp/meta/iterator.hpp>
#include <edsp/meta/expects.hpp>
#include <edsp/meta/data.hpp>
#include <edsp/spectral/types.hpp>

#include <complex>
#include <fftw3.h>
#include <algorithm>

namespace edsp { inline namespace spectral {
    inline namespace internal {
        template <typename T>
        inline T* fftw_cast(const T* p) noexcept {
            return const_cast<T*>(p);
        }

        inline fftwf_complex* fftw_cast(const std::complex<float>* p) {
            return const_cast<fftwf_complex*>(reinterpret_cast<const fftwf_complex*>(p));
        }

        inline fftw_complex* fftw_cast(const std::complex<double>* p) {
            return const_cast<fftw_complex*>(reinterpret_cast<const fftw_complex*>(p));
        }    
    }
   


    template <typename T>
    struct fftw_impl {};

    template <>
    struct fftw_impl<float> {
        using value_type   = float;
        using complex_type = std::complex<float>;
        using size_type    = int;

        ::fftwf_plan plan_{nullptr};
        fftw_impl() = default;
        ~fftw_impl() {
            if (!meta::is_null(plan_)) {
                fftwf_destroy_plan(plan_);
            }
        }

        inline void dft(const complex_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_))
                plan_ = fftwf_plan_dft_1d(nfft, fftw_cast(src), fftw_cast(dst), FFTW_FORWARD, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            fftwf_execute_dft(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void idft(const complex_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = fftwf_plan_dft_1d(nfft, fftw_cast(src), fftw_cast(dst), FFTW_BACKWARD, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_dft(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void dft(const value_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = fftwf_plan_dft_r2c_1d(nfft, fftw_cast(src), fftw_cast(dst), FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_dft_r2c(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void idft(const complex_type* src, value_type* dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = fftwf_plan_dft_c2r_1d(nfft, fftw_cast(src), fftw_cast(dst), FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_dft_c2r(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void dht(const value_type* src, value_type* dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = fftwf_plan_r2r_1d(nfft, fftw_cast(src), fftw_cast(dst), FFTW_DHT, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_r2r(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void dct(const value_type* src, value_type* dst, size_type nfft, DCT_Type type) {
            if (meta::is_null(plan_)) {
                const auto plan_type = [type]() {
                    switch (type) {
                        case DCT_Type::Type_I:
                            return FFTW_REDFT00;
                        case DCT_Type::Type_II:
                            return FFTW_REDFT10;
                        case DCT_Type::Type_III:
                            return FFTW_REDFT01;
                        case DCT_Type::Type_IV:
                            return FFTW_REDFT11;
                    }
                }();
                plan_ = fftwf_plan_r2r_1d(nfft, fftw_cast(src), fftw_cast(dst), plan_type, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_r2r(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void idct(const value_type* src, value_type* dst, size_type nfft, DCT_Type type) {
            if (meta::is_null(plan_)) {
                const auto plan_type = [type]() {
                    switch (type) {
                        case DCT_Type::Type_I:
                            return FFTW_REDFT00;
                        case DCT_Type::Type_II:
                            return FFTW_REDFT01;
                        case DCT_Type::Type_III:
                            return FFTW_REDFT10;
                        case DCT_Type::Type_IV:
                            return FFTW_REDFT11;
                    }
                }();
                plan_ = fftwf_plan_r2r_1d(nfft, fftw_cast(src), fftw_cast(dst), plan_type, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_r2r(plan_, fftw_cast(src), fftw_cast(dst));
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
    };

    template <>
    struct fftw_impl<double> {
        using value_type   = double;
        using complex_type = std::complex<double>;
        using size_type    = int;

        ::fftw_plan plan_{nullptr};
        fftw_impl() = default;
        ~fftw_impl() {
            if (!meta::is_null(plan_)) {
                fftw_destroy_plan(plan_);
            }
        }

        inline void dft(const complex_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_))
                plan_ = fftw_plan_dft_1d(nfft, fftw_cast(src), fftw_cast(dst), FFTW_FORWARD, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            fftw_execute_dft(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void idft(const complex_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_))
                plan_ = fftw_plan_dft_1d(nfft, fftw_cast(src), fftw_cast(dst), FFTW_BACKWARD, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            fftw_execute_dft(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void dft(const value_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_))
                plan_ = fftw_plan_dft_r2c_1d(nfft, fftw_cast(src), fftw_cast(dst), FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            fftw_execute_dft_r2c(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void idft(const complex_type* src, value_type* dst, size_type nfft) {
            if (meta::is_null(plan_))
                plan_ = fftw_plan_dft_c2r_1d(nfft, fftw_cast(src), fftw_cast(dst), FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            fftw_execute_dft_c2r(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void dht(const value_type* src, value_type* dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = fftw_plan_r2r_1d(nfft, fftw_cast(src), fftw_cast(dst), FFTW_DHT, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftw_execute_r2r(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void dct(const value_type* src, value_type* dst, size_type nfft, DCT_Type type) {
            if (meta::is_null(plan_)) {
                const auto plan_type = [type]() {
                    switch (type) {
                        case DCT_Type::Type_I:
                            return FFTW_REDFT00;
                        case DCT_Type::Type_II:
                            return FFTW_REDFT10;
                        case DCT_Type::Type_III:
                            return FFTW_REDFT01;
                        case DCT_Type::Type_IV:
                            return FFTW_REDFT11;
                    }
                }();
                plan_ = fftw_plan_r2r_1d(nfft, fftw_cast(src), fftw_cast(dst), plan_type, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftw_execute_r2r(plan_, fftw_cast(src), fftw_cast(dst));
        }

        inline void idct(const value_type* src, value_type* dst, size_type nfft, DCT_Type type) {
            if (meta::is_null(plan_)) {
                const auto plan_type = [type]() {
                    switch (type) {
                        case DCT_Type::Type_I:
                            return FFTW_REDFT00;
                        case DCT_Type::Type_II:
                            return FFTW_REDFT01;
                        case DCT_Type::Type_III:
                            return FFTW_REDFT10;
                        case DCT_Type::Type_IV:
                            return FFTW_REDFT11;
                    }
                }();
                plan_ = fftw_plan_r2r_1d(nfft, fftw_cast(src), fftw_cast(dst), plan_type, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftw_execute_r2r(plan_, fftw_cast(src), fftw_cast(dst));
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
    };
}} // namespace edsp::spectral

#endif // EDSP_FFTW_IMPL_HPP
