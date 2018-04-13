/*
 * eDSP, A cross-platform DSP framework written in C++.
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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef EDSP_CONSTANTS_H
#define EDSP_CONSTANTS_H

#include "config.h"
#include <limits>
#include <boost/math/constants/constants.hpp>

EDSP_BEGIN_NAMESPACE
    template <typename T>
    struct constants {
        constexpr static T root_two = boost::math::constants::root_two<T>;
        constexpr static T root_three = boost::math::constants::root_three<T>;
        constexpr static T half_root_two = boost::math::constants::half_root_two<T>;
        constexpr static T pi = boost::math::constants::pi<T>;
        constexpr static T half_pi = boost::math::constants::half_pi<T>;
        constexpr static T third_pi = boost::math::constants::third_pi<T>;
        constexpr static T sixth_pi = boost::math::constants::sixth_pi<T>;
        constexpr static T two_pi = boost::math::constants::two_pi<T>;
        constexpr static T root_pi = boost::math::constants::root_pi<T>;
        constexpr static T root_half_pi = boost::math::constants::root_half_pi<T>;
        constexpr static T root_two_pi = boost::math::constants::root_two_pi<T>;
        constexpr static T root_two_div_pi = boost::math::constants::root_two_div_pi<T>;
        constexpr static T one_div_two_pi = boost::math::constants::one_div_two_pi<T>;
        constexpr static T one_div_pi = 2 * boost::math::constants::one_div_two_pi<T>;
        constexpr static T one_div_root_pi = boost::math::constants::one_div_root_pi<T>;
        constexpr static T one_div_root_two_pi = boost::math::constants::one_div_root_two_pi<T>;
        constexpr static T two_div_pi = boost::math::constants::two_div_pi<T>;
        constexpr static T pi_sqr = boost::math::constants::pi_sqr<T>;
        constexpr static T pi_cubed = boost::math::constants::pi_cubed<T>;
        constexpr static T e = boost::math::constants::e<T>;
        constexpr static T root_e = boost::math::constants::root_e<T>;
        constexpr static T log10_e = boost::math::constants::log10_e<T>;
    };
EDSP_END_NAMESPACE


#endif //EDSP_CONSTANTS_H
