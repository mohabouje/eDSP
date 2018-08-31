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
 * Filename: highpass_transformer.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EASYDSP_HIGHPASS_TRANSFORMER_HPP
#define EASYDSP_HIGHPASS_TRANSFORMER_HPP

#include "layout_base.hpp"
#include <easy/dsp/math/constant.hpp>

namespace easy { namespace dsp { namespace filter {

    template <typename T>
    struct HighPassTransformer {
        using value_type = T;

        HighPassTransformer(value_type fc) : f(std::tan(constants<value_type>::pi * fc)) {}

        template <std::size_t AnalogMaxSize, std::size_t DigitalMaxSize>
        void operator()(LayoutBase<T, AnalogMaxSize>& digital, LayoutBase<T, DigitalMaxSize>& analog) {
            digital.reset();
            digital.setNormalW(constants<T>::pi - analog.normalW());
            digital.setNormalGain(analog.normalGain());

            const auto num_poles = analog.numberPoles();
            const auto num_pairs = num_poles / 2;
            for (auto i = 0ul; i < num_pairs; ++i) {
                const auto& pair = analog[i];
                digital.insert_conjugate(transform(pair.poles().first), transform(pair.zeros().second));
            }

            if (math::is_odd(num_poles)) {
                const auto& pair = analog[num_pairs];
                digital.insert(transform(pair.poles().first), transform(pair.zeros().first));
            }
        }

        std::complex<T> transform(const std::complex<T>& c) {
            if (math::is_inf(c)) {
                return std::complex<T>(1, 0);
            }
            constexpr auto one = std::complex<T>(1, 0);
            const auto element = f * c;
            return -(one + element) / (one - element);
        }

    private:
        value_type f;
    };

}}} // namespace easy::dsp::filter

#endif // EASYDSP_HIGHPASS_TRANSFORMER_HPP
