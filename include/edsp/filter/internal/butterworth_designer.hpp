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
 * File: butterworth.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EDSP_BIQUAD_BUTTERWORTH_HPP
#define EDSP_BIQUAD_BUTTERWORTH_HPP

#include <edsp/converter/db2mag.hpp>
#include <edsp/meta/expects.hpp>
#include <edsp/math/complex.hpp>
#include <edsp/math/constant.hpp>
#include <edsp/filter/internal/bilinear/bandpass_transformer.hpp>
#include <edsp/filter/internal/bilinear/bandstop_transformer.hpp>
#include <edsp/filter/internal/bilinear/lowpass_transformer.hpp>
#include <edsp/filter/internal/bilinear/highpass_transformer.hpp>
#include <edsp/filter/internal/abstract_designer.hpp>
#include <edsp/filter/internal/bilinear/layout_base.hpp>

namespace edsp { namespace filter {

    namespace butterworth {
        struct LowPassAnalogDesigner {
            template <typename T, std::size_t MaxSize>
            void design(LayoutBase<T, MaxSize>& analog, std::size_t num_poles) const {
                meta::expects(num_poles <= MaxSize, "Index out of bounds");

                analog.set_w(0);
                analog.set_gain(1);
                analog.reset();

                const auto size  = static_cast<T>(num_poles * 2);
                const auto pairs = num_poles / 2;
                for (auto i = 0ul; i < pairs; ++i) {
                    const std::complex<T> c =
                        std::polar(static_cast<T>(1), constants<T>::half_pi + (2 * i + 1) * constants<T>::pi / size);
                    analog.insert_conjugate(c, math::infinity<T>());
                }

                if (math::is_odd(num_poles)) {
                    analog.insert(std::complex<T>(-1, 0), math::infinity<T>());
                }
            }
        };

        struct LowShelfAnalogDesigner {
            template <typename T, std::size_t MaxSize>
            void design(LayoutBase<T, MaxSize>& analog, std::size_t num_poles, T gain_db) const {
                meta::expects(num_poles <= MaxSize, "Index out of bounds");

                analog.set_w(constants<T>::pi);
                analog.set_gain(1);
                analog.reset();

                const auto size  = static_cast<T>(num_poles * 2);
                const auto g     = std::pow(converter::db2mag(gain_db), math::inv(size));
                const auto gp    = -math::inv(g);
                const auto gz    = -g;
                const auto pairs = num_poles / 2;
                for (auto i = 1ul; i <= pairs; ++i) {
                    const auto theta = static_cast<T>(constants<T>::pi * (0.5 - (2 * i - 1) / size));
                    analog.insert_conjugate(std::polar(gp, theta), std::polar(gz, theta));
                }

                if (math::is_odd(num_poles)) {
                    analog.insert(std::complex<T>(gp), std::complex<T>(gz));
                }
            }
        };

        template <typename T, std::size_t MaxSize>
        class LowPass : public AbstractDesigner<T, LowPass<T, MaxSize>, MaxSize> {
            friend struct AbstractDesigner<T, LowPass, MaxSize>;
            void operator()(std::size_t order, T sample_rate, T cuttoff_frequency) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowPassAnalogDesigner{}.design(this->analog_, order);
                LowPassTransformer<T>{normalized_frequency}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class HighPass : public AbstractDesigner<T, HighPass<T, MaxSize>, MaxSize> {
            friend struct AbstractDesigner<T, HighPass, MaxSize>;
            void operator()(std::size_t order, T sample_rate, T cuttoff_frequency) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowPassAnalogDesigner{}.design(this->analog_, order);
                HighPassTransformer<T>{normalized_frequency}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandPass : public AbstractDesigner<T, BandPass<T, MaxSize>, MaxSize, 2 * MaxSize> {
            friend struct AbstractDesigner<T, BandPass, MaxSize, 2 * MaxSize>;
            void operator()(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowPassAnalogDesigner{}.design(this->analog_, order);
                BandPassTransformer<T>{normalized_center, normalized_bandwidth}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandStopPass : public AbstractDesigner<T, BandStopPass<T, MaxSize>, MaxSize, 2 * MaxSize> {
            friend struct AbstractDesigner<T, BandStopPass, MaxSize, 2 * MaxSize>;
            void operator()(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowPassAnalogDesigner{}.design(this->analog_, order);
                BandStopTransformer<T>{normalized_center, normalized_bandwidth}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class LowShelfPass : public AbstractDesigner<T, LowShelfPass<T, MaxSize>, MaxSize> {
            friend struct AbstractDesigner<T, LowShelfPass, MaxSize>;
            void operator()(std::size_t order, T sample_rate, T cuttoff_frequency, T gain_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowShelfAnalogDesigner{}.design(this->analog_, order, gain_db);
                LowPassTransformer<T>{normalized_frequency}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class HighShelfPass : public AbstractDesigner<T, HighShelfPass<T, MaxSize>, MaxSize> {
            friend struct AbstractDesigner<T, HighShelfPass, MaxSize>;
            void operator()(std::size_t order, T sample_rate, T cuttoff_frequency, T gain_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowShelfAnalogDesigner{}.design(this->analog_, order, gain_db);
                HighPassTransformer<T>{normalized_frequency}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandShelfPass : public AbstractDesigner<T, BandShelfPass<T, MaxSize>, MaxSize, 2 * MaxSize> {
            friend struct AbstractDesigner<T, BandShelfPass, MaxSize, 2 * MaxSize>;
            void operator()(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency, T gain_db) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowShelfAnalogDesigner{}.design(this->analog_, order, gain_db);
                BandPassTransformer<T>{normalized_center, normalized_bandwidth}(this->analog_, this->digital_);

                // HACK!
                this->digital_.set_w(normalized_center < 0.25 ? constants<T>::pi : 0);
                this->digital_.set_gain(1);
            }
        };

    } // namespace butterworth

    template <typename T, filter_type Type, std::size_t MaxOrder>
    struct butterworth_designer {};

    template <typename T, std::size_t MaxOrder>
    struct butterworth_designer<T, filter_type::LowPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(butterworth::LowPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return butterworth::LowPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct butterworth_designer<T, filter_type::HighPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(butterworth::HighPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return butterworth::HighPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct butterworth_designer<T, filter_type::BandPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(butterworth::BandPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return butterworth::BandPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct butterworth_designer<T, filter_type::BandStop, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(butterworth::BandStopPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return butterworth::BandStopPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct butterworth_designer<T, filter_type::LowShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(butterworth::LowShelfPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return butterworth::LowShelfPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct butterworth_designer<T, filter_type::HighShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(butterworth::HighShelfPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return butterworth::HighShelfPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct butterworth_designer<T, filter_type::BandShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(butterworth::BandShelfPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return butterworth::BandShelfPass<T, MaxOrder>{}.design(arg...);
        }
    };

}} // namespace edsp::filter

#endif // EDSP_BIQUAD_BUTTERWORTH_HPP
