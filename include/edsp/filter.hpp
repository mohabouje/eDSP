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
 * File: filter.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EDSP_FILTER_HPP
#define EDSP_FILTER_HPP

#include <edsp/filter/biquad.hpp>
#include <edsp/filter/biquad_cascade.hpp>
#include <edsp/filter/moving_median_filter.hpp>
#include <edsp/filter/moving_average_filter.hpp>
#include <edsp/filter/moving_rms_filter.hpp>

#include <edsp/filter/internal/rbj_designer.hpp>
#include <edsp/filter/internal/zoelzer_designer.hpp>
#include <edsp/filter/internal/butterworth_designer.hpp>
#include <edsp/filter/internal/chebyshev_I_designer.hpp>
#include <edsp/filter/internal/chebyshev_II_designer.hpp>

namespace edsp { namespace filter {

    /**
     * @brief The DesignerType enum defines the different filter's implementation
     * from different authors.
     * @see filter_type
     */
    enum class designer_type {
        RBJ,         /*!< Robert Bristow-Johnson formulas from the Audio-EQ-Cookbook */
        Zolzer,      /*!< Udo Zölzer formulas from his book: Digital Audio Signal Processing */
        Butterworth, /*!< Digital implementation of the classic Butterworth filter by using the bilinear transform */
        ChebyshevI, /*!< Digital implementation of the Chebyshev polynomials (ripple in the passband) filter by using the bilinear transform */
        ChebyshevII, /*!< Digital implementation of the "Inverse Chebyshev" filters (ripple in the stopband) by using the bilinear transform */
        Bessel,
        Elliptic, /*!< Elliptic filters design */
        Legendre  /*!< Legendre filters design */
    };

    template <typename T, designer_type Designer, std::size_t MaxOrder>
    struct designer {};

    /**
     * @brief Robert Bristow-Johnson filter designer.
     * @tparam T Arithmetic type.
     * @tparam MaxOrder Maximum order.
     */
    template <typename T, std::size_t MaxOrder>
    struct designer<T, designer_type::RBJ, MaxOrder> {
        /**
         * @brief Returns a filter which parameters represents the designed frequency response by using the RBJ formulas.
           @param sample_rate The sampling frequency in Hz.
           @param fc Center Frequency or Corner Frequency in Hz, or shelf midpoint frequency, depending on which filter type.
           @param gain_db Gain in dB, used only for peaking and shelving filters.
           @param Q Depending of the filter represents the Quality factor, the bandwidth in octaves (between -3 dB frequencies for BPF
                    and notch or between midpoint (gain_db/2) gain frequencies for peaking EQ) or the "shelf slope" parameter.
         * @return %Biquad filter with the computed coefficients.
         * @see AudioEQ-CookBook:  \link http://www.musicdsp.org/showone.php?id=197 \endlink
         */
        template <filter_type Type, typename... Args>
        constexpr biquad<T> design(T fc, T sample_rate, T Q, T gain_db = 1) const {
            return RBJFilterDesigner<T, Type>{}(fc, sample_rate, Q, gain_db);
        }
    };

    /**
     * @brief Udo Zölzer filter designer.
     * @tparam T Arithmetic type.
     * @tparam MaxOrder Maximum order.
     */
    template <typename T, std::size_t MaxOrder>
    struct designer<T, designer_type::Zolzer, MaxOrder> {
        /**
         * @brief Returns a filter which parameters represents the designed frequency response by using the Zoelzer formulas.
           @param sample_rate The sampling frequency in Hz.
           @param fc Center Frequency or Corner Frequency in Hz, or shelf midpoint frequency, depending on which filter type.
           @param gain_db Gain in dB, used only for peaking and shelving filters.
           @param Q Depending of the filter represents the Quality factor, the bandwidth in octaves (between -3 dB frequencies for BPF
                    and notch or between midpoint (gain_db/2) gain frequencies for peaking EQ) or the "shelf slope" parameter.
         * @return Biquad filter with the computed coefficients.
         * @see DAFX: Digital Audio Effects, Udo Zölzer:
         * \link https://www.wiley.com/en-us/DAFX%3A+Digital+Audio+Effects%2C+2nd+Edition-p-9780470979679 \endlink
         */
        template <filter_type Type, typename... Args>
        constexpr biquad<T> design(T fc, T sample_rate, T Q, T gain_db = 1) const {
            return ZoelzerFilterDesigner<T, Type>{}(fc, sample_rate, Q, gain_db);
        }
    };

