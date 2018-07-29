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
 * Filename: window.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_WINDOW_HPP
#define EASYDSP_WINDOW_HPP


#include "easy/dsp/math/constant.hpp"
#include <algorithm>

namespace easy { namespace dsp { namespace windowing {

    template <typename Implementation, typename T, typename Allocator = std::allocator<T>>
    struct Window {
        using value_type = T;
        using size_type  = std::size_t;
        inline explicit Window(size_type size);
        inline void set_size(size_type size);
        inline size_type size() const noexcept;

        template <typename InputIterator, typename OutputIterator>
        inline void compute(InputIterator first, InputIterator last, OutputIterator out);

        template <typename BiIterator>
        inline void compute(BiIterator first, BiIterator last);

    private:
        void initialize();

    protected:
        std::vector<value_type, Allocator> data_{};
    };

    template <typename Implementation, typename T, typename Allocator>
    inline Window<Implementation, T, Allocator>::Window(Window::size_type size) : data_(size) {
        initialize();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline void Window<Implementation, T, Allocator>::set_size(Window::size_type size) {
        data_.resize(size);
        initialize();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::size_type
        Window<Implementation, T, Allocator>::size() const noexcept {
        return data_.size();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline void Window<Implementation, T, Allocator>::initialize() {
        static_cast<Implementation*>(this)->initialize();
    }

    template <typename Implementation, typename T, typename Allocator>
    template <typename InputIterator, typename OutputIterator>
    inline void Window<Implementation, T, Allocator>::compute(InputIterator first, InputIterator last,
                                                                OutputIterator out) {
        E_ENSURES_MSG(std::distance(first, last) == size(), "Expecting a buffer with the same size");
        std::transform(first, last, std::begin(data_), out, std::multiplies<T>());
    }

    template <typename Implementation, typename T, typename Allocator>
    template <typename BiIterator>
    inline void Window<Implementation, T, Allocator>::compute(BiIterator first, BiIterator last) {
        compute(first, last, first);
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_WINDOW_HPP
