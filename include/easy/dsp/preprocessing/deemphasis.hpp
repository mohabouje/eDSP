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
 * Filename: de_emphasis.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_DE_EMPHASIS_HPP
#define EASYDSP_DE_EMPHASIS_HPP

#include "easymeet/dsp/filter/biquad.hpp"

namespace easy { namespace dsp {

    template <typename T>
    class DeEmphasis : public filter::Biquad<T> {
    public:
        using size_type  = std::size_t;
        using value_type = T;

        constexpr explicit DeEmphasis(ereal alpha);
        constexpr value_type alpha() const noexcept;
        constexpr void set_alpha(value_type alpha) noexcept;
    };

    template <typename T>
    constexpr DeEmphasis<T>::DeEmphasis(ereal alpha) : filter::Biquad<T>(1, 0, 0, 1, alpha, 0) {}

    template <typename T>
    constexpr void DeEmphasis<T>::set_alpha(value_type alpha) noexcept {
        filter::Biquad<T>::set_b1(alpha);
        filter::Biquad<T>::reset();
    }

    template <typename T>
    constexpr typename DeEmphasis<T>::value_type DeEmphasis<T>::alpha() const noexcept {
        return filter::Biquad<T>::b1();
    }

}} // namespace easy::dsp

#endif // EASYDSP_DE_EMPHASIS_HPP
