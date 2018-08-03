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
 * Filename: fwht_impl.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EASYDSP_FWHT_IMPL_HPP
#define EASYDSP_FWHT_IMPL_HPP

#include <algorithm>
#include <cmath>

namespace easy { namespace dsp {
    template <typename Integer,
              typename Type>
    void fwht_plan(Type data, Integer N) {
      const  auto log2 = std::log2(N) - 1;
      for (Integer i = 0; i < log2; ++i) {
        for (Integer j = 0; j < (1 << log2); j += 1 << (i+1)) {
           for (Integer k = 0; k < (1<<i); ++k) {
               std::swap(data [j + k], data [j + k + (1<<i)]);
           }
        }
      }
    }
}}

#endif // EASYDSP_FWHT_IMPL_HPP
