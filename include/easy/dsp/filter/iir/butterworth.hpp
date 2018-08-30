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
#include <easy/dsp/filter/iir/designer/bilinear/polefilter.hpp>

namespace easy { namespace dsp { namespace filter { namespace butterworth {

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
            void design(LayoutBase<T, MaxSize>& analog, std::size_t num_poles, T gain) const {
                meta::expects(num_poles < MaxSize, "Index out of bounds");

                analog.setNormalW(constants<T>::pi);
                analog.setNormalGain(1);
                analog.reset();

                const auto size  = static_cast<T>(num_poles * 2);
                const auto g     = std::pow(dsp::db2mag(gain), math::inv(n2));
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
    } // namespace

    template <typename T, std::size_t MaxSize>
    class LowPass : public AbstractFilter<T, LowPass, MaxSize> {
        friend class AbstractFilter<T, LowPassk, MaxSize>;
        void design(std::size_t order, T sample_rate, T cuttoff_frequency) {
            const auto normalized_frequency = cuttoff_frequency / sample_rate;
            LowPassAnalogDesigner::design(analog_, order);
            LowPassTransformer{normalized_frequency}(digital_, analog_);
        }
    };

    template <typename T, std::size_t MaxSize>
    class HighPass : public AbstractFilter<T, HighPass, MaxSize> {
        friend class AbstractFilter<T, HighPass, MaxSize>;
        void design(std::size_t order, T sample_rate, T cuttoff_frequency) {
            const auto normalized_frequency = cuttoff_frequency / sample_rate;
            LowPassAnalogDesigner::design(analog_, order);
            HighPassTransformer{normalized_frequency}(digital_, analog_);
        }
    };

    template <typename T, std::size_t MaxSize>
    class BandPass : public AbstractFilter<T, BandPass, MaxSize, 2 * MaxSize> {
        friend class AbstractFilter<T, BandPass, MaxSize>;
        void design(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency) {
            const auto normalized_center    = center_frequency / sample_rate;
            const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
            LowPassAnalogDesigner::design(analog_, order);
            BandPassTransformer{normalized_center, normalized_bandwidth}(digital_, analog_);
        }
    };

    template <typename T, std::size_t MaxSize>
    class BandStopPass : public AbstractFilter<T, BandStopPass, MaxSize, 2 * MaxSize> {
        friend class AbstractFilter<T, BandStopPass, MaxSize>;
        void design(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency) {
            const auto normalized_center    = center_frequency / sample_rate;
            const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
            LowPassAnalogDesigner::design(analog_, order);
            BandStopTransformer{normalized_center, normalized_bandwidth}(digital_, analog_);
        }
    };

    template <typename T, std::size_t MaxSize>
    class LowShelfPass : public AbstractFilter<T, LowShelfPass, MaxSize> {
        friend class AbstractFilter<T, LowShelfPass, MaxSize>;
        void design(std::size_t order, T sample_rate, T cuttoff_frequency, T gain_db) {
            const auto normalized_frequency = cuttoff_frequency / sample_rate;
            LowShelfAnalogDesigner::design(analog_, order, gain_db);
            HighPassTransformer{normalized_frequency}(digital_, analog_);
        }
    };

    template <typename T, std::size_t MaxSize>
    class HighShelfPass : public AbstractFilter<T, HighShelfPass, MaxSize> {
        friend class AbstractFilter<T, HighShelfPass, MaxSize>;
        void design(std::size_t order, T sample_rate, T cuttoff_frequency, T gain_db) {
            const auto normalized_frequency = cuttoff_frequency / sample_rate;
            LowShelfAnalogDesigner::design(analog_, order, gain_db);
            HighPassTransformer{normalized_frequency}(digital_, analog_);
        }
    };

    template <typename T, std::size_t MaxSize>
    class BandShelfPass : public AbstractFilter<T, BandShelfPass, MaxSize, 2 * MaxSize> {
        friend class AbstractFilter<T, BandShelfPass, MaxSize, 2 * MaxSize>;
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

}}}} // namespace easy::dsp::filter::butterworth

#endif // EASYDSP_BIQUAD_BUTTERWORTH_HPP
