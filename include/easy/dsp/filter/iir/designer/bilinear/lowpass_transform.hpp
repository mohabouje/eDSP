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
 * Filename: lowpass_transform.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EASYDSP_LOWPASS_TRANSFORM_HPP
#define EASYDSP_LOWPASS_TRANSFORM_HPP

#include "layout_base.hpp"
#include "easy/dsp/math/constant.hpp"

namespace easy { namespace dsp { namespace filter {

    template <typename T,
              typename Allocator = std::allocator<pz_pair>>
    struct LowPassTransformer {
        using value_type = T;

        LowPassTransformer(value_type fc) :
            f(std::tan(constants<value_type>::pi * fc)) {}

        void operator()(LayoutBase<T, Allocator>& digital,
                        LayoutBase<T, Allocator>& analog) {
            digital.reset();

            const auto num_poles = analog.numberPoles();
            const auto pairs = num_poles / 2;
            for (auto i = 0; i < pairs; ++i) {
                const auto& pair = analog[i];
                digital.insert_conjugate(transform (pair.first.first),
                                         transform (pair.second.first));
            }

            if (num_poles & 1) {
                const auto& pair = analog[pairs];
                digital.insert(transform (pair.first.first),
                            transform (pair.second.first));
            }

            digital.setNormalW(analog.getNormalW());
            digital.setNormalGain(analog.getNormalGain());

        }

        std::complex<T> transform (const std::complex<T>& c) {
            if (meta::is_inf(c)) {
                return std::complex<T>(-1, 0);
            }
            const auto element = f * c;
            return (1. + element) / (1. - element);
        }

    private:
        value_type f;
    };

}}}

#endif // EASYDSP_LOWPASS_TRANSFORM_HPP
