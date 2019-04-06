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
 * File: chebyshev_ii.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EDSP_CHEBYSHEV_II_HPP
#define EDSP_CHEBYSHEV_II_HPP

#include <edsp/converter/db2mag.hpp>
#include <edsp/meta/expects.hpp>
#include <edsp/math/complex.hpp>
#include <edsp/math/constant.hpp>
#include <edsp/filter/internal/bilinear/bandpass_transformer.hpp>
#include <edsp/filter/internal/bilinear/bandstop_transformer.hpp>
#include <edsp/filter/internal/bilinear/lowpass_transformer.hpp>
#include <edsp/filter/internal/bilinear/highpass_transformer.hpp>
#include <edsp/filter/internal/abstract_designer.hpp>

namespace edsp { namespace filter {

    namespace chebyshevII {
        struct LowPassAnalogDesigner {
            template <typename T, std::size_t MaxSize>
            void design(LayoutBase<T, MaxSize>& analog, std::size_t num_poles, T stopband_db) const {
                meta::expects(num_poles <= MaxSize, "Index out of bounds");
                analog.set_w(0);
                analog.set_gain(1);
                analog.reset();

                const auto eps     = std::sqrt(math::inv(std::expm1(stopband_db * 0.1 * constants<T>::ln_ten)));
                const auto v0      = std::asinh(math::inv(eps)) / static_cast<T>(num_poles);
                const auto sinh_v0 = -std::sinh(v0);
                const auto cosh_v0 = std::cosh(v0);
                const auto fn      = constants<T>::pi / static_cast<T>(2 * num_poles);
                for (std::int64_t k = 1, i = static_cast<std::int64_t>(num_poles / 2); --i >= 0; k += 2) {
                    const auto a  = sinh_v0 * std::cos((k - static_cast<std::int32_t>(num_poles)) * fn);
                    const auto b  = cosh_v0 * std::sin((k - static_cast<std::int32_t>(num_poles)) * fn);
                    const auto d2 = math::square(a) + math::square(b);
                    const auto im = math::inv(std::cos(static_cast<T>(k) * fn));
                    analog.insert_conjugate(std::complex<T>(a / d2, b / d2), std::complex<T>(0, im));
                }

                if (math::is_odd(num_poles)) {
                    analog.insert(std::complex<T>(math::inv(sinh_v0), 0), math::infinity<T>());
                }
            }
        };

        struct LowShelfAnalogDesigner {
            template <typename T, std::size_t MaxSize>
            void design(LayoutBase<T, MaxSize>& analog, std::size_t num_poles, T gain_db, T stopband_db) const {
                meta::expects(num_poles <= MaxSize, "Index out of bounds");

                analog.set_w(constants<T>::pi);
                analog.set_gain(1);
                analog.reset();

                gain_db = -gain_db;
                if (stopband_db >= std::fabs(gain_db))
                    stopband_db = std::fabs(gain_db);
                if (gain_db < 0)
                    stopband_db = -stopband_db;

                const auto G  = converter::db2mag(gain_db);
                const auto Gb = converter::db2mag(gain_db - stopband_db);
                const auto G0 = 1;
                const auto g0 = std::pow(G0, math::inv(static_cast<T>(num_poles)));
                const auto eps =
                    (Gb != G0) ? std::sqrt((math::square(G) - math::square(Gb)) / (math::square(Gb) - math::square(G0)))
                               : G - 1;
                const auto exponent = std::sqrt(1 + math::inv(math::square(eps)));
                const auto b        = std::pow(G / eps + Gb * exponent, math::inv(static_cast<T>(num_poles)));
                const auto v      = std::log(std::pow(math::inv(eps) + exponent, math::inv(static_cast<T>(num_poles))));
                const auto u      = std::log(b / g0);
                const auto sinh_u = std::sinh(u);
                const auto sinh_v = std::sinh(v);
                const auto cosh_u = std::cosh(u);
                const auto cosh_v = std::cosh(v);
                const auto size   = static_cast<T>(2 * num_poles);
                for (std::int32_t i = 1, pairs = num_poles / 2; i <= pairs; ++i) {
                    const auto a  = constants<T>::pi * static_cast<T>(2 * i - 1) / size;
                    const auto sn = std::sin(a);
                    const auto cs = std::cos(a);
                    analog.insert_conjugate(std::complex<T>(-sn * sinh_u, cs * cosh_u),
                                            std::complex<T>(-sn * sinh_v, cs * cosh_v));
                }

                if (math::is_odd(num_poles)) {
                    analog.insert(std::complex<T>(-sinh_u, 0), std::complex<T>(-sinh_v, 0));
                }
            }
        };

