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
 * Filename: biquad.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_FILTER_BIQUAD_HPP
#define EASYDSP_FILTER_BIQUAD_HPP

#include <easy/dsp/math/math.hpp>
#include <easy/dsp/filter/filter_types.hpp>
#include <algorithm>
#include <cmath>
#include <functional>
#include <complex>

namespace easy { namespace dsp { namespace filter {

    template <typename T>
    class Biquad {
    public:
        using value_type = T;

        constexpr Biquad() noexcept              = default;
        constexpr Biquad(const Biquad&) noexcept = default;
        constexpr Biquad(Biquad&&) noexcept      = default;
        constexpr Biquad& operator=(const Biquad&) noexcept = default;
        constexpr Biquad& operator=(Biquad&&) noexcept = default;
        constexpr Biquad(const std::complex<T>& pole, const std::complex<T>& zero);
        constexpr Biquad(const std::complex<T>& pole_first, const std::complex<T>& pole_second,
                         const std::complex<T>& zero_first, const std::complex<T>& zero_second);
        constexpr Biquad(value_type a0, value_type a1, value_type a2, value_type b0, value_type b1,
                         value_type b2) noexcept;
        ~Biquad() = default;

        constexpr value_type a0() const noexcept;
        constexpr value_type a1() const noexcept;
        constexpr value_type a2() const noexcept;
        constexpr value_type b0() const noexcept;
        constexpr value_type b1() const noexcept;
        constexpr value_type b2() const noexcept;

        constexpr void setA0(T value) noexcept;
        constexpr void setA1(T value) noexcept;
        constexpr void setA2(T value) noexcept;
        constexpr void setB0(T value) noexcept;
        constexpr void setB1(T value) noexcept;
        constexpr void setB2(T value) noexcept;

        template <typename BiIterator>
        constexpr void filter(BiIterator first, BiIterator last);

        template <typename InputIterator, typename OutputIterator>
        constexpr void filter(InputIterator first, InputIterator last, OutputIterator out);

        constexpr void reset() noexcept;
        constexpr bool isStable() const noexcept;

        constexpr value_type operator()(T tick) noexcept;
        constexpr operator bool() const noexcept;

    private:
        value_type b2_{0};
        value_type b1_{0};
        value_type b0_{1};
        value_type a2_{0};
        value_type a1_{0};
        value_type a0_{1};
        value_type w0_{0};
        value_type w1_{0};
    };

    template <typename T>
    constexpr Biquad<T>::Biquad(value_type a0, value_type a1, value_type a2, value_type b0, value_type b1,
                                value_type b2) noexcept :
        b2_(b2 / a0),
        b1_(b1 / a0),
        b0_(b0 / a0),
        a2_(a2 / a0),
        a1_(a1 / a0),
        a0_(1) {}

    template <typename T>
    constexpr Biquad<T>::Biquad(const std::complex<T>& pole, const std::complex<T>& zero) :
        a0_(1),
        a1_(-pole.real()),
        a2_(0),
        b0_(-zero.real()),
        b1_(1),
        b2_(0) {}

    template <typename T>
    constexpr Biquad<T>::Biquad(const std::complex<T>& pole_first, const std::complex<T>& pole_second,
                                const std::complex<T>& zero_first, const std::complex<T>& zero_second) :
        a0_(1),
        b0_(1) {
        if (pole_first.imag() != 0) {
            a1_ = -2 * pole_first.real();
            a2_ = math::square(std::abs(pole_first));
        } else {
            a1_ = -(pole_first.real() + pole_second.real());
            a2_ = pole_first.real() * pole_second.real();
        }

        if (zero_first.imag() != 0) {
            b1_ = -2 * zero_first.real();
            b2_ = math::square(std::abs(pole_first));
        } else {
            b1_ = -(zero_first.real() + zero_second.real());
            b2_ = zero_first.real() * zero_second.real();
        }
    }

    template <typename T>
    constexpr void Biquad<T>::reset() noexcept {
        w0_ = 0;
        w1_ = 1;
    }

    template <typename T>
    constexpr bool Biquad<T>::isStable() const noexcept {
        return std::abs(a2_) < 1 && (std::abs(a1_) < (1 + a2_));
    }

    template <typename T>
    constexpr void Biquad<T>::setA0(const value_type value) noexcept {
        a0_ = value;
        reset();
    }

    template <typename T>
    constexpr void Biquad<T>::setA1(const value_type value) noexcept {
        a1_ = value;
        reset();
    }

    template <typename T>
    constexpr void Biquad<T>::setA2(const value_type value) noexcept {
        a2_ = value;
        reset();
    }

    template <typename T>
    constexpr void Biquad<T>::setB0(const value_type value) noexcept {
        b0_ = value;
        reset();
    }

    template <typename T>
    constexpr void Biquad<T>::setB1(const value_type value) noexcept {
        b1_ = value;
        reset();
    }

    template <typename T>
    constexpr void Biquad<T>::setB2(const value_type value) noexcept {
        b2_ = value;
        reset();
    }

    template <typename T>
    template <typename BiIterator>
    constexpr void Biquad<T>::filter(BiIterator first, BiIterator last) {
        filter(first, last, first);
    }

    template <typename T>
    template <typename InputIterator, typename OutputIterator>
    constexpr void Biquad<T>::filter(InputIterator first, InputIterator last, OutputIterator out) {
        static_assert(std::is_same<typename std::iterator_traits<InputIterator>::value_type, T>::value &&
                          std::is_same<typename std::iterator_traits<OutputIterator>::value_type, T>::value,
                      "Iterator does not math the value type. No implicit conversion is allowed");
        std::transform(first, last, out, std::ref(*this));
    }

    template <typename T>
    constexpr typename Biquad<T>::value_type Biquad<T>::operator()(const value_type tick) noexcept {
        // Using Direct Form I
        const auto out = b0_ * tick + w0_;
        w0_            = b1_ * tick - a1_ * out + w1_;
        w1_            = b2_ * tick - a2_ * out;
        return out;
    }

    template <typename T>
    constexpr Biquad<T>::operator bool() const noexcept {
        return isStable();
    }

    template <typename T>
    constexpr typename Biquad<T>::value_type Biquad<T>::a0() const noexcept {
        return a0_;
    }

    template <typename T>
    constexpr typename Biquad<T>::value_type Biquad<T>::a1() const noexcept {
        return a1_;
    }

    template <typename T>
    constexpr typename Biquad<T>::value_type Biquad<T>::a2() const noexcept {
        return a2_;
    }

    template <typename T>
    constexpr typename Biquad<T>::value_type Biquad<T>::b0() const noexcept {
        return b0_;
    }

    template <typename T>
    constexpr typename Biquad<T>::value_type Biquad<T>::b1() const noexcept {
        return b1_;
    }

    template <typename T>
    constexpr typename Biquad<T>::value_type Biquad<T>::b2() const noexcept {
        return b2_;
    }
}}} // namespace easy::dsp::filter

#endif // EASYDSP_FILTER_BIQUAD_HPP
