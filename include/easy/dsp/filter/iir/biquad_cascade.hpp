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

        constexpr size_type max_size() const noexcept {
            return N;
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

        constexpr reference operator[](size_type index) noexcept {
            return cascade_[index];
        }

        constexpr iterator begin() noexcept {
            return std::begin(cascade_);
        }

        constexpr iterator end() noexcept {
            return std::begin(cascade_) + size();
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

        template <typename InputIt, typename OutputIt>
        constexpr void filter(InputIt first, InputIt last, OutputIt d_first) {
            for (; first != last; ++first, ++d_first) {
                *d_first = tick(*first);
            }
        }

        constexpr value_type tick(value_type tick) noexcept {
            for (auto i = 0ul; i < num_stage_; ++i) {
                tick = cascade_[i](tick);
            }
            return tick;
        }

        constexpr void push_back(const Biquad<T>& biquad) {
            meta::ensure(num_stage_ < N, "No space available");
            cascade_[num_stage_] = biquad;
            num_stage_++;
        }

        template <typename... Arg>
        constexpr void emplace_back(Arg... arg) {
            meta::ensure(num_stage_ < N, "No space available");
            cascade_[num_stage_] = Biquad<T>(arg...);
            num_stage_++;
        }

    private:
        std::size_t num_stage_{0};
        std::array<Biquad<T>, N> cascade_;
    };
}}}    // namespace easy::dsp::filter
#endif // EASYDSP_BIQUAD_CASCADE_HPP
