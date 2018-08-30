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

#include <easy/dsp/filter/iir/biquad.hpp>
#include <easy/dsp/filter/iir/biquad_cascade.hpp>
#include <easy/dsp/filter/filter_types.hpp>

#include <easy/dsp/filter/iir/designer/rbj_designer.hpp>
#include <easy/dsp/filter/iir/designer/zoelzer_designer.hpp>
#include <easy/dsp/filter/iir/designer/butterworth_designer.hpp>
#include <easy/dsp/filter/iir/designer/chebyshev_I_designer.hpp>
#include <easy/dsp/filter/iir/designer/chebyshev_II_designer.hpp>

namespace easy { namespace dsp  { namespace filter {

    template <typename T,
              DesignerType Designer,
              std::size_t MaxOrder>
    struct designer {};


    template <typename T, std::size_t MaxOrder = 100>
    struct designer<T, DesignerType::RBJ, MaxOrder> {
        template <FilterType Type,
                  typename... Args>
        constexpr Biquad<T> design(Args... arg) const {
            return RBJFilterDesigner<Type>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder = 100>
    struct designer<T, DesignerType::Zoelzer, MaxOrder> {
        template <FilterType Type,
                  typename... Args>
        constexpr Biquad<T> design(Args... arg) const {
            return ZoelzerFilterDesigner<Type>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder = 100>
    struct designer<T, DesignerType::Butterworth, MaxOrder> {
        template <FilterType Type,
                  typename... Args>
        constexpr auto design(Args... arg) const -> decltype(ButterworthDesigner<T, Type, MaxOrder>::operator()) {
            return ButterworthDesigner<T, Type, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder = 100>
    struct designer<T, DesignerType::ChebyshevI, MaxOrder> {
        template <FilterType Type,
                  typename... Args>
        constexpr auto design(Args... arg) const -> decltype(ChebyshevIDesigner<T, Type, MaxOrder>::operator()) {
            return ChebyshevIDesigner<T, Type, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder = 100>
    struct designer<T, DesignerType::Butterworth, MaxOrder> {
        template <FilterType Type,
                  typename... Args>
        constexpr auto design(Args... arg) const -> decltype(ChebyshevIIDesigner<T, Type, MaxOrder>::operator()) {
            return ChebyshevIIDesigner<T, Type, MaxOrder>{}(std::forward(arg...));
        }
    };


    template <typename T,
              DesignerType Designer,
              FilterType Type,
              std::size_t MaxSize,
              typename... Arg>
    constexpr auto make_filter(Arg... arg) -> decltype(designer<T, Designer, MaxOrder>::design<Type, Arg...>()) {
        const auto creator = designer<T, Designer, MaxOrder>{};
        return creator.design(std::forward(arg...));
    }

}}}

#endif // EASYDSP_FILTER_HPP
