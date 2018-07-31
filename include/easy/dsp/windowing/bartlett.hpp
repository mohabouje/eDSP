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
 * Filename: bartlett.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_BARTLETT_HPP
#define EASYDSP_BARTLETT_HPP

#include "window_impl.hpp"
#include <cmath>

namespace easy { namespace dsp { namespace windowing {

    template <typename T, typename Allocator = std::allocator<T>>
    class Bartlett : public Window<Bartlett<T, Allocator>, T, Allocator> {
        friend class Window<Bartlett<T, Allocator>, T, Allocator>;
        using parent = Window<Bartlett<T, Allocator>, T, Allocator>;

    public:
        using value_type = typename parent::value_type;
        using size_type  = typename parent::size_type;
        inline explicit Bartlett(size_type size);

    private:
        inline void initialize();
    };

    template <typename T, typename Allocator>
    inline Bartlett<T, Allocator>::Bartlett(Bartlett::size_type size) : parent(size) {}

    template <typename T, typename Allocator>
    inline void Bartlett<T, Allocator>::initialize() {
        const value_type N = parent::size() - 1;
        value_type half    = 0;
        std::modf(N / static_cast<value_type>(2), &half);
        for (size_type i = 0, sz = parent::size(); i < sz; ++i) {
            parent::data_[i] = ((i <= half) ? 2 * i : (2 - 2 * i)) / N;
        }
    }

    template <typename OutputIterator, typename Integer>
    inline void bartlett(Integer size, OutputIterator out) {
        using value_type = typename std::iterator_traits<OutputIterator>::value_type;
        using size_type  = typename Bartlett<value_type>::size_type;
        Bartlett<value_type> window(static_cast<size_type>(size));
        std::copy(std::cbegin(window), std::cend(window), out);
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_BARTLETT_HPP
