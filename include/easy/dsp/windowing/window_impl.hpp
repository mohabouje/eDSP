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
 * Filename: window_impl.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_WINDOW_HPP
#define EASYDSP_WINDOW_HPP

#include <easy/dsp/math/constant.hpp>
#include <easy/meta/expects.hpp>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>
#include <cmath>

namespace easy { namespace dsp { namespace windowing {

    template <typename Implementation, typename T, typename Allocator = std::allocator<T>>
    struct Window {
        using value_type      = T;
        using size_type       = std::size_t;
        using reference       = value_type&;
        using const_reference = const value_type&;
        using iterator        = typename std::vector<value_type, Allocator>::iterator;
        using const_iterator  = typename std::vector<value_type, Allocator>::const_iterator;

        inline explicit Window(size_type size);
        inline void setSize(size_type size);
        inline size_type size() const noexcept;
        inline value_type at(size_type index) const;

        inline reference operator[](size_type index) noexcept;
        inline const_reference operator[](size_type index) const noexcept;
        inline iterator begin() noexcept;
        inline const_iterator begin() const noexcept;
        inline const_iterator cbegin() const noexcept;
        inline iterator end() noexcept;
        inline const_iterator end() const noexcept;
        inline const_iterator cend() const noexcept;

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
        meta::expects(size > 0, "Window size must be a positive integer");
        initialize();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline void Window<Implementation, T, Allocator>::setSize(Window::size_type size) {
        data_.resize(size);
        initialize();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::size_type Window<Implementation, T, Allocator>::size() const
        noexcept {
        return data_.size();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::value_type
        Window<Implementation, T, Allocator>::at(Window::size_type index) const {
        if (index >= size()) {
            throw std::runtime_error("Index out of bounds");
        }
        return data_[index];
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::reference Window<Implementation, T, Allocator>::
        operator[](Window::size_type index) noexcept {
        return data_[index];
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::const_reference Window<Implementation, T, Allocator>::
        operator[](Window::size_type index) const noexcept {
        return data_[index];
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::iterator
        Window<Implementation, T, Allocator>::begin() noexcept {
        return data_.begin();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::const_iterator
        Window<Implementation, T, Allocator>::begin() const noexcept {
        return data_.begin();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::const_iterator
        Window<Implementation, T, Allocator>::cbegin() const noexcept {
        return data_.cbegin();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::iterator
        Window<Implementation, T, Allocator>::end() noexcept {
        return data_.end();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::const_iterator
        Window<Implementation, T, Allocator>::end() const noexcept {
        return data_.end();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline typename Window<Implementation, T, Allocator>::const_iterator
        Window<Implementation, T, Allocator>::cend() const noexcept {
        return data_.cend();
    }

    template <typename Implementation, typename T, typename Allocator>
    inline void Window<Implementation, T, Allocator>::initialize() {
        static_cast<Implementation*>(this)->initialize();
    }

    template <typename Implementation, typename T, typename Allocator>
    template <typename InputIterator, typename OutputIterator>
    inline void Window<Implementation, T, Allocator>::compute(InputIterator first, InputIterator last,
                                                              OutputIterator out) {
        meta::expects(std::distance(first, last) == size(), "Expecting a buffer with the same size");
        std::transform(first, last, std::begin(data_), out, std::multiplies<T>());
    }

    template <typename Implementation, typename T, typename Allocator>
    template <typename BiIterator>
    inline void Window<Implementation, T, Allocator>::compute(BiIterator first, BiIterator last) {
        compute(first, last, first);
    }

}}} // namespace easy::dsp::windowing

#endif // EASYDSP_WINDOW_HPP
