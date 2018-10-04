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
 * Filename: windowing.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_WINDOWING_HPP
#define EASYDSP_WINDOWING_HPP

#include <easy/dsp/windowing/bartlett.hpp>
#include <easy/dsp/windowing/blackman.hpp>
#include <easy/dsp/windowing/blackman_harris.hpp>
#include <easy/dsp/windowing/blackman_nuttall.hpp>
#include <easy/dsp/windowing/boxcar.hpp>
#include <easy/dsp/windowing/flat_top.hpp>
#include <easy/dsp/windowing/hamming.hpp>
#include <easy/dsp/windowing/hanning.hpp>
#include <easy/dsp/windowing/rectangular.hpp>
#include <easy/dsp/windowing/triangular.hpp>
#include <easy/dsp/windowing/welch.hpp>

namespace easy { namespace dsp { namespace windowing {

    /**
     * @brief The WindowType enum represents the type of availables windows
     */
    enum class WindowType {
        Bartlett = 0,    /*!< Bartlett Window */
        Blackman,        /*!< Blackman Window */
        BlackmanHarris,  /*!< Blackman-Harris Window */
        BlackmanNuttall, /*!< Blackman-Nuttall Window*/
        Boxcar,          /*!< Boxcar Window */
        FlatTop,         /*!< FlatTop Window */
        Hamming,         /*!< Hamming Window */
        Hanning,         /*!< Hanning Window */
        Rectangular,     /*!< Rectangular Window */
        Triangular,      /*!< Triangular Window */
        Welch            /*!< Welch Window */
    };

    namespace internal {

        template <WindowType Type>
        struct _build_window {};

        template <>
        struct _build_window<WindowType::Bartlett> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                bartlett(d_first, N);
            }
        };

        template <>
        struct _build_window<WindowType::Blackman> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                blackman(d_first, N);
            }
        };

        template <>
        struct _build_window<WindowType::BlackmanHarris> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                blackman_harris(d_first, N);
            }
        };

        template <>
        struct _build_window<WindowType::BlackmanNuttall> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                blackman_nutall(d_first, N);
            }
        };

        template <>
        struct _build_window<WindowType::Boxcar> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                boxcar(d_first, N);
            }
        };

        template <>
        struct _build_window<WindowType::FlatTop> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                flattop(d_first, N);
            }
        };

        template <>
        struct _build_window<WindowType::Hamming> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                hamming(d_first, N);
            }
        };

        template <>
        struct _build_window<WindowType::Hanning> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                hanning(d_first, N);
            }
        };

        template <>
        struct _build_window<WindowType::Rectangular> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                rectangular(d_first, N);
            }
        };

        template <>
        struct _build_window<WindowType::Triangular> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                triangular(d_first, N);
            }
        };

        template <>
        struct _build_window<WindowType::Welch> {
            template <typename OutIterator, typename Integer>
            constexpr void operator()(OutIterator d_first, Integer N) {
                welch(d_first, N);
            }
        };
    } // namespace internal

    /**
     * @brief Computes a window of the given type and length N and stores the result in the range, beginning at d_first.
     * @tparam Type Type of window to be computed
     * @param N Number of elements to compute.
     * @param d_first Output iterator defining the beginning of the destination range.
     */
    template <WindowType Type, typename OutIterator, typename Integer>
    constexpr void make_window(OutIterator d_first, Integer N) {
        return internal::_build_window<Type>{}(d_first, N);
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_WINDOWING_HPP
