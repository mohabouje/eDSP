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
 * Filename: flat_top.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_FLAT_TOP_HPP
#define EASYDSP_FLAT_TOP_HPP

#include "window.hpp"
#include <cmath>
namespace easy { namespace dsp { namespace windowing {

    template <typename T, typename Allocator = std::allocator<T>>
    class FlatTop : public Window<FlatTop<T, Allocator>, T, Allocator> {
        friend class Window<FlatTop<T, Allocator>, T, Allocator>;
        using parent = Window<FlatTop<T, Allocator>, T, Allocator>;
    public:
        using value_type = typename parent::value_type;
        using size_type  = typename parent::size_type;
        inline explicit FlatTop(size_type size);

    private:
        inline void initialize();
    };

    template <typename T, typename Allocator>
    FlatTop<T, Allocator>::FlatTop(FlatTop::size_type size) : parent(size) {}

    template <typename T, typename Allocator>
    void FlatTop<T, Allocator>::initialize() {
        for (size_type i = 0, sz = parent::size(); i < sz; ++i) {
            const value_type tmp = constants<value_type>::two_pi * i / static_cast<value_type>(sz);
            parent::data_[i] = 1 - 1.9300 * std::cos(tmp) + 1.2900 * std::cos(2 * tmp) - 0.3880 * std::cos(3 * tmp) +
                               0.0322 * std::cos(4 * tmp);
        }
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_FLAT_TOP_HPP
