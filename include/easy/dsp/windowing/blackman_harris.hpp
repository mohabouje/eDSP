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
 * Filename: blackman_harris.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EASYDSP_BLACKMANHARRIS_HARRIS_HPP
#define EASYDSP_BLACKMANHARRIS_HARRIS_HPP

#include "window_impl.hpp"

namespace easy { namespace dsp { namespace windowing {

    template <typename T, typename Allocator = std::allocator<T>>
    class BlackmanHarris : public Window<BlackmanHarris<T, Allocator>, T, Allocator> {
        friend class Window<BlackmanHarris<T, Allocator>, T, Allocator>;
        using parent = Window<BlackmanHarris<T, Allocator>, T, Allocator>;

    public:
        using value_type = typename parent::value_type;
        using size_type  = typename parent::size_type;
        inline explicit BlackmanHarris(size_type size);

    private:
        inline void initialize();
    };

    template <typename T, typename Allocator>
    inline BlackmanHarris<T, Allocator>::BlackmanHarris(BlackmanHarris::size_type size) : parent(size) {}

    template <typename T, typename Allocator>
    inline void BlackmanHarris<T, Allocator>::initialize() {
        constexpr auto a0 = static_cast<value_type>(0.35875);
        constexpr auto a1 = static_cast<value_type>(0.48829);
        constexpr auto a2 = static_cast<value_type>(0.14128);
        constexpr auto a3 = static_cast<value_type>(0.01168);
        for (size_type i = 0, sz = parent::size(); i < sz; ++i) {
            const value_type tmp = constants<value_type>::two_pi * i / static_cast<value_type>(sz);
            parent::data_[i]     = a0 - a1 * std::cos(tmp) + a2 * std::cos(2 * tmp) - a3 * std::cos(3 * tmp);
        }
    }

    template <typename OutputIterator, typename Integer>
    inline void blackmanharris(Integer size, OutputIterator out) {
        using value_type = typename std::iterator_traits<OutputIterator>::value_type;
        using size_type  = typename BlackmanHarris<value_type>::size_type;
        BlackmanHarris<value_type> window(static_cast<size_type>(size));
        std::copy(std::cbegin(window), std::cend(window), out);
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_BLACKMANHARRIS_HARRIS_HPP
