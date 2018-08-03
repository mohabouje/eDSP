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
 * Filename: fht_impl.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EASYDSP_FHT_IMPL_HPP
#define EASYDSP_FHT_IMPL_HPP

#include <easy/meta/data.hpp>
#include <algorithm>

namespace easy { namespace dsp {

    template <typename Integer,
              typename Type,
              typename Allocator = std::allocator<Type>>
    void fwht_plan(Integer n, const Type *src, Type *dst) {
        std::vector<Type> adata(n), bdata(n);
        std::copy(src, src + n, std::begin(adata));
        auto *a = meta::data(adata);
        auto *b = meta::data(bdata);
        for (Integer i = n >> 1; i > 0; i >>= 1) {
            for (Integer j = 0; j < n; j++) {
                s = j / i % 2;
                b[j]= a[(s ? -i : 0) + j]
                        + (s ? -1 : 1) * a[(s ? 0 : i) + j];
            }
            std::swap(a, b);
            tmp = a; a = b; b = tmp;
        }
        std::copy(std::cbegin(a), std::cend(a), dst);
    }
}}

#endif // EASYDSP_FHT_IMPL_HPP
