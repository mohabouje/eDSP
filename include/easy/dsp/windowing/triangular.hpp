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
 * Filename: triangular.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_TRIANGULAR_HPP
#define EASYDSP_TRIANGULAR_HPP

#include "window_impl.hpp"
#include <cmath>

namespace easy { namespace dsp { namespace windowing {

    template <typename T, typename Allocator = std::allocator<T>>
    class Triangular : public Window<Triangular<T, Allocator>, T, Allocator> {
        friend class Window<Triangular<T, Allocator>, T, Allocator>;
        using parent = Window<Triangular<T, Allocator>, T, Allocator>;
    public:
        using value_type = typename parent::value_type;
        using size_type  = typename parent::size_type;
        inline explicit Triangular(size_type size);

    private:
        inline void initialize();
    };

    template <typename T, typename Allocator>
    inline Triangular<T, Allocator>::Triangular(Triangular::size_type size) : parent(size) {}

    template <typename T, typename Allocator>
    inline void Triangular<T, Allocator>::initialize() {
        const size_type sz   = parent::size();
        const value_type rem = sz + std::remainder(sz, 2);
        value_type initial   = -(sz - 1);
        for (size_type i = 0; i < sz; ++i) {
            parent::data_[i] = 1 - std::abs(initial / rem);
            initial += 2;
        }
    }

    template <typename OutputIterator, typename Integer>
    inline void triang(Integer size, OutputIterator out) {
        using value_type = typename std::iterator_traits<OutputIterator>::value_type;
        using size_type = typename Triangular<value_type>::size_type;
        Triangular<value_type> window(static_cast<size_type>(size));
        std::copy(std::cbegin(window), std::cend(window), out);
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_TRIANGULAR_HPP
