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
 * Filename: kaiser.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EASYDSP_RCOSTAPER_HPP
#define EASYDSP_RCOSTAPER_HPP

#include "window_impl.hpp"
#include <easy/dsp/math/math.hpp>
#include <boost/math/special_functions/bessel.hpp>

namespace easy { namespace dsp { namespace windowing {

    template <typename T, typename Allocator = std::allocator<T>>
    class Kaiser : public Window<Kaiser<T, Allocator>, T, Allocator> {
        friend class Window<Kaiser<T, Allocator>, T, Allocator>;
        using parent = Window<Kaiser<T, Allocator>, T, Allocator>;

    public:
        using value_type = typename parent::value_type;
        using size_type  = typename parent::size_type;
        inline explicit Kaiser(size_type size, value_type window_taper, value_type franctional_sample_offset);

    private:
        inline void initialize();
        value_type beta_;
        value_type mu_;
    };

    template <typename T, typename Allocator>
    inline Kaiser<T, Allocator>::Kaiser(size_type size, value_type window_taper, value_type fractional_sample_offset) :
        parent(size),
        beta_(window_taper),
        mu_(fractional_sample_offset) {}

    template <typename T, typename Allocator>
    inline void Kaiser<T, Allocator>::initialize() {
        const auto r      = math::square(2 * beta_ / static_cast<value_type>(parent::size()));
        for (size_type i = 0, sz = parent::size(); i < sz; ++i) {
            //const auto t         = i - static_cast<value_type>(sz - 1) / 2 + mu_;
            //const value_type tmp = constants<value_type>::two_pi * i / static_cast<value_type>(sz);
            parent::data_[i] =
                boost::math::cyl_bessel_j_zero(0, beta_ * std::sqrt(1 - r)) / boost::math::cyl_bessel_j_zero(0, beta_);
        }
    }

    template <typename OutputIterator, typename Integer>
    inline void kaiser(Integer size, OutputIterator out) {
        using value_type = typename std::iterator_traits<OutputIterator>::value_type;
        using size_type  = typename Kaiser<value_type>::size_type;
        Kaiser<value_type> window(static_cast<size_type>(size));
        std::copy(std::cbegin(window), std::cend(window), out);
    }

}}}    // namespace easy::dsp::windowing
#endif // EASYDSP_RCOSTAPER_HPP
