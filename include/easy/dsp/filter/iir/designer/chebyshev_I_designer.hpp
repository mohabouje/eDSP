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
 * Filename: chebyshev_i.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EASYDSP_CHEBYSHEV_I_HPP
#define EASYDSP_CHEBYSHEV_I_HPP

#include <easy/dsp/utilities/db2mag.hpp>
#include <easy/meta/expects.hpp>
#include <easy/dsp/math/complex.hpp>
#include <easy/dsp/math/constant.hpp>
#include <easy/dsp/filter/filter_types.hpp>
#include <easy/dsp/filter/iir/designer/bilinear/bandpass_transformer.hpp>
#include <easy/dsp/filter/iir/designer/bilinear/bandstop_transformer.hpp>
#include <easy/dsp/filter/iir/designer/bilinear/lowpass_transformer.hpp>
#include <easy/dsp/filter/iir/designer/bilinear/highpass_transformer.hpp>
#include <easy/dsp/filter/iir/designer/abstract_designer.hpp>

namespace easy { namespace dsp { namespace filter {

    namespace {
        struct LowPassAnalogDesigner {
            template <typename T, std::size_t MaxSize>
            void design(LayoutBase<T, MaxSize>& analog, std::size_t num_poles, T ripple_db) const {
                meta::expects(num_poles < MaxSize, "Index out of bounds");
                analog.reset();

                const auto eps     = std::sqrt(math::inv(std::exp(-ripple_db * 0.1 * constants<T>::ln_ten) - 1));
                const auto v0      = std::asinh(math::inv(eps)) / num_poles;
                const auto sinh_v0 = -std::sinh(v0);
                const auto cosh_v0 = std::cosh(v0);

                const auto size  = static_cast<T>(num_poles * 2);
                const auto pairs = num_poles / 2;
                for (auto i = 0ul; i < pairs; ++i) {
                    const auto k = 2 * i + 1 - num_poles;
                    const auto a = sinh_v0 * std::cos(k * constants<T>::pi / size);
                    const auto b = cosh_v0 * std::sin(k * constants<T>::pi / size);
                    analog.insert_conjugate(std::complex<T>(a, b), math::infinity<T>());
                }

                if (math::is_odd(num_poles)) {
                    analog.insert(std::complex<T>(sinh_v0, 0), math::infinity<T>());
                    analog.setNormalW(0);
                    analog.setNormalGain(1);
                } else {
                    analog.setNormalW(0);
                    analog.setNormalGain(dsp::db2mag(-ripple));
                }
            }
        };

        struct LowShelfAnalogDesigner {
            template <typename T, std::size_t MaxSize>
            void design(LayoutBase<T, MaxSize>& analog, std::size_t num_poles, T gain_db, T ripple_db) const {
                meta::expects(num_poles < MaxSize, "Index out of bounds");

                analog.setNormalW(constants<T>::pi);
                analog.setNormalGain(1);
                analog.reset();

                gain_db = -gain_db;
                if (ripple_db >= std::fabs(gain_db))
                    ripple_db = std::fabs(gain_db);
                if (gain_db < 0)
                    ripple_db = -ripple_db;

                const auto G  = dsp::db2mag(gain_db);
                const auto Gb = dsp::db2mag(gain_db - ripple_db);
                const auto G0 = 1;
                const auto g0 = std::pow(G0, math::inv(num_poles));
                const auto eps =
                    (Gb != G0) ? std::sqrt((math::square(G) - math::square(Gb)) / (math::square(Gb) - math::square(G0)))
                               : G - 1;
                const auto b =
                    std::pow(G / eps + Gb * std::sqrt(1 + math::inv(math::square(eps))), math::inv(num_poles));
                const auto u      = log(b / g0);
                const auto v      = log(pow(1. / eps + sqrt(1 + 1 / (eps * eps)), 1. / numPoles));
                const auto sinh_u = std::sinh(u);
                const auto sinh_v = std::sinh(v);
                const auto cosh_u = std::cosh(u);
                const auto cosh_v = std::cosh(v);
                const auto size   = static_cast<T>(2 * num_poles);
                const auto pairs  = numPoles / 2;
                for (auto i = 0ul; i < pairs; ++i) {
                    const auto a  = constants<T>::pi * (2 * i - 1) / size;
                    const auto sn = std::sin(a);
                    const auto cs = std::cos(a);
                    analog.insert_conjugate(std::complex<T>(-sn * sinh_u, cs * cosh_u),
                                            std::complex<T>(-sn * sinh_v, cs * cosh_v));
                }

                if (math::is_odd(num_poles)) {
                    analog.insert(std::complex<T>(-sinh_u), std::complex<T>(-sinh_v));
                }
            }
        };

