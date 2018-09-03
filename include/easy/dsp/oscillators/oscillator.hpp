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
 * Filename: oscillator.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EASYDSP_OSCILLATOR_HPP
#define EASYDSP_OSCILLATOR_HPP

#include <easy/dsp/oscillators/sawtooth.hpp>
#include <easy/dsp/oscillators/square.hpp>
#include <easy/dsp/oscillators/triangular.hpp>
#include <easy/dsp/oscillators/sine.hpp>

#include <iterator>
#include <type_traits>
#include <algorithm>

namespace easy { namespace dsp {

    enum class SignalType { Sinusoidal, Square, Sawtooth, Triangular };

    namespace internal {

        template <SignalType Type, typename T>
        struct _build_Generator;

        template <typename T>
        struct _build_Generator<SignalType::Sinusoidal, T> {
            template <typename... Args>
            constexpr auto build(Args... arg) -> oscillators::SinOscillator<T> {
                return oscillators::SinOscillator<T>(arg...);
            }
        };

        template <typename T>
        struct _build_Generator<SignalType::Square, T> {
            template <typename... Args>
            constexpr auto build(Args... arg) -> oscillators::SquareOscillator<T> {
                return oscillators::SquareOscillator<T>(arg...);
            }
        };

        template <typename T>
        struct _build_Generator<SignalType::Triangular, T> {
            template <typename... Args>
            constexpr auto build(Args... arg) -> oscillators::TriangularOscillator<T> {
                return oscillators::TriangularOscillator<T>(arg...);
            }
        };

        template <typename T>
        struct _build_Generator<SignalType::Sawtooth, T> {
            template <typename... Args>
            constexpr auto build(Args... arg) -> oscillators::SawtoothOscillator<T> {
                return oscillators::SawtoothOscillator<T>(arg...);
            }
        };

    } // namespace internal

    template <SignalType Type, typename T, typename... Args>
    constexpr auto make_oscillator(Args... arg) noexcept
        -> decltype(internal::_build_Generator<Type, T>{}.template build(std::declval<Args&&>()...)) {
        return internal::_build_Generator<Type, T>{}.build(arg...);
    }

}} // namespace easy::dsp

#endif // EASYDSP_OSCILLATOR_HPP
