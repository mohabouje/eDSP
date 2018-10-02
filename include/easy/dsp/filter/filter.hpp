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
 * Filename: filter.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EASYDSP_FILTER_HPP
#define EASYDSP_FILTER_HPP

#include <easy/dsp/filter/biquad.hpp>
#include <easy/dsp/filter/biquad_cascade.hpp>

#include <easy/dsp/filter/internal/rbj_designer.hpp>
#include <easy/dsp/filter/internal/zoelzer_designer.hpp>
#include <easy/dsp/filter/internal/butterworth_designer.hpp>
#include <easy/dsp/filter/internal/chebyshev_I_designer.hpp>
#include <easy/dsp/filter/internal/chebyshev_II_designer.hpp>

namespace easy { namespace dsp { namespace filter {

    /**
     * @brief The DesignerType enum defines the different filter's implementation
     * from different authors.
     * @see FilterType
     */
    enum class DesignerType {
        RBJ,         /*!< Robert Bristow-Johnson formulas from the Audio-EQ-Cookbook */
        Zolzer,      /*!< Udo Zölzer formulas from his book: Digital Audio Signal Processing */
        Butterworth, /*!< Digital implementation of the classic Butterworth filter by using the bilinear transform */
        ChebyshevI, /*!< Digital implementation of the Chebyshev polynomials (ripple in the passband) filter by using the bilinear transform */
        ChebyshevII, /*!< Digital implementation of the "Inverse Chebyshev" filters (ripple in the stopband) by using the bilinear transform */
        Bessel,
        Elliptic, /*!< Elliptic filters design */
        Legendre  /*!< Legendre filters design */
    };

    template <typename T, DesignerType Designer, std::size_t MaxOrder>
    struct designer {};

    /**
     * @brief Robert Bristow-Johnson filter designer.
     * @tparam T Arithmetic type.
     * @tparam MaxOrder Maximum order.
     */
    template <typename T, std::size_t MaxOrder>
    struct designer<T, DesignerType::RBJ, MaxOrder> {
        /**
         * @brief Returns a filter which parameters represents the designed frequency response by using the RBJ formulas.
           @param sample_rate The sampling frequency in Hz.
           @param fc Center Frequency or Corner Frequency in Hz, or shelf midpoint frequency, depending on which filter type.
           @param gain_db Gain in dB, used only for peaking and shelving filters.
           @param Q Depending of the filter represents the Quality factor, the bandwidth in octaves (between -3 dB frequencies for BPF
                    and notch or between midpoint (gain_db/2) gain frequencies for peaking EQ) or the "shelf slope" parameter.
         * @return #Biquad filter with the computed coefficients.
         * @see AudioEQ-CookBook:  \link http://www.musicdsp.org/showone.php?id=197 \endlink
         */
        template <FilterType Type, typename... Args>
        constexpr Biquad<T> design(T fc, T sample_rate, T Q, T gain_db = 1) const {
            return RBJFilterDesigner<T, Type>{}(fc, sample_rate, Q, gain_db);
        }
    };

    /**
     * @brief Udo Zölzer filter designer.
     * @tparam T Arithmetic type.
     * @tparam MaxOrder Maximum order.
     */
    template <typename T, std::size_t MaxOrder>
    struct designer<T, DesignerType::Zolzer, MaxOrder> {
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
        template <FilterType Type, typename... Args>
        constexpr Biquad<T> design(T fc, T sample_rate, T Q, T gain_db = 1) const {
            return ZoelzerFilterDesigner<T, Type>{}(fc, sample_rate, Q, gain_db);
        }
    };

    /**
     * @brief Udo Zölzer filter designer.
     * @tparam T Arithmetic type.
     * @tparam MaxOrder Maximum order.
     */
    template <typename T, std::size_t MaxOrder>
    struct designer<T, DesignerType::Butterworth, MaxOrder> {
        template <FilterType Type, typename... Args>
        constexpr auto design(Args... arg) const -> decltype(ButterworthDesigner<T, Type, MaxOrder>{}(arg...)) {
            return ButterworthDesigner<T, Type, MaxOrder>{}.operator()(arg...);
        }
    };

    /**
     * @brief Udo Zölzer filter designer.
     * @tparam T Arithmetic type.
     * @tparam MaxOrder Maximum order.
     */
    template <typename T, std::size_t MaxOrder>
    struct designer<T, DesignerType::ChebyshevI, MaxOrder> {
        template <FilterType Type, typename... Args>
        constexpr auto design(Args... arg) const
            -> decltype(ChebyshevIDesigner<T, Type, MaxOrder>{}(std::declval<Args&&>()...)) {
            return ChebyshevIDesigner<T, Type, MaxOrder>{}(arg...);
        }
    };

    /**
     * @brief Inverse Chebyshev filter designer.
     * @tparam T Arithmetic type.
     * @tparam MaxOrder Maximum order.
     */
    template <typename T, std::size_t MaxOrder>
    struct designer<T, DesignerType::ChebyshevII, MaxOrder> {
        template <FilterType Type, typename... Args>
        constexpr auto design(Args... arg) const
            -> decltype(ChebyshevIIDesigner<T, Type, MaxOrder>{}(std::declval<Args&&>()...)) {
            return ChebyshevIIDesigner<T, Type, MaxOrder>{}(arg...);
        }
    };

    template <typename T, DesignerType Designer, FilterType Type, std::size_t MaxOrder, typename... Args>
    constexpr auto make_filter(Args... arg)
        -> decltype(designer<T, Designer, MaxOrder>{}.template design<Type>(std::declval<Args&&>()...)) {
        const auto creator = designer<T, Designer, MaxOrder>{};
        return creator.template design<Type>(arg...);
    }

}}} // namespace easy::dsp::filter

#endif // EASYDSP_FILTER_HPP
