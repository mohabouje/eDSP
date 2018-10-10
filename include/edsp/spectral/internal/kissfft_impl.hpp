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
* Filename: kissfft_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 10/10/18
*/

#ifndef EDSP_KISSFFT_IMPL_HPP
#define EDSP_KISSFFT_IMPL_HPP

#include <edsp/thirdparty/kissfft/kissfft.hh>
#include <edsp/spectral/types.hpp>
#include <edsp/meta/is_null.hpp>
#include <edsp/meta/data.hpp>
#include <complex>
#include <memory>

namespace edsp { inline namespace spectral {

    template<typename T, typename Allocator = std::allocator<std::complex<T>>>
    struct kissfft_impl {
        using value_type   = T;
        using complex_type = std::complex<T>;
        using size_type    = std::size_t ;


        kissfft_impl() = default;

        ~kissfft_impl() = default;

        inline void dft(const complex_type *src, complex_type *dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = std::make_unique<kissfft<T, Allocator>>(nfft, false);
            }
            plan_->transform(src, dst);
        }

        inline void idft(const complex_type *src, complex_type *dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = std::make_unique<kissfft<T, Allocator>>(nfft, true);
            }
            plan_->transform(src, dst);
        }

        inline void dft(const value_type *src, complex_type *dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = std::make_unique<kissfft<T, Allocator>>(nfft, false);
            }
            plan_->transform_real(src, dst);
        }

        inline void idft(const complex_type *src, value_type *dst, size_type nfft) {
            if (meta::is_null(plan_)) {
                plan_ = std::make_unique<kissfft<T, Allocator>>(nfft, true);
            }

            std::vector<complex_type, Allocator> input_ifft(nfft), output_ifft(nfft);
            std::copy(src, src + nfft / 2, std::begin(input_ifft));
            for (auto i = 0ul, N = nfft / 2; i < N; ++i) {
                input_ifft[2 * N - i] = std::conj(input_ifft[i]);
            }
            plan_->transform(input_ifft.data(), output_ifft.data());
            std::transform(std::begin(output_ifft), std::end(output_ifft), dst,
                           [](const complex_type & element) -> value_type {
                               return element.real(); });
        }

        inline void dht(const value_type *src, value_type *dst, size_type nfft) {

        }

        inline void dct(const value_type *src, value_type *dst, size_type nfft, DCT_Type type) {

        }

        inline void idct(const value_type *src, value_type *dst, size_type nfft, DCT_Type type) {

        }

        inline void idft_scale(value_type *dst, size_type nfft) {
            const auto scaling = static_cast<value_type>(nfft);
            for (size_type i = 0; i < nfft; ++i) {
                dst[i] /= scaling;
            }
        }

        inline void idft_scale(complex_type *dst, size_type nfft) {
            const auto scaling = static_cast<value_type>(nfft);
            for (size_type i = 0; i < nfft; ++i) {
                dst[i] /= scaling;
            }
        }

        inline void idct_scale(value_type *dst, size_type nfft, DCT_Type type) {
            const auto scaling = static_cast<value_type>(2 * nfft);
            for (size_type i = 0; i < nfft; ++i) {
                dst[i] /= scaling;
            }
        }

    private:
        std::unique_ptr<kissfft<T>> plan_{nullptr};
    };

}}
#endif //EDSP_KISSFFT_IMPL_HPP
