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
 * Filename: hamming.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_HAMMING_HPP
#define EASYDSP_HAMMING_HPP

#include "window.hpp"
#include <cmath>

namespace easy { namespace dsp { namespace windowing {

    template <typename T, typename Allocator = std::allocator<T>>
    class Hamming : public Window<Hamming<T, Allocator>, T, Allocator> {
        using parent = Window<Hamming<T, Allocator>, T, Allocator>;

    public:
        using value_type = typename parent::value_type;
        using size_type  = typename parent::size_type;
        inline explicit Hamming(size_type size);

    private:
        inline void initialize();
    };

    template <typename T, typename Allocator>
    inline Hamming<T, Allocator>::Hamming(Hamming::size_type size) : parent(size) {}

    template <typename T, typename Allocator>
    inline void Hamming<T, Allocator>::initialize() {
        for (size_type i = 0, sz = parent::size(); i < sz; ++i) {
            parent::data_[i] = static_cast<value_type>(0.54 - 0.46 * std::cos(constants<value_type>::two_pi * i / sz));
        }
    }

}}}    // namespace easy::dsp::windowing
#endif // EASYDSP_HAMMING_HPP
