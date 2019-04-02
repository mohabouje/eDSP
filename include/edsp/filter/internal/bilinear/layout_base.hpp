/*
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
 * You should have received a copy of the GNU General Public License along width
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * File: layout_base.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EDSP_LAYOUT_BASE_HPP
#define EDSP_LAYOUT_BASE_HPP

#include <edsp/math/numeric.hpp>
#include <edsp/meta/expects.hpp>
#include <edsp/meta/ensure.hpp>
#include <complex>
#include <vector>
#include <array>

namespace edsp { namespace filter {

    inline namespace internal {
        template <typename T>
        constexpr std::complex<T> addmul(const std::complex<T>& left, const T factor,
                                         const std::complex<T>& right) noexcept {
            return std::complex<T>(left.real() + factor * right.real(), left.imag() + factor * right.imag());
        }
    } // namespace internal

    template <typename T>
    struct complex_pair : public std::pair<std::complex<T>, std::complex<T>> {
        using base = std::pair<std::complex<T>, std::complex<T>>;
        explicit constexpr complex_pair(const std::complex<T>& c1) : base(c1, std::complex<T>(0, 0)) {
            meta::expects(c1.imag() == 0, "Expected a real number");
            meta::ensure(this->is_real(), "Expected a real initialization");
        }

        constexpr complex_pair() : base(std::complex<T>(0, 0), std::complex<T>(0, 0)) {}
        constexpr complex_pair(const std::complex<T>& c1, const std::complex<T>& c2) : base(c1, c2) {}
        constexpr bool isConjugate() const noexcept {
            return this->second == std::conj(this->first);
        }

        constexpr bool is_real() const noexcept {
            return this->first.imag() == 0 && this->second.imag() == 0;
        }

        constexpr bool is_matched_pair() const noexcept {
            if (this->first.imag() != 0) {
                return this->second == std::conj(this->first);
            } else {
                return this->second.imag() == 0 && this->second.real() != 0 && this->first.real() != 0;
            }
        }

        constexpr bool NaN() const noexcept {
            return std::isnan(this->first) || std::isnan(this->second);
        }
    };

    template <typename T>
    struct pz_pair : std::pair<complex_pair<T>, complex_pair<T>> {
        using base = std::pair<complex_pair<T>, complex_pair<T>>;
        constexpr pz_pair() : base(complex_pair<T>(), complex_pair<T>()) {}
        constexpr pz_pair(const std::complex<T>& p, const std::complex<T>& z) : base(p, z) {}
        constexpr pz_pair(const std::complex<T>& p1, const std::complex<T>& z1, const std::complex<T>& p2,
                          const std::complex<T>& z2) :
            base(complex_pair<T>(p1, p2), complex_pair<T>(z1, z2)) {}

        constexpr bool single_pole() const noexcept {
            return poles().second == std::complex<T>(0, 0) && zeros().second == std::complex<T>(0, 0);
        }

        constexpr bool NaN() const noexcept {
            return this->first.NaN() || this->second.NaN();
        }

        constexpr const complex_pair<T>& poles() const noexcept {
            return this->first;
        }

        constexpr complex_pair<T>& poles() noexcept {
            return this->first;
        }

        constexpr const complex_pair<T>& zeros() const noexcept {
            return this->second;
        }

        constexpr complex_pair<T>& zeros() noexcept {
            return this->second;
        }
    };

    template <typename T, std::size_t MaxSize = 50>
    struct LayoutBase {
        using value_type      = pz_pair<T>;
        using size_type       = std::size_t;
        using reference       = value_type&;
        using const_reference = const value_type&;
        using iterator        = value_type*;
        using const_iterator  = const value_type*;

        constexpr LayoutBase() = default;

        constexpr T w() const noexcept {
            return normal_W_;
        }

        constexpr T gain() const noexcept {
            return normal_gain_;
        }

        constexpr size_type poles() const noexcept {
            return num_poles_;
        }

        constexpr void set_w(T normal_W) noexcept {
            normal_W_ = normal_W;
        }

        constexpr void set_gain(T normal_gain) noexcept {
            normal_gain_ = normal_gain;
        }

        constexpr void insert(const std::complex<T>& pole, const std::complex<T>& zero) {
            meta::ensure(math::is_even(num_poles_));
            meta::expects(!math::is_nan(pole), "NAN number cannot be a pole");
            pairs_[num_poles_ / 2] = pz_pair<T>(pole, zero);
            num_poles_ += 1;
        }

        constexpr void insert_conjugate(const std::complex<T>& pole, const std::complex<T>& zero) {
            meta::ensure(math::is_even(num_poles_));
            meta::expects(!math::is_nan(pole), "NAN number cannot be a pole");
            meta::expects(!math::is_nan(zero), "NAN number cannot be a zero");
            pairs_[num_poles_ / 2] = pz_pair<T>(pole, zero, std::conj(pole), std::conj(zero));
            num_poles_ += 2;
        }

        constexpr void insert(const complex_pair<T>& poles, const complex_pair<T>& zeros) {
            meta::ensure(math::is_even(num_poles_));
            meta::expects(poles.is_matched_pair(), "Expected conjugate pairs");
            meta::expects(zeros.is_matched_pair(), "Expected conjugate pairs");
            pairs_[num_poles_ / 2] = pz_pair<T>(poles.first, zeros.first, poles.second, zeros.second);
            num_poles_ += 2;
        }

        constexpr void reset() noexcept {
            num_poles_ = 0;
        }

        constexpr size_type size() const noexcept {
            return static_cast<size_type>(std::ceil(num_poles_ / 2) + 1);
        }

        constexpr const_iterator cbegin() const noexcept {
            return std::cbegin(pairs_);
        }

        constexpr const_iterator cend() const noexcept {
            return std::cbegin(pairs_) + size();
        }

        constexpr const_reference operator[](size_type index) const noexcept {
            meta::expects(index < size(), "Index out of bounds");
            return pairs_[index];
        }

        constexpr const_reference at(size_type index) const {
            if (index >= size()) {
                throw std::runtime_error("Index out of bounds");
            }
            return pairs_[index];
        }

    private:
        size_type num_poles_{0};
        std::array<value_type, MaxSize> pairs_{};
        T normal_W_{0};
        T normal_gain_{1};
    };

}} // namespace edsp::filter

#endif // EDSP_LAYOUT_BASE_HPP
