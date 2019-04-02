/*
* eDSP, A cross-platform Digital Signal Processing library written in modern C++.
* Copyright (C) 2019 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
* Filename: fft_engine.hpp
* Author: Mohammed Boujemaoui
* Date: 15/01/19
*/

#ifndef EDSP_FFT_HPP
#define EDSP_FFT_HPP

#include <edsp/spectral/internal/fft_impl.hpp>

namespace edsp { inline namespace spectral {

    /**
     * @brief Computes the expected DFT size for a real-to-complex DFT transform
     * @returns Size of the DFT
     */
    template <typename Integer>
    constexpr Integer make_fft_size(Integer real_size) noexcept {
        return std::floor(real_size / 2) + 1;
    }

    /**
     * @brief Computes the expected IDFT size for a complex-to-real IDFT transform
     * @returns Size of the IDFT
     */
    template <typename Integer>
    constexpr Integer make_ifft_size(Integer complex_size) noexcept {
        return 2 * (complex_size - 1);
    }

    /**
     * @brief This class contains an instance of an FFT engine. Use this class to perform
     * an FFT internally in any algorithm and only for performance reason. There are wrappers
     * around this class to perform basic operations.
     * @tparam T Floating point type.
     */
    template <typename T>
    class fft_engine {
    public:
        //static_assert(std::is_floating_point<T>::value, "Expecting floating point numbers");

        using value_type   = T;
        using complex_type = std::complex<T>;
        using size_type    = std::size_t;

        /**
         * @brief Creates a FFT engine of the given size
         * @param nfft Number of samples of the FFT
         */
        explicit fft_engine(size_type nfft) : impl_(nfft) {}

        /**
         * @brief Default destructor
         */
        ~fft_engine() = default;

        /**
         * @brief Performs a Complex-to-Complex FFT
         * @note The buffer size should be the engine's size.
         * @param src Buffer storing the input samples
         * @param dst Buffer storing the computed spectral samples.
         */
        inline void dft(const complex_type* src, complex_type* dst) {
            impl_.dft(src, dst);
        }

        /**
         * @brief Performs a Complex-to-Complex IFFT.
         * @param src Buffer storing the computed spectral samples.
         * @param dst Buffer storing the transformed samples.
         */
        inline void idft(const complex_type* src, complex_type* dst) {
            impl_.idft(src, dst);
        }

        /**
         * @brief Performs a Real-to-Complex-Hermitian FFT.
         *
         * @note In this case, the DFT output satisfies the “Hermitian” redundancy:
         * out[i] is the conjugate of out[n-i]. So, First of all, the input and output arrays are
         * of different sizes and types: the input is n real numbers, while the output is n/2+1
         * (where the division is rounded down) complex numbers (the non-redundant outputs).
         *
         * @param src Buffer storing purely real numbers
         * @param dst Buffer storing the computed spectral samples.
         */
        inline void dft(const value_type* src, complex_type* dst) {
            impl_.dft(src, dst);
        }

        /**
         * @brief Performs a Complex-Hermitian-to-Real IFFT.
         * @param src Buffer storing the computed spectral samples.
         * @param dst Buffer storing the transformed samples.
         */
        inline void idft(const complex_type* src, value_type* dst) {
            impl_.idft(src, dst);
        }

        /**
         * @brief Performs a Discrete Hartley Transform (DHT)
         * @param src Buffer storing the input samples.
         * @param dst Buffer storing the transformed samples.
         */
        inline void dht(const value_type* src, value_type* dst) {
            impl_.dht(src, dst);
        }

        /**
         * @brief Performs a Discrete Cosine Transform (DCT)
         * @param src Buffer storing the input samples.
         * @param dst Buffer storing the transformed samples.
         */
        inline void dct(const value_type* src, value_type* dst) {
            impl_.dct(src, dst);
        }

        /**
         * @brief Performs an Inverse Discrete Cosine Transform (IDCT)
         * @param src Buffer storing the previously transformed samples.
         * @param dst Buffer storing the computed samples.
         */
        inline void idct(const value_type* src, value_type* dst) {
            impl_.idct(src, dst);
        }

        /**
         * @brief Scales the computed IFFT to match the original input
         * @param dst Buffer containing the samples to be scaled
         */
        template <typename R>
        inline void idft_scale(R* dst) const {
            impl_.idft_scale(dst);
        }

        /**
         * @brief Scales the computed IFFT to match the original input
         * @param dst Buffer containing the samples to be scaled
         */
        inline void idct_scale(value_type* dst) const {
            impl_.idct_scale(dst);
        }

    private:
        internal::fft_impl<T> impl_;
    };

}} // namespace edsp::spectral

#endif //EDSP_FFT_HPP
