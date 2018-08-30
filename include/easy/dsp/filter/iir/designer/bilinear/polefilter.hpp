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
 * Filename: polefilter.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EASYDSP_POLEFILTER_HPP
#define EASYDSP_POLEFILTER_HPP

#include "layout_base.hpp"
#include "lowpass_transformer.hpp"
#include "highpass_transformer.hpp"
#include "bandpass_transformer.hpp"
#include "bandstop_transformer.hpp"

namespace easy { namespace dsp { namespace filter {


    template <typename T,
              class Designer,
              std::size_t MaxAnalog,
              std::size_t MaxDigital = MaxAnalog>
    struct AbstractFilter {
        using digital_type = LayoutBase<T, MaxDigital>;
        using analog_type = LayoutBase<T, MaxAnalog>;

        template <typename...Args>
        void design(Args... arg) {
            auto* designer = static_cast<Designer*>(this);
            designer.design(std::forward(arg...));
        }

        constexpr const analog_type& analog_layout() const noexcept {
            return analog_;
        }

        constexpr const digital_type& digital_layout() const noexcept {
            return digital_;
        }

    private:
        friend class Designer;
        LayoutBase<T, MaxAnalog> analog_;
        LayoutBase<T, MaxDigital> digital_;
    };


}}}

#endif // EASYDSP_POLEFILTER_HPP
