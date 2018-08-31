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
 * Filename: bandpass_transformer.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EASYDSP_BANDPASS_TRANSFORMER_HPP
#define EASYDSP_BANDPASS_TRANSFORMER_HPP

#include "layout_base.hpp"
#include <easy/dsp/math/constant.hpp>
#include <easy/dsp/math/complex.hpp>

namespace easy { namespace dsp { namespace filter {

    template <typename T>
    struct BandPassTransformer {
        using value_type = T;

        BandPassTransformer(value_type fc, value_type fw) {
            initialize(fc, fw);
        }

        void initialize(value_type fc, value_type fw) {
            ww  = constants<T>::two_pi * fw;
            wc2 = constants<T>::two_pi * fc - ww / 2;
            wc  = wc2 + ww;

            if (wc2 < 1e-8)
                wc2 = 1e-8;
            if (wc > constants<T>::pi - 1e-8)
                wc = constants<T>::pi - 1e-8;

            a    = std::cos((wc + wc2) * 0.5) / std::cos((wc - wc2) * 0.5);
            b    = math::inv(std::tan((wc - wc2) * 0.5));
            a2   = a * a;
            b2   = b * b;
            ab   = a * b;
            ab_2 = 2 * ab;
        }

        template <std::size_t AnalogMaxSize, std::size_t DigitalMaxSize>
        void operator()(LayoutBase<T, AnalogMaxSize>& digital, LayoutBase<T, DigitalMaxSize>& analog) {
            digital.reset();

            const auto num_poles = analog.numberPoles();
            const auto num_pairs = num_poles / 2;
            for (auto i = 0ul; i < num_pairs; ++i) {
                const auto& pair = analog[i];
                const auto p1    = transform(pair.poles().first);
                const auto z1    = transform(pair.zeros().first);
                digital.insert_conjugate(p1.first, z1.first);
                digital.insert_conjugate(p1.second, z1.second);
            }

            if (math::is_odd(num_poles)) {
                const auto& pair = analog[num_pairs];
                const auto poles = transform(pair.poles().first);
                const auto zeros = transform(pair.zeros().first);
                digital.insert(poles, zeros);
            }

            const auto wn = analog.normalW();
            digital.setNormalW(2 * std::atan(std::sqrt(std::tan((wc + wn) * 0.5) + std::tan((wc2 + wn) * 0.5))));
            digital.setNormalGain(analog.normalGain());
        }

        complex_pair<T> transform(const std::complex<T>& initial) {
            if (math::is_inf(initial)) {
                return std::complex<T>(-1, 1);
            }
            const auto c       = (std::complex<T>(1, 0) + initial) / (std::complex<T>(1, 0) - initial);

            auto v = math::addmul(std::complex<T>(0, 0), 4 * (b2 * (a2 - 1) + 1), c);
            v += 8 * (b2 * (a2 - 1) - 1);
            v *= c;
            v += 4 * (b2 * (a2 - 1) + 1);
            v = std::sqrt(v);

            auto u = -v;
            u      = math::addmul(u, ab_2, c);
            u += ab_2;

            v = math::addmul(v, ab_2, c);
            v += ab_2;

            const auto d = math::addmul(std::complex<T>(0, 0), 2 * (b - 1), c) + 2 * (1 + b);

            return {u / d, v / d};
        }

    private:
        value_type ww{0};
        value_type wc2{0}, wc{0};
        value_type a{0}, b{0}, a2{0}, b2{0}, ab{0}, ab_2{0};
    };

}}} // namespace easy::dsp::filter

#endif // EASYDSP_BANDPASS_TRANSFORMER_HPP
