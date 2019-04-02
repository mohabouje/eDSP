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
 * File: windowing.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EDSP_WINDOWING_HPP
#define EDSP_WINDOWING_HPP

#include <edsp/windowing/bartlett.hpp>
#include <edsp/windowing/blackman.hpp>
#include <edsp/windowing/blackman_harris.hpp>
#include <edsp/windowing/blackman_nuttall.hpp>
#include <edsp/windowing/boxcar.hpp>
#include <edsp/windowing/flattop.hpp>
#include <edsp/windowing/hamming.hpp>
#include <edsp/windowing/hanning.hpp>
#include <edsp/windowing/rectangular.hpp>
#include <edsp/windowing/triangular.hpp>
#include <edsp/windowing/welch.hpp>

namespace edsp { namespace windowing {

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
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                bartlett(first, last);
            }
        };

        template <>
        struct _build_window<WindowType::Blackman> {
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                blackman(first, last);
            }
        };

        template <>
        struct _build_window<WindowType::BlackmanHarris> {
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                blackman_harris(first, last);
            }
        };

        template <>
        struct _build_window<WindowType::BlackmanNuttall> {
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                blackman_nutall(first, last);
            }
        };

        template <>
        struct _build_window<WindowType::Boxcar> {
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                boxcar(first, last);
            }
        };

        template <>
        struct _build_window<WindowType::FlatTop> {
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                flattop(first, last);
            }
        };

        template <>
        struct _build_window<WindowType::Hamming> {
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                hamming(first, last);
            }
        };

        template <>
        struct _build_window<WindowType::Hanning> {
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                hanning(first, last);
            }
        };

        template <>
        struct _build_window<WindowType::Rectangular> {
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                rectangular(first, last);
            }
        };

        template <>
        struct _build_window<WindowType::Triangular> {
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                triangular(first, last);
            }
        };

        template <>
        struct _build_window<WindowType::Welch> {
            template <typename OutputIt>
            constexpr void operator()(OutputIt first, OutputIt last) {
                welch(first, last);
            }
        };
    } // namespace internal

    /**
     * @brief Computes a window of the given type and length N and stores the result in the range, beginning at d_first.
     * @tparam Type Type of window to be computed
     * @param first Input iterator defining the beginning of the output range.
     * @param last Input iterator defining the ending of the output range.
     */
    template <WindowType Type, typename OutputIt>
    constexpr void make_window(OutputIt first, OutputIt last) {
        return internal::_build_window<Type>{}(first, last);
    }

}} // namespace edsp::windowing

#endif // EDSP_WINDOWING_HPP
