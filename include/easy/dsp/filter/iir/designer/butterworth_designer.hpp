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
 * Filename: butterworth.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EASYDSP_BIQUAD_BUTTERWORTH_HPP
#define EASYDSP_BIQUAD_BUTTERWORTH_HPP

#include <easy/dsp/utilities/db2mag.hpp>
#include <easy/meta/expects.hpp>
#include <easy/dsp/math/complex.hpp>
#include <easy/dsp/math/constant.hpp>
#include <easy/dsp/filter/iir/designer/bilinear/bandpass_transformer.hpp>
#include <easy/dsp/filter/iir/designer/bilinear/bandstop_transformer.hpp>
#include <easy/dsp/filter/iir/designer/bilinear/lowpass_transformer.hpp>
#include <easy/dsp/filter/iir/designer/bilinear/highpass_transformer.hpp>
#include <easy/dsp/filter/iir/designer/abstract_designer.hpp>

namespace easy { namespace dsp { namespace filter {

    namespace {
        struct LowPassAnalogDesigner {
            template <typename T, std::size_t MaxSize>
            void design(LayoutBase<T, MaxSize>& analog, std::size_t num_poles) const {
                meta::expects(num_poles < MaxSize, "Index out of bounds");

                analog.setNormalW(0);
                analog.setNormalGain(1);
                analog.reset();

                const auto size  = static_cast<T>(num_poles * 2);
                const auto pairs = num_poles / 2;
                for (auto i = 0ul; i < pairs; ++i) {
                    const std::complex<T> c =
                        std::polar(1, constants<T>::two_pi + (2 * i + 1) * constants<T>::pi / size);
                    analog.insert_conjugate(c, math::infinity<T>());
                }

                if (math::is_odd(num_poles)) {
                    analog.insert(std::complex<T>(-1), math::infinity<T>());
                }
            }
        };

        struct LowShelfAnalogDesigner {
            template <typename T, std::size_t MaxSize>
            void design(LayoutBase<T, MaxSize>& analog, std::size_t num_poles, T gain_db) const {
                meta::expects(num_poles < MaxSize, "Index out of bounds");

                analog.setNormalW(constants<T>::pi);
                analog.setNormalGain(1);
                analog.reset();

                const auto size  = static_cast<T>(num_poles * 2);
                const auto g     = std::pow(dsp::db2mag(gain_db), math::inv(n2));
                const auto gp    = -math::inv(g);
                const auto gz    = -g;
                const auto pairs = num_poles / 2;
                for (auto i = 0ul; i < pairs; ++i) {
                    const auto theta = constants<T>::pi * (0.5 - (2 * i - 1) / size);
                    analog.insert_conjugate(std::polar(gp, theta), std::polar(gz, theta));
                }

                if (math::is_odd(num_poles)) {
                    analog.insert(std::complex<T>(gp), std::complex<T>(gz));
                }
            }
        };

        template <typename T, std::size_t MaxSize>
        class LowPass : public AbstractDesigner<T, LowPass, MaxSize> {
            friend class AbstractDesigner<T, LowPassk, MaxSize>;
            void design(std::size_t order, T sample_rate, T cuttoff_frequency) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowPassAnalogDesigner::design(analog_, order);
                LowPassTransformer{normalized_frequency}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class HighPass : public AbstractDesigner<T, HighPass, MaxSize> {
            friend class AbstractDesigner<T, HighPass, MaxSize>;
            void design(std::size_t order, T sample_rate, T cuttoff_frequency) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowPassAnalogDesigner::design(analog_, order);
                HighPassTransformer{normalized_frequency}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandPass : public AbstractDesigner<T, BandPass, MaxSize, 2 * MaxSize> {
            friend class AbstractDesigner<T, BandPass, MaxSize>;
            void design(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowPassAnalogDesigner::design(analog_, order);
                BandPassTransformer{normalized_center, normalized_bandwidth}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandStopPass : public AbstractDesigner<T, BandStopPass, MaxSize, 2 * MaxSize> {
            friend class AbstractDesigner<T, BandStopPass, MaxSize>;
            void design(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowPassAnalogDesigner::design(analog_, order);
                BandStopTransformer{normalized_center, normalized_bandwidth}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class LowShelfPass : public AbstractDesigner<T, LowShelfPass, MaxSize> {
            friend class AbstractDesigner<T, LowShelfPass, MaxSize>;
            void design(std::size_t order, T sample_rate, T cuttoff_frequency, T gain_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowShelfAnalogDesigner::design(analog_, order, gain_db);
                HighPassTransformer{normalized_frequency}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class HighShelfPass : public AbstractDesigner<T, HighShelfPass, MaxSize> {
            friend class AbstractDesigner<T, HighShelfPass, MaxSize>;
            void design(std::size_t order, T sample_rate, T cuttoff_frequency, T gain_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowShelfAnalogDesigner::design(analog_, order, gain_db);
                HighPassTransformer{normalized_frequency}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandShelfPass : public AbstractDesigner<T, BandShelfPass, MaxSize, 2 * MaxSize> {
            friend class AbstractDesigner<T, BandShelfPass, MaxSize, 2 * MaxSize>;
            void design(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency, T gain_db) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowShelfAnalogDesigner::design(analog_, order, gain_db);
                BandPassTransformer{normalized_center, normalized_bandwidth}(digital_, analog_);

                // HACK!
                digital_.setNormalW(normalized_center < 0.25 ? constants<T>::pi : 0);
                digital_.setNormalGain(1);
            }
        };

    } // namespace

    template <typename T, FilterType Type, std::size_t MaxOrder>
    struct ButterworthDesigner {};

    template <typename T, std::size_t MaxOrder>
    struct ButterworthDesigner<T, FilterType::LowPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return LowPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ButterworthDesigner<T, FilterType::HighPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return HighPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ButterworthDesigner<T, FilterType::BandPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return BandPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ButterworthDesigner<T, FilterType::BandStop, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return BandStopPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ButterworthDesigner<T, FilterType::LowShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return LowShelfPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ButterworthDesigner<T, FilterType::HighShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return HighShelfPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ButterworthDesigner<T, FilterType::BandShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return BandShelfPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

}}} // namespace easy::dsp::filter::butterworth

#endif // EASYDSP_BIQUAD_BUTTERWORTH_HPP
