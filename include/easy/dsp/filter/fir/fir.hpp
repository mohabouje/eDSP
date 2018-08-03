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
 * Filename: fir.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EASYDSP_FILTER_FIR_HPP
#define EASYDSP_FILTER_FIR_HPP

#include <boost/circular_buffer.hpp>
#include <easy/meta/size.hpp>
#include <numeric>
#include <algorithm>
#include <initializer_list>
#include <vector>

namespace easy { namespace dsp { namespace filter {

    template <typename T, typename Allocator = std::allocator<T>>
    class FIR {
    public:
        using value_type = T;
        using size_type  = typename std::vector<value_type, Allocator>::size_type;
        explicit FIR()   = default;
        explicit FIR(std::initializer_list<T> init, const Allocator& alloc = Allocator());

        size_type size() const noexcept;
        value_type gain() const noexcept;
        void setGain(value_type gain) noexcept;
        const std::vector<value_type, Allocator>& taps() const noexcept;
        void setTaps(const std::vector<value_type, Allocator>& taps);

        template <typename InputIterator, typename OutputIterator>
        void filter(InputIterator first, InputIterator last, OutputIterator out);

        template <typename BiIterator>
        void filter(BiIterator first, BiIterator last);

        value_type operator()(value_type tick);

    private:
        using buf = boost::circular_buffer<value_type, Allocator>;
        std::vector<value_type, Allocator> b_{};
        buf delay_{};
        value_type gain_{1};
    };

    template <typename T, typename Allocator>
    explicit FIR<T, Allocator>::FIR(std::initializer_list<T> init, const Allocator& alloc = Allocator()) :
        b_(init, alloc),
        delay_(meta::size(b), 0) {}

    template <typename T, typename Allocator>
    typename FIR<T, Allocator>::size_type FIR<T, Allocator>::size() const noexcept {
        return meta::size(b_);
    }

    template <typename T, typename Allocator>
    typename FIR<T, Allocator>::value_type FIR<T, Allocator>::gain() const noexcept {
        return gain_;
    }

    template <typename T, typename Allocator>
    void FIR<T, Allocator>::setGain(value_type gain) noexcept {
        gain_ = gain;
    }

    template <typename T, typename Allocator>
    const std::vector<typename FIR<T, Allocator>::value_type, Allocator>& FIR<T, Allocator>::taps() const noexcept {
        return b_;
    }

    template <typename T, typename Allocator>
    void FIR<T, Allocator>::setTaps(const std::vector<value_type, Allocator>& taps) {
        b_     = taps;
        delay_ = buf(meta::size(taps), 0);
    }

    template <typename T, typename Allocator>
    template <typename InputIterator, typename OutputIterator>
    void FIR<T, Allocator>::filter(InputIterator first, InputIterator last, OutputIterator out) {
        for (; first != last; ++first, ++out) {
            *out = this->operator()(*first);
        }
    }

    template <typename T, typename Allocator>
    template <typename BiIterator>
    void FIR<T, Allocator>::filter(BiIterator first, BiIterator last) {
        filter(first, last, first);
    }

    template <typename T, typename Allocator>
    typename FIR<T, Allocator>::value_type FIR<T, Allocator>::operator()(value_type tick) {
        delay_.push_back(tick);
        const auto result =
            std::inner_product(std::cbegin(b_), std::cend(b_), std::rbegin(delay_), static_cast<value_type>(0));
        return result / gain_;
    }

}}} // namespace easy::dsp::filter

#endif // EASYDSP_FILTER_FIR_HPP
