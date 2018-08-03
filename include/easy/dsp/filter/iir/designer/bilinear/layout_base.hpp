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
 * Filename: layout_base.hpp
 * Author: Mohammed Boujemaoui
 * Date: 3/8/2018
 */
#ifndef EASYDSP_LAYOUT_BASE_HPP
#define EASYDSP_LAYOUT_BASE_HPP

#include <easy/meta/math.hpp>
#include <easy/meta/expects.hpp>
#include <complex>
#include <vector>

namespace easy { namespace dsp { namespace filter {

    template <typename T>
    struct complex_pair : public std::pair<std::complex<T>, std::complex<T>> {
        using base = std::pair<std::complex<T>, std::complex<T>>;
        explicit constexpr complex_pair(const std::complex<T>& c1) :
            base(c1, std::complex<T>(0, 0)) {}

        constexpr complex_pair(const std::complex<T>& c1, const std::complex<T>& c2) :
            base(c1, c2) {}

        constexpr isConjugate() const noexcept {
            return this->second == std::conj(first);
        }

        constexpr isReal() const noexcept {
            return this->first.imag() == 0
                    && this->second.imag() == 0;
        }

        constexpr isMatchedPair() const noexcept {
            if (this->first.imag() != 0) {
                return this->second == std::conj (first);
            } else {
                return this->second.imag () == 0 &&
                     this->second.real () != 0 &&
                     this->first.real () != 0;
            }
        }

        constexpr isNaN() const noexcept {
            return std::isnan(this->first) || std::isnan(this->second);
        }
    };

    template <typename T>
    struct pz_pair : std::pair<complex_pair<T>, complex_pair<T>> {
        using base =  std::pair<complex_pair<T>, complex_pair<T>> ;
        constexpr pz_pair(const std::complex<T>& p, const std::complex<T>& z) :
            base(p, z) {}

        constexpr pz_pair(const std::complex<T>& p1, const std::complex<T>& z1,
                          const std::complex<T>& p2, const std::complex<T>& z2) :
            base(complex_pair(p1, z1), complex_pair(p2, z2)) {}

        constexpr isSinglePole() const noexcept {
            return this->first.isReal() && this->second.isReal();
        }

        constexpr isNaN() const noexcept {
            return this->first.isNaN() || this->second.isNaN();
        }

    };


    template <typename T,
              typename Allocator = std::allocator<pz_pair>>
    struct LayoutBase {
        using value_type = pz_pair<T>;
        using size_type = std::size_t;

        explicit LayoutBase(size_type number_poles) :
            num_poles_(number_poles)
        {
            pairs_.reserve(meta::is_odd(number_poles) ? number_poles / 2 + 1
                                                      : number_poles / 2);
        }

        T normalW() const noexcept {
            return normal_W_;
        }

        T normalGain() const noexcept {
            return normal_Gain_;
        }

        size_type numberPoles() const noexcept {
            return num_poles_;
        }

        void setNormalW(T normal_W) noexcept {
            normal_W_ = normal_W;
        }

        void setNormalGain(T normal_gain) noexcept {
            normal_gain_ = normal_gain;
        }

        void insert(const std::complex<T>& pole, const std::complex<T>& zero) {
            pairs_.emplace_back(pole, zero);
            ++num_poles_;
        }

        void insert_conjugate(const std::complex<T>& pole, const std::complex<T>& zero) {
            pairs_.emplace_back(pole, zero, std::conj(pole), std::conj(zero));
            num_poles_ += 2;
        }

        void insert(const complex_pair& poles, const complex_pair& zeros) {
            pairs_.emplace_back(poles.first, zeros.first, poles.second, zeros.second);
            num_poles_ += 2;
        }

        void reset() noexcept {
            num_poles_ = 0;
            pairs_.clear();
        }

        const value_type& operator[](size_type index) const noexcept {
            meta::expects(index < (num_poles_ + 1 ) / 2, "Index out of bounds");
            return pair_[index];
        }

        value_type& operator[](size_type index) noexcept {
            meta::expects(index < (num_poles_ + 1 ) / 2, "Index out of bounds");
            return pair_[index];
        }

    private:
        size_type num_poles_;
        std::vector<value_type, Allocator> pairs_;
        T normal_W_;
        T normal_gain_;
    };

}}}

#endif // EASYDSP_LAYOUT_BASE_HPP