        template <typename T, std::size_t MaxSize>
        class LowPass : public AbstractDesigner<T, LowPass<T, MaxSize>, MaxSize> {
            friend struct AbstractDesigner<T, LowPass, MaxSize>;
            void operator()(std::size_t order, T sample_rate, T cuttoff_frequency, T stopband_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowPassAnalogDesigner{}.design(this->analog_, order, stopband_db);
                LowPassTransformer<T>{normalized_frequency}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class HighPass : public AbstractDesigner<T, HighPass<T, MaxSize>, MaxSize> {
            friend struct AbstractDesigner<T, HighPass, MaxSize>;
            void operator()(std::size_t order, T sample_rate, T cuttoff_frequency, T stopband_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowPassAnalogDesigner{}.design(this->analog_, order, stopband_db);
                HighPassTransformer<T>{normalized_frequency}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandPass : public AbstractDesigner<T, BandPass<T, MaxSize>, MaxSize, 2 * MaxSize> {
            friend struct AbstractDesigner<T, BandPass, MaxSize, 2 * MaxSize>;
            void operator()(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency,
                            T stopband_db) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowPassAnalogDesigner{}.design(this->analog_, order, stopband_db);
                BandPassTransformer<T>{normalized_center, normalized_bandwidth}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandStopPass : public AbstractDesigner<T, BandStopPass<T, MaxSize>, MaxSize, 2 * MaxSize> {
            friend struct AbstractDesigner<T, BandStopPass, MaxSize, 2 * MaxSize>;
            void operator()(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency,
                            T stopband_db) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowPassAnalogDesigner{}.design(this->analog_, order, stopband_db);
                BandStopTransformer<T>{normalized_center, normalized_bandwidth}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class LowShelfPass : public AbstractDesigner<T, LowShelfPass<T, MaxSize>, MaxSize> {
            friend struct AbstractDesigner<T, LowShelfPass, MaxSize>;
            void operator()(std::size_t order, T sample_rate, T cuttoff_frequency, T gain_db, T stopband_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowShelfAnalogDesigner{}.design(this->analog_, order, gain_db, stopband_db);
                LowPassTransformer<T>{normalized_frequency}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class HighShelfPass : public AbstractDesigner<T, HighShelfPass<T, MaxSize>, MaxSize> {
            friend struct AbstractDesigner<T, HighShelfPass, MaxSize>;
            void operator()(std::size_t order, T sample_rate, T cuttoff_frequency, T gain_db, T stopband_db) {
                const auto normalized_frequency = cuttoff_frequency / sample_rate;
                LowShelfAnalogDesigner{}.design(this->analog_, order, gain_db, stopband_db);
                HighPassTransformer<T>{normalized_frequency}(this->analog_, this->digital_);
            }
        };

        template <typename T, std::size_t MaxSize>
        class BandShelfPass : public AbstractDesigner<T, BandShelfPass<T, MaxSize>, MaxSize, 2 * MaxSize> {
            friend struct AbstractDesigner<T, BandShelfPass, MaxSize, 2 * MaxSize>;
            void operator()(std::size_t order, T sample_rate, T center_frequency, T bandwidth_frequency, T gain_db,
                            T stopband_db) {
                const auto normalized_center    = center_frequency / sample_rate;
                const auto normalized_bandwidth = bandwidth_frequency / sample_rate;
                LowShelfAnalogDesigner{}.design(this->analog_, order, gain_db, stopband_db);
                BandPassTransformer<T>{normalized_center, normalized_bandwidth}(this->analog_, this->digital_);

                // HACK!
                this->digital_.set_w(normalized_center < 0.25 ? constants<T>::pi : 0);
                this->digital_.set_gain(1);
            }
        };

    } // namespace chebyshevII

    template <typename T, filter_type Type, std::size_t MaxOrder>
    struct chebyshevII_designer {};

    template <typename T, std::size_t MaxOrder>
    struct chebyshevII_designer<T, filter_type::LowPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(chebyshevII::LowPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return chebyshevII::LowPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct chebyshevII_designer<T, filter_type::HighPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(chebyshevII::HighPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return chebyshevII::HighPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct chebyshevII_designer<T, filter_type::BandPass, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(chebyshevII::BandPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return chebyshevII::BandPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct chebyshevII_designer<T, filter_type::BandStop, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(chebyshevII::BandStopPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return chebyshevII::BandStopPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct chebyshevII_designer<T, filter_type::LowShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(chebyshevII::LowShelfPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return chebyshevII::LowShelfPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct chebyshevII_designer<T, filter_type::HighShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(chebyshevII::HighShelfPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return chebyshevII::HighShelfPass<T, MaxOrder>{}.design(arg...);
        }
    };

    template <typename T, std::size_t MaxOrder>
    struct chebyshevII_designer<T, filter_type::BandShelf, MaxOrder> {
        template <typename... Arg>
        constexpr auto operator()(Arg... arg)
            -> decltype(chebyshevII::BandShelfPass<T, MaxOrder>{}.design(std::declval<Arg&&>()...)) {
            return chebyshevII::BandShelfPass<T, MaxOrder>{}.design(arg...);
        }
    };

}} // namespace edsp::filter

#endif // EDSP_CHEBYSHEV_II_HPP
