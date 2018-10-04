/* 
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
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

 * File: make_oscillator.hpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 03/10/18.
 */

#ifndef EASYDSP_MAKE_OSCILLATOR_HPP
#define EASYDSP_MAKE_OSCILLATOR_HPP

#include <easy/dsp/oscillators/sawtooth.hpp>
#include <easy/dsp/oscillators/square.hpp>
#include <easy/dsp/oscillators/triangular.hpp>
#include <easy/dsp/oscillators/sinusoidal.hpp>

namespace easy { namespace dsp { namespace oscillators {

    namespace internal {
        template <OscillatorType Type, typename T>
        struct _build_Generator;

        template <typename T>
        struct _build_Generator<OscillatorType::Sinusoidal, T> {
            template <typename... Args>
            constexpr auto build(Args... arg) -> oscillators::sin_oscillator<T> {
                return oscillators::sin_oscillator<T>(arg...);
            }
        };

        template <typename T>
        struct _build_Generator<OscillatorType::Square, T> {
            template <typename... Args>
            constexpr auto build(Args... arg) -> oscillators::square_oscillator<T> {
                return oscillators::square_oscillator<T>(arg...);
            }
        };

        template <typename T>
        struct _build_Generator<OscillatorType::Triangular, T> {
            template <typename... Args>
            constexpr auto build(Args... arg) -> oscillators::triangular_oscillator<T> {
                return oscillators::triangular_oscillator<T>(arg...);
            }
        };

        template <typename T>
        struct _build_Generator<OscillatorType::Sawtooth, T> {
            template <typename... Args>
            constexpr auto build(Args... arg) -> oscillators::sawtooth_oscillator<T> {
                return oscillators::sawtooth_oscillator<T>(arg...);
            }
        };

    } // namespace internal

    /**
     * @brief Creates an oscillator using args as the parameter list for the construction.
     * @tparam T Value type
     * @tparam Type Types of oscillator: sinusoidal, triangle, sawtooth or square.
     * @param arg Arguments parameters to constructs the oscillator.
     * @return An oscillator with the given configuration.
     * @see OscillatorType
     */
    template <typename T, OscillatorType Type, typename... Args>
    constexpr auto make_oscillator(Args... arg) noexcept
        -> decltype(internal::_build_Generator<Type, T>{}.template build(std::declval<Args&&>()...)) {
        return internal::_build_Generator<Type, T>{}.build(arg...);
    }

}}} // namespace easy::dsp::oscillators

#endif //EASYDSP_MAKE_OSCILLATOR_HPP
