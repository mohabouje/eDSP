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
#include <easy/dsp/windowing/bohman.hpp>
#include <easy/dsp/windowing/boxcar.hpp>
#include <easy/dsp/windowing/flat_top.hpp>
#include <easy/dsp/windowing/hamming.hpp>
#include <easy/dsp/windowing/hanning.hpp>
#include <easy/dsp/windowing/kaiser.hpp>
#include <easy/dsp/windowing/rectangular.hpp>
#include <easy/dsp/windowing/triangular.hpp>
#include <easy/dsp/windowing/welch.hpp>

namespace easy { namespace dsp { namespace windowing {

    enum class WindowType {
        Bartlett = 0,
        Blackman,
        BlackmanHarris,
        BlackmanNuttall,
        Bohman,
        Boxcar,
        FlatTop,
        Hamming,
        Hanning,
        Kaiser,
        Rectangular,
        Triangular,
        Welch
    };
    namespace internal {

        template <typename T, WindowType Type>
        struct _buildWindow {};

        template <typename T>
        struct _buildWindow<T, WindowType::Bartlett> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> Bartlett<T> {
                return Bartlett<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::Blackman> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> Blackman<T> {
                return Blackman<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::BlackmanHarris> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> BlackmanHarris<T> {
                return BlackmanHarris<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::BlackmanNuttall> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> BlackmanNuttall<T> {
                return BlackmanNuttall<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::Bohman> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> Bohman<T> {
                return Bohman<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::Boxcar> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> Boxcar<T> {
                return Boxcar<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::FlatTop> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> FlatTop<T> {
                return FlatTop<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::Hamming> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> Hamming<T> {
                return Hamming<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::Hanning> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> Hanning<T> {
                return Hanning<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::Kaiser> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> Kaiser<T> {
                return Kaiser<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::Rectangular> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> Rectangular<T> {
                return Rectangular<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::Triangular> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> Triangular<T> {
                return Triangular<T>{arg...};
            }
        };

        template <typename T>
        struct _buildWindow<T, WindowType::Welch> {
            template <typename... Args>
            constexpr auto operator()(Args... arg) -> Welch<T> {
                return Welch<T>{arg...};
            }
        };
    } // namespace internal

    template <typename T, WindowType Type, typename... Args>
    constexpr auto make_window(Args... arg) -> decltype(internal::_buildWindow<T, Type>{}(std::declval<Args&&>()...)) {
        return internal::_buildWindow<T, Type>{}(arg...);
    }

    template <typename Window, typename BiIterator, typename... Arg>
    inline void generate_window(BiIterator first, BiIterator last, Arg... arg) {
        using size_type   = typename Window::size_type;
        const auto size   = static_cast<size_type>(std::distance(first, last));
        const auto window = Window(size, std::forward(arg...));
        std::copy(std::cbegin(window), std::cend(window), first);
    }

    template <typename Window, typename OutputIterator, typename Size, typename... Arg>
    inline void generate_window(Size size, OutputIterator out, Arg... arg) {
        using size_type   = typename Window::size_type;
        const auto window = Window(static_cast<size_type>(size), std::forward(arg...));
        std::copy(std::cbegin(window), std::cend(window), out);
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_WINDOWING_HPP