        template <typename T, std::size_t MaxSize>
        class LowPass : public AbstractDesigner<T, LowPass, MaxSize> {
            friend class AbstractDesigner<T, LowPassk, MaxSize>;
            void design(std::size_t order, T sample_rate, T cuttoff_frequency, double ripple_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowPassAnalogDesigner::design(analog_, order, ripple_db);
                LowPassTransformer{normalized_frequency}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class HighPass : public AbstractDesigner<T, HighPass, MaxSize> {
            friend class AbstractDesigner<T, HighPass, MaxSize>;
            void design(std::size_t order, T sample_rate, T cuttoff_frequency, double ripple_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowPassAnalogDesigner::design(analog_, order, ripple_db);
                HighPassTransformer{normalized_frequency}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandPass : public AbstractDesigner<T, BandPass, MaxSize, 2 * MaxSize> {
            friend class AbstractDesigner<T, BandPass, MaxSize>;
            void design(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency, double ripple_db) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowPassAnalogDesigner::design(analog_, order, ripple_db);
                BandPassTransformer{normalized_center, normalized_bandwidth}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandStopPass : public AbstractDesigner<T, BandStopPass, MaxSize, 2 * MaxSize> {
            friend class AbstractDesigner<T, BandStopPass, MaxSize>;
            void design(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency, double ripple_db) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowPassAnalogDesigner::design(analog_, order, ripple_db);
                BandStopTransformer{normalized_center, normalized_bandwidth}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class LowShelfPass : public AbstractDesigner<T, LowShelfPass, MaxSize> {
            friend class AbstractDesigner<T, LowShelfPass, MaxSize>;
            void design(std::size_t order, T sample_rate, T cuttoff_frequency, T gain_db, double ripple_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowShelfAnalogDesigner::design(analog_, order, gain_db, ripple_db);
                HighPassTransformer{normalized_frequency}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class HighShelfPass : public AbstractDesigner<T, HighShelfPass, MaxSize> {
            friend class AbstractDesigner<T, HighShelfPass, MaxSize>;
            void design(std::size_t order, T sample_rate, T cuttoff_frequency, T gain_db, double ripple_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowShelfAnalogDesigner::design(analog_, order, gain_db, ripple_db);
                HighPassTransformer{normalized_frequency}(digital_, analog_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandShelfPass : public AbstractDesigner<T, BandShelfPass, MaxSize, 2 * MaxSize> {
            friend class AbstractDesigner<T, BandShelfPass, MaxSize, 2 * MaxSize>;
            void design(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency, T gain_db,
                        double ripple_db) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowShelfAnalogDesigner::design(analog_, order, gain_db, ripple_db);
                BandPassTransformer{normalized_center, normalized_bandwidth}(digital_, analog_);

                // HACK!
                digital_.setNormalW(normalized_center < 0.25 ? constants<T>::pi : 0);
                digital_.setNormalGain(1);
            }
        };
    } // namespace


    template <typename T, FilterType Type, std::size_t MaxOrder>
    struct ChebyshevIDesigner {};

    template <typename T, std::size_t MaxOrder>
    struct ChebyshevIDesigner<T, FilterType::LowPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return LowPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ChebyshevIDesigner<T, FilterType::HighPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return HighPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ChebyshevIDesigner<T, FilterType::BandPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return BandPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ChebyshevIDesigner<T, FilterType::BandStop, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return BandStopPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ChebyshevIDesigner<T, FilterType::LowShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return LowShelfPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ChebyshevIIDesigner<T, FilterType::HighShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return HighShelfPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct ChebyshevIDesigner<T, FilterType::BandShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg) {
            return BandShelfPass<T, MaxOrder>{}(std::forward(arg...));
        }
    };

}}} // namespace easy::dsp::filter::chebyshevI

#endif // EASYDSP_CHEBYSHEV_I_HPP
