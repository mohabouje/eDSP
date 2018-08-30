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
 * Filename: biquad_cascade.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EASYDSP_BIQUAD_CASCADE_HPP
#define EASYDSP_BIQUAD_CASCADE_HPP

#include <easy/meta/expects.hpp>
#include <easy/meta/ensure.hpp>
#include <easy/dsp/math/constant.hpp>
#include <easy/dsp/math/complex.hpp>
#include <easy/dsp/filter/iir/designer/bilinear/layout_base.hpp>
#include <easy/dsp/filter/iir/biquad.hpp>

namespace easy { namespace dsp { namespace filter {

    template <typename T, std::size_t N>
    struct BiquadCascade {
        using value_type      = Biquad<T>;
        using reference       = value_type&;
        using const_reference = const value_type&;
        using iterator        = value_type*;
        using const_iterator  = const value_type*;
        using size_type       = std::size_t;

        constexpr BiquadCascade() = default;

        constexpr size_type size() const noexcept {
            return num_stage_;
        }

        constexpr void clear() {
            num_stage_ = 0;
        }

        constexpr void reset() {
            for (auto i = 0ul; i < num_stage_; ++i) {
                cascade_[i].reset();
            }
        }

        constexpr const_reference operator[](size_type index) const noexcept {
            return cascade_[index];
        }

        constexpr const_iterator cbegin() const noexcept {
            return std::cbegin(cascade_);
        }

        constexpr const_iterator begin() const noexcept {
            return std::cbegin(cascade_);
        }

        constexpr const_iterator cend() const noexcept {
            return std::cbegin(cascade_) + size();
        }

        constexpr const_iterator end() const noexcept {
            return std::cbegin(cascade_) + size();
        }

        template <typename InputIterator, typename OutputIterator>
        constexpr void filter(InputIterator first, InputIterator last, OutputIterator out) {
            static_assert(std::is_same<typename std::iterator_traits<InputIterator>::value_type, T>::value &&
                              std::is_same<typename std::iterator_traits<OutputIterator>::value_type, T>::value,
                          "Iterator does not math the value type. No implicit conversion is allowed");
            std::transform(first, last, out, std::ref(*this));
        }

        template <typename BiIterator>
        constexpr void filter(BiIterator first, BiIterator last) {
            filter(first, last, first);
        }

        template <typename T>
        constexpr value_type operator()(value_type tick) noexcept {
            for (auto i = 0ul; i < num_stage_; ++i) {
                tick = cascade_[i](tick);
            }
            return tick;
        }

        constexpr void push_back(const Biquad<T>& biquad) {
            meta::ensure(num_stage_ < N, "No space available");
            cascade_[num_stage_] = biquad;
        }

        template <typename... Arg>
        constexpr void emplace_back(Arg... arg) {
            meta::ensure(num_stage_ < N, "No space available");
            cascade_[num_stage_] = Biquad(std::forward(arg...));
        }

    private:
        std::size_t num_stage_;
        std::array<Biquad<T>, N> cascade_;
    };
}}}    // namespace easy::dsp::filter
#endif // EASYDSP_BIQUAD_CASCADE_HPP
