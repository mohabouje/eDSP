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
 * Filename: dcremoval.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_DCREMOVAL_HPP
#define EASYDSP_DCREMOVAL_HPP

#include "easy/dsp/filter/biquad.hpp"

namespace easy { namespace dsp {

    template <typename T>
    class DCRemoval : public filter::Biquad<T> {
    public:
        using size_type  = std::size_t;
        using value_type = T;

        constexpr explicit DCRemoval(value_type alpha);
        constexpr value_type alpha() const noexcept;
        constexpr void setAlpha(value_type alpha) noexcept;
    };

    template <typename T>
    constexpr DCRemoval<T>::DCRemoval(value_type alpha) : filter::Biquad<T>(1, -alpha, 0, 1 - alpha, alpha - 1, 0) {}

    template <typename T>
    constexpr void DCRemoval<T>::setAlpha(value_type alpha) noexcept {
        filter::Biquad<T>::setA1(-alpha);
        filter::Biquad<T>::setB0(1 - alpha);
        filter::Biquad<T>::setB1(alpha - 1);
        filter::Biquad<T>::reset();
    }

    template <typename T>
    constexpr typename DCRemoval<T>::value_type DCRemoval<T>::alpha() const noexcept {
        return -filter::Biquad<T>::a1();
    }
}} // namespace easy::dsp

#endif // EASYDSP_DCREMOVAL_HPP
