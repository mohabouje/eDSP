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
 * Filename: blackman.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_BLACKMAN_HPP
#define EASYDSP_BLACKMAN_HPP

#include "window_impl.hpp"
#include <easy/dsp/math/math.hpp>
#include <cmath>

namespace easy { namespace dsp { namespace windowing {

    template <typename T, typename Allocator = std::allocator<T>>
    class Blackman : public Window<Blackman<T, Allocator>, T, Allocator> {
        friend class Window<Blackman<T, Allocator>, T, Allocator>;
        using parent = Window<Blackman<T, Allocator>, T, Allocator>;

    public:
        using value_type = typename parent::value_type;
        using size_type  = typename parent::size_type;
        inline explicit Blackman(size_type size);

    private:
        inline void initialize();
    };

    template <typename T, typename Allocator>
    inline Blackman<T, Allocator>::Blackman(Blackman::size_type size) : parent(size) {}

    template <typename T, typename Allocator>
    inline void Blackman<T, Allocator>::initialize() {
        constexpr auto a0 = static_cast<value_type>(0.42);
        constexpr auto a1 = static_cast<value_type>(0.50);
        constexpr auto a2 = static_cast<value_type>(0.08);
        const auto size   = parent::size();
        const auto middle = math::is_even(size) ? size / 2 : (size + 1) / 2;
        const auto factor = constants<value_type>::two_pi / static_cast<value_type>(size - 1);

        for (size_type i = 0; i < middle; ++i) {
            const value_type tmp = factor * i;
            parent::data_[i]     = a0 - a1 * std::cos(tmp) + a2 * std::cos(2 * tmp);
        }

        for (size_type i = middle; i < size; ++i) {
            parent::data_[i] = parent::data_[size - i - 1];
        }
    }

    template <typename OutputIterator, typename Integer>
    inline void blackman(Integer size, OutputIterator out) {
        using value_type = typename std::iterator_traits<OutputIterator>::value_type;
        using size_type  = typename Blackman<value_type>::size_type;
        Blackman<value_type> window(static_cast<size_type>(size));
        std::copy(std::cbegin(window), std::cend(window), out);
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_BLACKMAN_HPP
