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
 * Filename: testing_filter_generator.cpp
 * Author: Mohammed Boujemaoui
 * Date: 31/8/2018
 */

#include <easy/dsp/filter/filter_types.hpp>
#include <easy/dsp/filter/filter.hpp>
#include <catch/catch.hpp>

using namespace easy::dsp;
using namespace easy::dsp::filter;

SCENARIO("Generating random filters", "[make_filter]") {
    GIVEN("A low pass filter to generate") {
        constexpr auto sample_rate = 44100.0;
        constexpr auto frequency   = 600.0;

        WHEN("We want to generate a RBJ filter") {
            constexpr auto Q = 0.71;
            const auto designed_filter =
                make_filter<double, DesignerType::RBJ, FilterType::LowPass, 100>(frequency, sample_rate, Q);
        }

        WHEN("We want to generate a Zoelzer filter") {
            constexpr auto Q = 0.71;
            const auto designed_filter =
                make_filter<double, DesignerType::Zoelzer, FilterType::LowPass, 100>(frequency, sample_rate, Q);
        }

        WHEN("We want to generate a Butterworth") {
            constexpr std::size_t order = 8;
            const auto designed_filter =
                make_filter<double, DesignerType::Butterworth, FilterType::LowPass, 100>(order, sample_rate, frequency);
            constexpr auto i = 10;
        }

        WHEN("We want to generate a Butterworth") {
            constexpr std::size_t order = 10;
            constexpr auto ripple       = 5.;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevI, FilterType::LowPass, 100>(
                order, sample_rate, frequency, ripple);
        }

        WHEN("We want to generate a Butterworth") {
            constexpr std::size_t order = 10;
            constexpr auto ripple       = 5.;
            const auto designed_filter  = make_filter<double, DesignerType::ChebyshevII, FilterType::LowPass, 100>(
                order, sample_rate, frequency, ripple);
        }
    }
}
