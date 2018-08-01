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
 * Filename: bohman.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/8/2018
 */
#ifndef EASYDSP_BOHMAN_HPP
#define EASYDSP_BOHMAN_HPP

#include "window_impl.hpp"
#include <cmath>

namespace easy { namespace dsp { namespace windowing {

    template <typename T, typename Allocator = std::allocator<T>>
    class Bohman : public Window<Bohman<T, Allocator>, T, Allocator> {
        friend class Window<Bohman<T, Allocator>, T, Allocator>;
        using parent = Window<Bohman<T, Allocator>, T, Allocator>;

    public:
        using value_type = typename parent::value_type;
        using size_type  = typename parent::size_type;
        inline explicit Bohman(size_type size);

    private:
        inline void initialize();
    };

    template <typename T, typename Allocator>
    inline Bohman<T, Allocator>::Bohman(Bohman::size_type size) : parent(size) {}

    template <typename T, typename Allocator>
    inline void Bohman<T, Allocator>::initialize() {
        const auto sz = parent::size();
        const auto N = static_cast<value_type>(sz) - 1;
        value_type initial = -N / 2;
        for (size_type i = 0; i < sz; ++i, ++initial) {
            const auto tmp = std::abs(initial) / N;
            const auto phase = constants<value_type>::two_pi * tmp;
            parent::data_[i] = (1 - 2 * tmp) * std::cos(phase) + constants<value_type>::inv_pi * std::sin(phase);
        }
        parent::data_[0] = 0;
        parent::data_[N] = 0;
    }

    template <typename OutputIterator, typename Integer>
    inline void bohman(Integer size, OutputIterator out) {
        using value_type = typename std::iterator_traits<OutputIterator>::value_type;
        using size_type  = typename Bohman<value_type>::size_type;
        Bohman<value_type> window(static_cast<size_type>(size));
        std::copy(std::cbegin(window), std::cend(window), out);
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_BOHMAN_HPP
