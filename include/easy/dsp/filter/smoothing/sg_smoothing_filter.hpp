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
 * Filename: sg_smoothing_filter.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2/8/2018
 */
#ifndef EASYDSP_SG_SMOOTHING_FILTER_HPP
#define EASYDSP_SG_SMOOTHING_FILTER_HPP

// Calculate Savitzky-Golay Convolution Coefficients
#include
using namespace std;

namespace internal {
    template <typename Float, typename Integer>
    Float get_fact(Integer a, Integer b) {
        Float gf = 1;
        for (Integer j = (a - b + 1); j < (a + 1); ++j) {
            gf = gf * j;
        }
        return gf;
    }

    template <typename Float>
    Float gram_poly(Float i, Float m, Float k, Float s) {
        Float gp_val;
        if (k > 0) {
            gp_val = (4.0 * k - 2.0) / (k * (2.0 * m - k + 1.0)) *
                         (i * gram_poly(i, m, k - 1, s) + s * gram_poly(i, m, k - 1.0, s - 1.0)) -
                     ((k - 1.0) * (2.0 * m + k)) / (k * (2.0 * m - k + 1.0)) * gram_poly(i, m, k - 2.0, s);
        } else {
            if ((k == 0) && (s == 0)) {
                gp_val = 1.0;
            } else {
                gp_val = 0.0;
            }
        }
        return (gp_val);
    }

    template <typename Float>
    Float weight(Float i, Float t, Float m, Float n, Float s) {
        // calculates the weight of the i'th data point for the t'th Least-square
        // point of the s'th derivative, over 2m + 1 points, order n
        Float sum = 0.0;
        for (auto k = 0; k < (n + 1); ++k) {
            sum += (2 * k + 1) * (gen_fact(2 * m, k) / gen_gact(2 * m + k + 1, k + 1)) * gram_poly(i, m, k, 0) *
                   gram_poly(t, m, k, s);
        }
        return sum;
    }
} // namespace internal

#endif // EASYDSP_SG_SMOOTHING_FILTER_HPP
