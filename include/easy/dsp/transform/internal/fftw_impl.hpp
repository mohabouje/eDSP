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
 * Filename: fftw_impl.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_FFTW_IMPL_HPP
#define EASYDSP_FFTW_IMPL_HPP

#include <easy/meta/is_null.hpp>
#include <complex>
#include <fftw3.h>

namespace easy { namespace dsp {

    enum class DCT_Type { Type_I, Type_II, Type_III, Type_IV };

    template <typename Integer>
    constexpr Integer make_fft_size(Integer real_size) noexcept {
        return std::floor(real_size / 2) + 1;
    }

    template <typename Integer>
    constexpr Integer make_ifft_size(Integer complex_size) noexcept {
        return 2 * (complex_size - 1);
    }

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

    template <typename T>
    struct fftw_plan {};

    template <>
    struct fftw_plan<float> {
        using value_type   = float;
        using complex_type = fftwf_complex;
        using size_type    = int;

        ::fftwf_plan plan_{nullptr};
        fftw_plan() = default;
        ~fftw_plan() {
            if (!meta::is_null(plan_)) {
                fftwf_destroy_plan(plan_);
            }
        }

        inline void dft(complex_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_))
                plan_ = fftwf_plan_dft_1d(nfft, src, dst, FFTW_FORWARD, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            fftwf_execute_dft(plan_, src, dst);
        }

        inline void idft(complex_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = fftwf_plan_dft_1d(nfft, src, dst, FFTW_BACKWARD, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_dft(plan_, src, dst);
        }

        inline void dft(value_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = fftwf_plan_dft_r2c_1d(nfft, src, dst, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_dft_r2c(plan_, src, dst);
        }

        inline void idft(complex_type* src, value_type* dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = fftwf_plan_dft_c2r_1d(nfft, src, dst, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_dft_c2r(plan_, src, dst);
        }

        inline void dht(value_type* src, value_type* dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = fftwf_plan_r2r_1d(nfft, src, dst, FFTW_DHT, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_r2r(plan_, src, dst);
        }

        inline void dct(value_type* src, value_type* dst, size_type nfft, DCT_Type type) {
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
                plan_ = fftwf_plan_r2r_1d(nfft, src, dst, plan_type, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_r2r(plan_, src, dst);
        }

        inline void idct(value_type* src, value_type* dst, size_type nfft, DCT_Type type) {
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
                plan_ = fftwf_plan_r2r_1d(nfft, src, dst, plan_type, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftwf_execute_r2r(plan_, src, dst);
        }
    };

    template <>
    struct fftw_plan<double> {
        using value_type   = double;
        using complex_type = fftw_complex;
        using size_type    = int;

        ::fftw_plan plan_{nullptr};
        fftw_plan() = default;
        ~fftw_plan() {
            if (!meta::is_null(plan_)) {
                fftw_destroy_plan(plan_);
            }
        }

        inline void dft(complex_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_))
                plan_ = fftw_plan_dft_1d(nfft, src, dst, FFTW_FORWARD, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            fftw_execute_dft(plan_, src, dst);
        }

        inline void idft(complex_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_))
                plan_ = fftw_plan_dft_1d(nfft, src, dst, FFTW_BACKWARD, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            fftw_execute_dft(plan_, src, dst);
        }

        inline void dft(value_type* src, complex_type* dst, size_type nfft) {
            if (meta::is_null(plan_))
                plan_ = fftw_plan_dft_r2c_1d(nfft, src, dst, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            fftw_execute_dft_r2c(plan_, src, dst);
        }

        inline void idft(complex_type* src, value_type* dst, size_type nfft) {
            if (meta::is_null(plan_))
                plan_ = fftw_plan_dft_c2r_1d(nfft, src, dst, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            fftw_execute_dft_c2r(plan_, src, dst);
        }

        inline void dht(value_type* src, value_type* dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = fftw_plan_r2r_1d(nfft, src, dst, FFTW_DHT, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftw_execute_r2r(plan_, src, dst);
        }

        inline void dct(value_type* src, value_type* dst, size_type nfft, DCT_Type type) {
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
                plan_ = fftw_plan_r2r_1d(nfft, src, dst, plan_type, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftw_execute_r2r(plan_, src, dst);
        }

        inline void idct(value_type* src, value_type* dst, size_type nfft, DCT_Type type) {
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
                plan_ = fftw_plan_r2r_1d(nfft, src, dst, plan_type, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
            }
            fftw_execute_r2r(plan_, src, dst);
        }
    };

}} // namespace easy::dsp

#endif // EASYDSP_FFTW_IMPL_HPP
