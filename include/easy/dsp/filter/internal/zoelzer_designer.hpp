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
 * Filename: zoelzer_designer.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EASYDSP_ZOELZER_DESIGNER_HPP
#define EASYDSP_ZOELZER_DESIGNER_HPP

#include <easy/dsp/filter/biquad.hpp>
#include <easy/dsp/math/constant.hpp>
#include <easy/dsp/converter/db2mag.hpp>
#include <easy/dsp/math/numeric.hpp>
#include <easy/meta/unused.hpp>
#include <cmath>

namespace easy { namespace dsp { namespace filter {
    template <typename T, FilterType Type>
    struct ZoelzerFilterDesigner {};

    template <typename T>
    struct ZoelzerFilterDesigner<T, FilterType::LowPass> {
        constexpr Biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            meta::unused(gain_db);
            const auto K    = std::tan(constants<T>::pi * fc / sample_rate);
            const auto norm = 1 / (1 + K / Q + K * K);
            const auto b0   = K * K * norm;
            const auto b1   = 2 * b0;
            const auto b2   = b0;
            const auto a1   = 2 * (K * K - 1) * norm;
            const auto a2   = (1 - K / Q + K * K) * norm;
            return Biquad<T>(1, a1, a2, b0, b1, b2);
        }
    };

    template <typename T>
    struct ZoelzerFilterDesigner<T, FilterType::HighPass> {
        constexpr Biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            meta::unused(gain_db);
            const auto K    = std::tan(constants<T>::pi * fc / sample_rate);
            const auto norm = 1 / (1 + K / Q + K * K);
            const auto b0   = 1 * norm;
            const auto b1   = -2 * b0;
            const auto b2   = b0;
            const auto a1   = 2 * (K * K - 1) * norm;
            const auto a2   = (1 - K / Q + K * K) * norm;
            return Biquad<T>(1, a1, a2, b0, b1, b2);
        }
    };

    template <typename T>
    struct ZoelzerFilterDesigner<T, FilterType::BandPassSkirtGain> {
        constexpr Biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            meta::unused(gain_db);
            const auto K    = std::tan(constants<T>::pi * fc / sample_rate);
            const auto norm = 1 / (1 + K / Q + K * K);
            const auto b0   = K / Q * norm;
            const auto b1   = 0;
            const auto b2   = -b0;
            const auto a1   = 2 * (K * K - 1) * norm;
            const auto a2   = (1 - K / Q + K * K) * norm;
            return Biquad<T>(1, a1, a2, b0, b1, b2);
        }
    };

    template <typename T>
    struct ZoelzerFilterDesigner<T, FilterType::Notch> {
        constexpr Biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            meta::unused(gain_db);
            const auto K    = std::tan(constants<T>::pi * fc / sample_rate);
            const auto norm = 1 / (1 + K / Q + K * K);
            const auto b0   = (1 + K * K) * norm;
            const auto b1   = 2 * (K * K - 1) * norm;
            const auto b2   = b0;
            const auto a1   = b1;
            const auto a2   = (1 - K / Q + K * K) * norm;
            return Biquad<T>(1, a1, a2, b0, b1, b2);
        }
    };

    template <typename T>
    struct ZoelzerFilterDesigner<T, FilterType::PeakingEQ> {
        constexpr Biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            const auto V = db2mag(gain_db);
            const auto K = std::tan(constants<T>::pi * fc / sample_rate);
            if (gain_db >= 0) { // boost
                const auto norm = 1 / (1 + 1 / Q * K + K * K);
                const auto b0   = (1 + V / Q * K + K * K) * norm;
                const auto b1   = 2 * (K * K - 1) * norm;
                const auto b2   = (1 - V / Q * K + K * K) * norm;
                const auto a1   = b1;
                const auto a2   = (1 - 1 / Q * K + K * K) * norm;
                return Biquad<T>(1, a1, a2, b0, b1, b2);
            } else { // cut
                const auto norm = 1 / (1 + V / Q * K + K * K);
                const auto b0   = (1 + 1 / Q * K + K * K) * norm;
                const auto b1   = 2 * (K * K - 1) * norm;
                const auto b2   = (1 - 1 / Q * K + K * K) * norm;
                const auto a1   = b1;
                const auto a2   = (1 - V / Q * K + K * K) * norm;
                return Biquad<T>(1, a1, a2, b0, b1, b2);
            }
        }
    };

    template <typename T>
    struct ZoelzerFilterDesigner<T, FilterType::LowShelf> {
        constexpr Biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            meta::unused(Q);
            const auto V = db2mag(gain_db);
            const auto K = std::tan(constants<T>::pi * fc / sample_rate);
            if (gain_db >= 0) { // boost
                const auto norm = 1 / (1 + constants<T>::root_two * K + K * K);
                const auto b0   = (1 + std::sqrt(2 * V) * K + V * K * K) * norm;
                const auto b1   = 2 * (V * K * K - 1) * norm;
                const auto b2   = (1 - std::sqrt(2 * V) * K + V * K * K) * norm;
                const auto a1   = 2 * (K * K - 1) * norm;
                const auto a2   = (1 - constants<T>::root_two * K + K * K) * norm;
                return Biquad<T>(1, a1, a2, b0, b1, b2);
            } else { // cut
                const auto norm = 1 / (1 + std::sqrt(2 * V) * K + V * K * K);
                const auto b0   = (1 + constants<T>::root_two * K + K * K) * norm;
                const auto b1   = 2 * (K * K - 1) * norm;
                const auto b2   = (1 - constants<T>::root_two * K + K * K) * norm;
                const auto a1   = 2 * (V * K * K - 1) * norm;
                const auto a2   = (1 - std::sqrt(2 * V) * K + V * K * K) * norm;
                return Biquad<T>(1, a1, a2, b0, b1, b2);
            }
        }
    };

    template <typename T>
    struct ZoelzerFilterDesigner<T, FilterType::HighShelf> {
        constexpr Biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            meta::unused(Q);
            const auto V = db2mag(gain_db);
            const auto K = std::tan(constants<T>::pi * fc / sample_rate);
            if (gain_db >= 0) { // boost
                const auto norm = 1 / (1 + constants<T>::root_two * K + K * K);
                const auto b0   = (V + std::sqrt(2 * V) * K + K * K) * norm;
                const auto b1   = 2 * (K * K - V) * norm;
                const auto b2   = (V - std::sqrt(2 * V) * K + K * K) * norm;
                const auto a1   = 2 * (K * K - 1) * norm;
                const auto a2   = (1 - constants<T>::root_two * K + K * K) * norm;
                return Biquad<T>(1, a1, a2, b0, b1, b2);
            } else { // cut
                const auto norm = 1 / (V + std::sqrt(2 * V) * K + K * K);
                const auto b0   = (1 + constants<T>::root_two * K + K * K) * norm;
                const auto b1   = 2 * (K * K - 1) * norm;
                const auto b2   = (1 - constants<T>::root_two * K + K * K) * norm;
                const auto a1   = 2 * (K * K - V) * norm;
                const auto a2   = (V - std::sqrt(2 * V) * K + K * K) * norm;
                return Biquad<T>(b0, b1, b2, a1, a1, a2);
            }
        }
    };

}}} // namespace easy::dsp::filter

#endif // EASYDSP_ZOELZER_DESIGNER_HPP
