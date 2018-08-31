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

namespace easy { namespace dsp { namespace filter {

    template <typename T, DesignerType Designer, std::size_t MaxOrder>
    struct designer {};

    template <typename T, std::size_t MaxOrder>
    struct designer<T, DesignerType::RBJ, MaxOrder> {
        template <FilterType Type, typename... Args>
        constexpr auto design(Args... arg) const -> decltype(RBJFilterDesigner<T, Type>{}(std::declval<Args&&>()...)) {
            return RBJFilterDesigner<T, Type>{}(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct designer<T, DesignerType::Zoelzer, MaxOrder> {
        template <FilterType Type, typename... Args>
        constexpr auto design(Args... arg) const
            -> decltype(ZoelzerFilterDesigner<T, Type>{}(std::declval<Args&&>()...)) {
            return ZoelzerFilterDesigner<T, Type>{}(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct designer<T, DesignerType::Butterworth, MaxOrder> {
        template <FilterType Type, typename... Args>
        constexpr auto design(Args... arg) const -> decltype(ButterworthDesigner<T, Type, MaxOrder>{}(arg...)) {
            return ButterworthDesigner<T, Type, MaxOrder>{}.operator()(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct designer<T, DesignerType::ChebyshevI, MaxOrder> {
        template <FilterType Type, typename... Args>
        constexpr auto design(Args... arg) const
            -> decltype(ChebyshevIDesigner<T, Type, MaxOrder>{}(std::declval<Args&&>()...)) {
            return ChebyshevIDesigner<T, Type, MaxOrder>{}(arg...);
        }
    };

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
