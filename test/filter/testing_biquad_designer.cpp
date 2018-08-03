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
 * Filename: testing_biquad_designer.cpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */

#include <easy/dsp/filter/biquad/designer/rbj_designer.hpp>
#include <catch/catch.hpp>

using namespace easy;
using namespace easy::dsp::filter;

SCENARIO("Testing Biquad Designer", "[RBJFilterDesigner]") {
    WHEN("Creating a High Pass filter") {
        constexpr float fs               = 24000;
        constexpr float fc               = 100;
        constexpr float Q                = 0.7f;
        constexpr float G                = 0;
        constexpr std::array<float, 3> a = {{1, -1.96297974726857f, 0.963652641985662f}};
        constexpr std::array<float, 3> b = {{0.981658097313558f, -1.96331619462712f, 0.981658097313558f}};
        const auto biquad                = RBJFilterDesigner<float, BiquadType::HighPass>{}(fc, fs, Q, G);
        THEN("The coefficient should be the same") {
            REQUIRE(biquad.a0() == Approx(a[0]).margin(0.05));
            REQUIRE(biquad.a1() == Approx(a[1]).margin(0.05));
            REQUIRE(biquad.a2() == Approx(a[2]).margin(0.05));
            REQUIRE(biquad.b0() == Approx(b[0]).margin(0.05));
            REQUIRE(biquad.b1() == Approx(b[1]).margin(0.05));
            REQUIRE(biquad.b2() == Approx(b[2]).margin(0.05));
        }
    }

    WHEN("Creating a Band Pass with Skirt Gain") {
        constexpr float fs = 24000;
        constexpr float fc = 100;
        constexpr float Q  = 0.7f;
        constexpr float G  = 0;

        std::array<float, 3> a{};
        std::array<float, 3> b{};
        b[0] = static_cast<float>(0.0128506084259693);
        b[1] = 0;
        b[2] = static_cast<float>(-0.0128506084259693);
        a[0] = 1;
        a[1] = static_cast<float>(-1.96297974726857);
        a[2] = static_cast<float>(0.963652641985662);

        const auto biquad = RBJFilterDesigner<float, BiquadType::BandPassSkirtGain>{}(fc, fs, Q, G);
        THEN("The coefficient should be the same") {
            REQUIRE(biquad.a0() == Approx(a[0]).margin(0.05));
            REQUIRE(biquad.a1() == Approx(a[1]).margin(0.05));
            REQUIRE(biquad.a2() == Approx(a[2]).margin(0.05));
            REQUIRE(biquad.b0() == Approx(b[0]).margin(0.05));
            REQUIRE(biquad.b1() == Approx(b[1]).margin(0.05));
            REQUIRE(biquad.b2() == Approx(b[2]).margin(0.05));
        }
    }

    WHEN("Creating a Band Pass with Peak Gain") {
        constexpr float fs = 24000;
        constexpr float fc = 100;
        constexpr float Q  = 0.7f;
        constexpr float G  = 0;

        std::array<float, 3> a{};
        std::array<float, 3> b{};

        b[0] = static_cast<float>(0.0181736790071691);
        b[1] = 0;
        b[2] = static_cast<float>(-0.0181736790071691);
        a[0] = 1;
        a[1] = static_cast<float>(-1.96297974726857);
        a[2] = static_cast<float>(0.963652641985662);

        const auto biquad = RBJFilterDesigner<float, BiquadType::BandPassSkirtGain>{}(fc, fs, Q, G);
        THEN("The coefficient should be the same") {
            REQUIRE(biquad.a0() == Approx(a[0]).margin(0.05));
            REQUIRE(biquad.a1() == Approx(a[1]).margin(0.05));
            REQUIRE(biquad.a2() == Approx(a[2]).margin(0.05));
            REQUIRE(biquad.b0() == Approx(b[0]).margin(0.05));
            REQUIRE(biquad.b1() == Approx(b[1]).margin(0.05));
            REQUIRE(biquad.b2() == Approx(b[2]).margin(0.05));
        }
    }

    WHEN("Creating a Notch filter") {
        constexpr float fs = 24000;
        constexpr float fc = 100;
        constexpr float Q  = 0.7f;
        constexpr float G  = 0;

        std::array<float, 3> a{};
        std::array<float, 3> b{};

        b[0] = static_cast<float>(0.981826320992831);
        b[1] = static_cast<float>(-1.96297974726857);
        b[2] = static_cast<float>(0.981826320992831);
        a[0] = 1;
        a[1] = static_cast<float>(-1.96297974726857);
        a[2] = static_cast<float>(0.963652641985662);

        const auto biquad = RBJFilterDesigner<float, BiquadType::BandPassSkirtGain>{}(fc, fs, Q, G);
        THEN("The coefficient should be the same") {
            REQUIRE(biquad.a0() == Approx(a[0]).margin(0.05));
            REQUIRE(biquad.a1() == Approx(a[1]).margin(0.05));
            REQUIRE(biquad.a2() == Approx(a[2]).margin(0.05));
            REQUIRE(biquad.b0() == Approx(b[0]).margin(0.05));
            REQUIRE(biquad.b1() == Approx(b[1]).margin(0.05));
            REQUIRE(biquad.b2() == Approx(b[2]).margin(0.05));
        }
    }

    WHEN("Creating a All Pass filter") {
        constexpr float fs = 24000;
        constexpr float fc = 100;
        constexpr float Q  = 0.7f;
        constexpr float G  = 0;

        std::array<float, 3> a{};
        std::array<float, 3> b{};

        b[0] = static_cast<float>(0.963652641985662);
        b[1] = static_cast<float>(-1.96297974726857);
        b[2] = 1;
        a[0] = 1;
        a[1] = static_cast<float>(-1.96297974726857);
        a[2] = static_cast<float>(0.963652641985662);

        const auto biquad = RBJFilterDesigner<float, BiquadType::BandPassSkirtGain>{}(fc, fs, Q, G);
        THEN("The coefficient should be the same") {
            REQUIRE(biquad.a0() == Approx(a[0]).margin(0.05));
            REQUIRE(biquad.a1() == Approx(a[1]).margin(0.05));
            REQUIRE(biquad.a2() == Approx(a[2]).margin(0.05));
            REQUIRE(biquad.b0() == Approx(b[0]).margin(0.05));
            REQUIRE(biquad.b1() == Approx(b[1]).margin(0.05));
            REQUIRE(biquad.b2() == Approx(b[2]).margin(0.05));
        }
    }

    WHEN("Creating a Peaking EQ filter") {
        constexpr float fs = 24000;
        constexpr float fc = 100;
        constexpr float Q  = 0.7f;
        constexpr float G  = 14;

        std::array<float, 3> a{};
        std::array<float, 3> b{};

        b[0] = static_cast<float>(1.03322966142232);
        b[1] = static_cast<float>(-1.98275466415748);
        b[2] = static_cast<float>(0.950204676145267);
        a[0] = 1;
        a[1] = static_cast<float>(-1.98275466415748);
        a[2] = static_cast<float>(0.983434337567586);

        const auto biquad = RBJFilterDesigner<float, BiquadType::BandPassSkirtGain>{}(fc, fs, Q, G);
        THEN("The coefficient should be the same") {
            REQUIRE(biquad.a0() == Approx(a[0]).margin(0.05));
            REQUIRE(biquad.a1() == Approx(a[1]).margin(0.05));
            REQUIRE(biquad.a2() == Approx(a[2]).margin(0.05));
            REQUIRE(biquad.b0() == Approx(b[0]).margin(0.05));
            REQUIRE(biquad.b1() == Approx(b[1]).margin(0.05));
            REQUIRE(biquad.b2() == Approx(b[2]).margin(0.05));
        }
    }

    WHEN("Creating a Low Shelf filter") {
        constexpr float fs = 24000;
        constexpr float fc = 100;
        constexpr float Q  = 0.7f;
        constexpr float G  = 14;

        std::array<float, 3> a{};
        std::array<float, 3> b{};

        b[0] = static_cast<float>(1.0155934280269);
        b[1] = static_cast<float>(-1.97440406495045);
        b[2] = static_cast<float>(0.960326149525744);
        a[0] = 1;
        a[1] = static_cast<float>(-1.9750106289924);
        a[2] = static_cast<float>(0.975313013510697);

        const auto biquad = RBJFilterDesigner<float, BiquadType::BandPassSkirtGain>{}(fc, fs, Q, G);
        THEN("The coefficient should be the same") {
            REQUIRE(biquad.a0() == Approx(a[0]).margin(0.05));
            REQUIRE(biquad.a1() == Approx(a[1]).margin(0.05));
            REQUIRE(biquad.a2() == Approx(a[2]).margin(0.05));
            REQUIRE(biquad.b0() == Approx(b[0]).margin(0.05));
            REQUIRE(biquad.b1() == Approx(b[1]).margin(0.05));
            REQUIRE(biquad.b2() == Approx(b[2]).margin(0.05));
        }
    }

    WHEN("Creating a High Shelf filter") {
        constexpr float fs = 24000;
        constexpr float fc = 100;
        constexpr float Q  = 0.7f;
        constexpr float G  = 14;

        std::array<float, 3> a{};
        std::array<float, 3> b{};

        b[0] = static_cast<float>(4.9349200161819);
        b[1] = static_cast<float>(-9.74651948518657);
        b[2] = static_cast<float>(4.81309171241662);
        a[0] = 1;
        a[1] = static_cast<float>(-1.94408905223652);
        a[2] = static_cast<float>(0.945581295648469);

        const auto biquad = RBJFilterDesigner<float, BiquadType::BandPassSkirtGain>{}(fc, fs, Q, G);
        THEN("The coefficient should be the same") {
            REQUIRE(biquad.a0() == Approx(a[0]).margin(0.05));
            REQUIRE(biquad.a1() == Approx(a[1]).margin(0.05));
            REQUIRE(biquad.a2() == Approx(a[2]).margin(0.05));
            REQUIRE(biquad.b0() == Approx(b[0]).margin(0.05));
            REQUIRE(biquad.b1() == Approx(b[1]).margin(0.05));
            REQUIRE(biquad.b2() == Approx(b[2]).margin(0.05));
        }
    }
}
