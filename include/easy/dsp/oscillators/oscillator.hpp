/* 
 * EasyDSP, just another repository with a bunch of utilities written in modern C++.
 * Copyright (c) 2018  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
