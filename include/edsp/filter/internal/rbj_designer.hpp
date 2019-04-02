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
 * File: biquad_designer.hpp
 * Date: 10/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_FILTER_RBJ_DESIGNER_HPP
#define EDSP_FILTER_RBJ_DESIGNER_HPP

#include <edsp/meta/unused.hpp>
#include <edsp/filter/biquad.hpp>
#include <edsp/math/constant.hpp>
#include <cmath>

namespace edsp { namespace filter {
    template <typename T, filter_type Type>
    struct RBJFilterDesigner {};

    template <typename T>
    struct RBJFilterDesigner<T, filter_type::LowPass> {
        constexpr biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            meta::unused(gain_db);
            const auto omega   = 2 * constants<T>::pi * fc / sample_rate;
            const auto omega_s = std::sin(omega);
            const auto omega_c = std::cos(omega);
            const auto alpha   = omega_s / (2 * Q);

            std::array<T, 3> a{}, b{};
            a[0] = static_cast<T>(1 + alpha);
            a[1] = static_cast<T>(-2 * omega_c);
            a[2] = static_cast<T>(1 - alpha);
            b[0] = static_cast<T>((1 - omega_c) / 2);
            b[1] = static_cast<T>(1 - omega_c);
            b[2] = b[0];
            return biquad<T>(a[0], a[1], a[2], b[0], b[1], b[2]);
        }
    };

    template <typename T>
    struct RBJFilterDesigner<T, filter_type::HighPass> {
        constexpr biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            meta::unused(gain_db);
            const auto omega   = 2 * constants<T>::pi * fc / sample_rate;
            const auto omega_s = std::sin(omega);
            const auto omega_c = std::cos(omega);
            const auto alpha   = omega_s / (2 * Q);

            std::array<T, 3> a{}, b{};
            a[0] = static_cast<T>(1 + alpha);
            a[1] = static_cast<T>(-2 * omega_c);
            a[2] = static_cast<T>(1 - alpha);
            b[0] = static_cast<T>((1 + omega_c) / 2);
            b[1] = static_cast<T>(-(1 + omega_c));
            b[2] = b[0];
            return biquad<T>(a[0], a[1], a[2], b[0], b[1], b[2]);
        }
    };

    template <typename T>
    struct RBJFilterDesigner<T, filter_type::BandPass> {
        constexpr biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            meta::unused(gain_db);
            const auto omega   = 2 * constants<T>::pi * fc / sample_rate;
            const auto omega_s = std::sin(omega);
            const auto omega_c = std::cos(omega);
            const auto alpha   = omega_s / (2 * Q);

            std::array<T, 3> a{}, b{};
            a[0] = static_cast<T>(1 + alpha);
            a[1] = static_cast<T>(-2 * omega_c);
            a[2] = static_cast<T>(1 - alpha);
            b[0] = static_cast<T>(Q * alpha);
            b[1] = 0;
            b[2] = static_cast<T>(-Q * alpha);
            return biquad<T>(a[0], a[1], a[2], b[0], b[1], b[2]);
        }
    };

    template <typename T>
    struct RBJFilterDesigner<T, filter_type::AllPass> {
        constexpr biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            meta::unused(gain_db);
            const auto omega   = 2 * constants<T>::pi * fc / sample_rate;
            const auto omega_s = std::sin(omega);
            const auto omega_c = std::cos(omega);
            const auto alpha   = omega_s / (2 * Q);

            std::array<T, 3> a{}, b{};
            a[0] = static_cast<T>(1 + alpha);
            a[1] = static_cast<T>(-2 * omega_c);
            a[2] = static_cast<T>(1 - alpha);
            b[0] = a[2];
            b[1] = a[1];
            b[2] = a[0];
            return biquad<T>(a[0], a[1], a[2], b[0], b[1], b[2]);
        }
    };

    template <typename T>
    struct RBJFilterDesigner<T, filter_type::LowShelf> {
        constexpr biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            const T A          = std::sqrt(std::pow(10., gain_db / 20));
            const auto omega   = 2 * constants<T>::pi * fc / sample_rate;
            const auto omega_s = std::sin(omega);
            const auto omega_c = std::cos(omega);
            const auto beta    = std::sqrt(A) / Q;

            std::array<T, 3> a{}, b{};
            a[0] = static_cast<T>((A + 1) + (A - 1) * omega_c + beta * omega_s);
            a[1] = static_cast<T>(-2 * ((A - 1) + (A + 1) * omega_c));
            a[2] = static_cast<T>((A + 1) + (A - 1) * omega_c - beta * omega_s);
            b[0] = static_cast<T>(A * ((A + 1) - (A - 1) * omega_c + beta * omega_s));
            b[1] = static_cast<T>(2 * A * ((A - 1) - (A + 1) * omega_c));
            b[2] = static_cast<T>(A * ((A + 1) - (A - 1) * omega_c - beta * omega_s));
            return biquad<T>(a[0], a[1], a[2], b[0], b[1], b[2]);
        }
    };

    template <typename T>
    struct RBJFilterDesigner<T, filter_type::HighShelf> {
        constexpr biquad<T> operator()(T fc, T sample_rate, T Q, T gain_db = 1) const {
            const T A          = std::sqrt(std::pow(10, gain_db / 20));
            const auto omega   = 2 * constants<T>::pi * fc / sample_rate;
            const auto omega_s = std::sin(omega);
            const auto omega_c = std::cos(omega);
            const auto beta    = std::sqrt(A) / Q;

            std::array<T, 3> a{}, b{};
            a[0] = static_cast<T>((A + 1) - (A - 1) * omega_c + beta * omega_s);
            a[1] = static_cast<T>(2 * ((A - 1) - (A + 1) * omega_c));
            a[2] = static_cast<T>((A + 1) - (A - 1) * omega_c - beta * omega_s);
            b[0] = static_cast<T>(A * ((A + 1) + (A - 1) * omega_c + beta * omega_s));
            b[1] = static_cast<T>(-2 * A * ((A - 1) + (A + 1) * omega_c));
            b[2] = static_cast<T>(A * ((A + 1) + (A - 1) * omega_c - beta * omega_s));
            return biquad<T>(a[0], a[1], a[2], b[0], b[1], b[2]);
        }
    };

}} // namespace edsp::filter

#endif // EDSP_FILTER_RBJ_DESIGNER_HPP