    /**
     * @brief Butterworth filter designer.
     * @tparam T Arithmetic type.
     * @tparam MaxOrder Maximum order.
     */
    template <typename T, std::size_t MaxOrder>
    struct designer<T, designer_type::Butterworth, MaxOrder> {
        template <filter_type Type, typename... Args>
        constexpr auto design(Args... arg) const -> decltype(butterworth_designer<T, Type, MaxOrder>{}(arg...)) {
            return butterworth_designer<T, Type, MaxOrder>{}.operator()(arg...);
        }
    };

    /**
     * @brief Chebyshev filter designer.
     * @tparam T Arithmetic type.
     * @tparam MaxOrder Maximum order.
     */
    template <typename T, std::size_t MaxOrder>
    struct designer<T, designer_type::ChebyshevI, MaxOrder> {
        template <filter_type Type, typename... Args>
        constexpr auto design(Args... arg) const
            -> decltype(chebyshevI_designer<T, Type, MaxOrder>{}(std::declval<Args&&>()...)) {
            return chebyshevI_designer<T, Type, MaxOrder>{}(arg...);
        }
    };

    /**
     * @brief Inverse Chebyshev filter designer.
     * @tparam T Arithmetic type.
     * @tparam MaxOrder Maximum order.
     */
    template <typename T, std::size_t MaxOrder>
    struct designer<T, designer_type::ChebyshevII, MaxOrder> {
        template <filter_type Type, typename... Args>
        constexpr auto design(Args... arg) const
            -> decltype(chebyshevII_designer<T, Type, MaxOrder>{}(std::declval<Args&&>()...)) {
            return chebyshevII_designer<T, Type, MaxOrder>{}(arg...);
        }
    };

    /**
     * @brief Creates a filter using args as the parameter list for the construction.
     * @tparam T Value type
     * @tparam Type Types of filter to be created.
     * @param arg Arguments parameters to constructs the filter.
     * @return A filter with the given configuration.
     */
    template <typename T, designer_type Designer, filter_type Type, std::size_t MaxOrder, typename... Args>
    constexpr auto make_filter(Args... arg)
        -> decltype(designer<T, Designer, MaxOrder>{}.template design<Type>(std::declval<Args&&>()...)) {
        return designer<T, Designer, MaxOrder>{}.template design<Type>(arg...);
    }

    /**
     * @brief Computes the frequency response of a digital filter.
     * @param b_first Beginning of the range elements representing the FIR/MA filter coefficients.
     * @param b_last End of the range elements representing the FIR/MA filter coefficients.
     * @param a_first Beginning of the range elements representing the IIR/AR filter coefficients.
     * @param a_last End of the range elements re
     * presenting the IIR/AR filter coefficients.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @param K Number of evaluation points.
     */
    template <typename InputIt, typename OutputIt, typename Numeric>
    constexpr void freq(InputIt b_first, InputIt b_last, InputIt a_first, InputIt a_last, OutputIt d_first, Numeric K) {
        using value_type  = typename std::iterator_traits<InputIt>::value_type;
        using output_type = typename std::iterator_traits<OutputIt>::value_type;
        const auto M      = std::distance(b_first, b_last);
        const auto N      = std::distance(a_first, a_last);

        constexpr auto i = output_type(0, 1);
        for (auto k = 0ul; k < K; ++k, ++d_first) {
            auto b_tmp = output_type(*b_first, 0);
            auto b     = b_first + 1;
            for (auto m = 1; m < M; ++m, ++b) {
                const auto rad = m * math::constants<value_type>::pi * k / K;
                b_tmp += *b * (std::cos(rad) - i * std::sin(rad));
            }

            auto a_tmp = output_type(*a_first, 0);
            auto a     = a_first + 1;
            for (auto n = 1; n < N; ++n, ++a) {
                const auto rad = n * math::constants<value_type>::pi * k / K;
                a_tmp += *a * (std::cos(rad) - i * std::sin(rad));
            }

            *d_first = b_tmp / a_tmp;
        }
    }

}} // namespace edsp::filter

#endif // EDSP_FILTER_HPP
