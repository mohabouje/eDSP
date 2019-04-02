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
 * File: constant.hpp
 * Date: 08/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_CONSTANT_HPP
#define EDSP_CONSTANT_HPP

#include <limits>

namespace edsp { inline namespace math {
    template <typename T>
    struct constants {
        static constexpr const T half                = static_cast<T>(5.000000000000000000000000000000000000e-01);
        static constexpr const T third               = static_cast<T>(3.333333333333333333333333333333333333e-01);
        static constexpr const T twothirds           = static_cast<T>(6.666666666666666666666666666666666666e-01);
        static constexpr const T two_thirds          = static_cast<T>(6.666666666666666666666666666666666666e-01);
        static constexpr const T sixth               = static_cast<T>(1.66666666666666666666666666666666666666666e-01);
        static constexpr const T three_quarters      = static_cast<T>(7.500000000000000000000000000000000000e-01);
        static constexpr const T root_two            = static_cast<T>(1.414213562373095048801688724209698078e+00);
        static constexpr const T root_three          = static_cast<T>(1.732050807568877293527446341505872366e+00);
        static constexpr const T half_root_two       = static_cast<T>(7.071067811865475244008443621048490392e-01);
        static constexpr const T ln_two              = static_cast<T>(6.931471805599453094172321214581765680e-01);
        static constexpr const T ln_ln_two           = static_cast<T>(-3.665129205816643270124391582326694694e-01);
        static constexpr const T root_ln_four        = static_cast<T>(1.177410022515474691011569326459699637e+00);
        static constexpr const T one_div_root_two    = static_cast<T>(7.071067811865475244008443621048490392e-01);
        static constexpr const T pi                  = static_cast<T>(3.141592653589793238462643383279502884e+00);
        static constexpr const T half_pi             = static_cast<T>(1.570796326794896619231321691639751442e+00);
        static constexpr const T third_pi            = static_cast<T>(1.047197551196597746154214461093167628e+00);
        static constexpr const T sixth_pi            = static_cast<T>(5.235987755982988730771072305465838140e-01);
        static constexpr const T two_pi              = static_cast<T>(6.283185307179586476925286766559005768e+00);
        static constexpr const T two_thirds_pi       = static_cast<T>(2.094395102393195492308428922186335256e+00);
        static constexpr const T three_quarters_pi   = static_cast<T>(2.356194490192344928846982537459627163e+00);
        static constexpr const T four_thirds_pi      = static_cast<T>(4.188790204786390984616857844372670512e+00);
        static constexpr const T one_div_two_pi      = static_cast<T>(1.591549430918953357688837633725143620e-01);
        static constexpr const T one_div_root_two_pi = static_cast<T>(3.989422804014326779399460599343818684e-01);
        static constexpr const T root_pi             = static_cast<T>(1.772453850905516027298167483341145182e+00);
        static constexpr const T root_half_pi        = static_cast<T>(1.253314137315500251207882642405522626e+00);
        static constexpr const T root_two_pi         = static_cast<T>(2.506628274631000502415765284811045253e+00);
        static constexpr const T log_root_two_pi     = static_cast<T>(9.189385332046727417803297364056176398e-01);
        static constexpr const T one_div_root_pi     = static_cast<T>(5.641895835477562869480794515607725858e-01);
        static constexpr const T root_one_div_pi     = static_cast<T>(5.641895835477562869480794515607725858e-01);
        static constexpr const T pi_minus_three      = static_cast<T>(1.415926535897932384626433832795028841e-01);
        static constexpr const T four_minus_pi       = static_cast<T>(8.584073464102067615373566167204971158e-01);
        static constexpr const T pi_pow_e            = static_cast<T>(2.245915771836104547342715220454373502e+01);
        static constexpr const T pi_sqr              = static_cast<T>(9.869604401089358618834490999876151135e+00);
        static constexpr const T pi_sqr_div_six      = static_cast<T>(1.644934066848226436472415166646025189e+00);
        static constexpr const T pi_cubed            = static_cast<T>(3.100627668029982017547631506710139520e+01);
        static constexpr const T cbrt_pi             = static_cast<T>(1.464591887561523263020142527263790391e+00);
        static constexpr const T one_div_cbrt_pi     = static_cast<T>(6.827840632552956814670208331581645981e-01);
        static constexpr const T e                   = static_cast<T>(2.718281828459045235360287471352662497e+00);
        static constexpr const T exp_minus_half      = static_cast<T>(6.065306597126334236037995349911804534e-01);
        static constexpr const T e_pow_pi            = static_cast<T>(2.314069263277926900572908636794854738e+01);
        static constexpr const T root_e              = static_cast<T>(1.648721270700128146848650787814163571e+00);
        static constexpr const T log10_e             = static_cast<T>(4.342944819032518276511289189166050822e-01);
        static constexpr const T one_div_log10_e     = static_cast<T>(2.302585092994045684017991454684364207e+00);
        static constexpr const T ln_ten              = static_cast<T>(2.302585092994045684017991454684364207e+00);
        static constexpr const T degree              = static_cast<T>(1.745329251994329576923690768488612713e-02);
        static constexpr const T radian              = static_cast<T>(5.729577951308232087679815481410517033e+01);
        static constexpr const T sin_one             = static_cast<T>(8.414709848078965066525023216302989996e-01);
        static constexpr const T cos_one             = static_cast<T>(5.403023058681397174009366074429766037e-01);
        static constexpr const T sinh_one            = static_cast<T>(1.175201193643801456882381850595600815e+00);
        static constexpr const T cosh_one            = static_cast<T>(1.543080634815243778477905620757061682e+00);
        static constexpr const T phi                 = static_cast<T>(1.618033988749894848204586834365638117e+00);
        static constexpr const T ln_phi              = static_cast<T>(4.812118250596034474977589134243684231e-01);
        static constexpr const T one_div_ln_phi      = static_cast<T>(2.078086921235027537601322606117795767e+00);
        static constexpr const T euler               = static_cast<T>(5.772156649015328606065120900824024310e-01);
        static constexpr const T one_div_euler       = static_cast<T>(1.732454714600633473583025315860829681e+00);
        static constexpr const T euler_sqr           = static_cast<T>(3.331779238077186743183761363552442266e-01);
        static constexpr const T zeta_two            = static_cast<T>(1.644934066848226436472415166646025189e+00);
        static constexpr const T zeta_three          = static_cast<T>(1.202056903159594285399738161511449990e+00);
        static constexpr const T catalan             = static_cast<T>(9.159655941772190150546035149323841107e-01);
        static constexpr const T glaisher            = static_cast<T>(1.282427129100622636875342568869791727e+00);
        static constexpr const T khinchin            = static_cast<T>(2.685452001065306445309714835481795693e+00);
        static constexpr const T extreme_value_skewness   = static_cast<T>(1.139547099404648657492793019389846112e+00);
        static constexpr const T rayleigh_skewness        = static_cast<T>(6.311106578189371381918993515442277798e-01);
        static constexpr const T rayleigh_kurtosis        = static_cast<T>(3.245089300687638062848660410619754415e+00);
        static constexpr const T rayleigh_kurtosis_excess = static_cast<T>(2.450893006876380628486604106197544154e-01);
        static constexpr const T two_div_pi               = static_cast<T>(6.366197723675813430755350534900574481e-01);
        static constexpr const T root_two_div_pi          = static_cast<T>(7.978845608028653558798921198687637369e-01);
    };
}} // namespace edsp::math

#endif // EDSP_CONSTANT_HPP
