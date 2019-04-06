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
 * File: biquad.hpp
 * Date: 09/06/18
 * Author: Mohammed Boujemaoui
 */

#ifndef EDSP_FILTER_BIQUAD_HPP
#define EDSP_FILTER_BIQUAD_HPP

#include <edsp/math/numeric.hpp>
#include <edsp/meta/expects.hpp>
#include <algorithm>
#include <cmath>
#include <functional>
#include <complex>

namespace edsp { namespace filter {

    /**
    * @brief The filter_type enum defines the different available filters.
    */
    enum class filter_type {
        LowPass,   /*!< Low pass filter */
        HighPass,  /*!< High pass filter */
        BandPass,  /*!< Band pass filter */
        BandStop,  /*!< Band stop filter */
        AllPass,   /*!< All pass filter */
        LowShelf,  /*!< Low shelf (shelving) filter */
        HighShelf, /*!< High shelf (shelving) filter */
        BandShelf, /*!< Band shelf (shelving) filter */
    };

    /**
     * @brief This Biquad class implements a second-order recursive linear filter, containing two poles and two zeros.
     *
     * In the Z domain, its transfer function is:
     *
     * \f[
     *    H(z)={\frac  {b_{0}+b_{1}z^{{-1}}+b_{2}z^{{-2}}}{a_{0}+a_{1}z^{{-1}}+a_{2}z^{{-2}}}}
     * \f]
     *
     * Which is often normalized by dividing all coefficients by a0. This class performs the filtering with a Direct Form I:
     *
     * \f[
     *  y[n]={\frac  {1}{a_{0}}}\left(b_{0}x[n]+b_{1}x[n-1]+b_{2}x[n-2]-a_{1}y[n-1]-a_{2}y[n-2]\right)
     * \f]
     *
     */

    template <typename T>
    class biquad {
    public:
        using value_type = T;

        constexpr biquad() noexcept              = default;
        constexpr biquad(const biquad&) noexcept = default;
        constexpr biquad(biquad&&) noexcept      = default;
        constexpr biquad& operator=(const biquad&) noexcept = default;
        constexpr biquad& operator=(biquad&&) noexcept = default;

        /**
         * @brief Initialize a Biquad filter with one single pole and zero.
         * @param pole Complex value representing the pole.
         * @param zero Complex value representing the zero.
         */
        constexpr biquad(const std::complex<T>& pole, const std::complex<T>& zero);

        /**
         * @brief Initialize a Biquad filter with a pair of zero-pole.
         * @param pole_first Complex value representing the first pole.
         * @param zero_first Complex value representing the first zero.
         * @param pole_second Complex value representing the second pole.
         * @param zero_second Complex value representing the second zeo.
         */
        constexpr biquad(const std::complex<T>& pole_first, const std::complex<T>& zero_first,
                         const std::complex<T>& pole_second, const std::complex<T>& zero_second);

        /**
         * @brief Initialize a Biquad fitler with the given coefficients.
         * @param a0 Value of the coefficient \f$ a_0 \f$.
         * @param a1 Value of the coefficient \f$ a_1 \f$.
         * @param a2 Value of the coefficient \f$ a_2 \f$.
         * @param b0 Value of the coefficient \f$ b_0 \f$.
         * @param b1 Value of the coefficient \f$ b_1 \f$.
         * @param b2 Value of the coefficient \f$ b_2 \f$.
         */
        constexpr biquad(value_type a0, value_type a1, value_type a2, value_type b0, value_type b1,
                         value_type b2) noexcept;
        /**
         * @brief Default destructor.
         */
        ~biquad() = default;

        /**
         * @brief Returns the value of the coefficient \f$ a_0 \f$.
         * @return Value of the coefficient \f$ a_0 \f$.
         */
        constexpr value_type a0() const noexcept;

        /**
         * @brief Returns the value of the coefficient \f$ a_1 \f$.
         * @return Value of the coefficient \f$ a_1 \f$.
         */
        constexpr value_type a1() const noexcept;

        /**
         * @brief Returns the value of the coefficient \f$ a_2 \f$.
         * @return Value of the coefficient \f$ a_2 \f$.
         */
        constexpr value_type a2() const noexcept;

        /**
         * @brief Returns the value of the coefficient \f$ b_0 \f$.
         * @return Value of the coefficient \f$ b_0 \f$.
         */
        constexpr value_type b0() const noexcept;

        /**
         * @brief Returns the value of the coefficient \f$ b_1 \f$.
         * @return Value of the coefficient \f$ b_1 \f$.
         */
        constexpr value_type b1() const noexcept;

        /**
         * @brief Returns the value of the coefficient \f$ b_2 \f$.
         * @return Value of the coefficient \f$ b_2 \f$.
         */
        constexpr value_type b2() const noexcept;

        /**
         * @brief Updates the value of the coefficient \f$ a_0 \f$.
         */
        constexpr void set_a0(T value) noexcept;
        /**
         * @brief Updates the value of the coefficient \f$ a_1 \f$.
         */
        constexpr void set_a1(T value) noexcept;

        /**
         * @brief Updates the value of the coefficient \f$ a_2 \f$.
         */
        constexpr void set_a2(T value) noexcept;

        /**
         * @brief Updates the value of the coefficient \f$ b_0 \f$.
         */
        constexpr void set_b0(T value) noexcept;

        /**
         * @brief Updates the value of the coefficient \f$ b_1 \f$.
         */
        constexpr void set_b1(T value) noexcept;

        /**
         * @brief Updates the value of the coefficient \f$ b_2 \f$.
         */
        constexpr void set_b2(T value) noexcept;

        /**
         * @brief Filters the signal in the range [first, last) and stores the result in another range, beginning at d_first.
         * @param first Input iterator defining the beginning of the input range.
         * @param last Input iterator defining the ending of the input range.
         * @param d_first Output iterator defining the beginning of the destination range.
         * @see tick
         */
        template <typename InputIt, typename OutputIt>
        constexpr void filter(InputIt first, InputIt last, OutputIt d_first);

        /**
         * @brief Reset the filter to the original state
         */
        constexpr void reset() noexcept;

        /**
         * @brief Checks if the Biquad Filter is stable.
         *
         * In general, the two poles of the biquad filter must be inside the unit circle for it to be stable
         * @return true if the filter is stable, false otherwise.
         */
        constexpr bool stability() const noexcept;

        /**
         * @brief Boolean operator to checks if the filter is stable.
         * @see stability
         */
        constexpr explicit operator bool() const noexcept;

        /**
         * @brief Computes the output of filtering one digital time-step.
         * @param value Input value to be filtered.
         * @return Filtered value.
         */
        constexpr value_type tick(T value) noexcept;

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
    constexpr biquad<T>::biquad(value_type a0, value_type a1, value_type a2, value_type b0, value_type b1,
                                value_type b2) noexcept :
        b2_(b2 / a0),
        b1_(b1 / a0),
        b0_(b0 / a0),
        a2_(a2 / a0),
        a1_(a1 / a0),
        a0_(1) {}

    template <typename T>
    constexpr biquad<T>::biquad(const std::complex<T>& pole, const std::complex<T>& zero) :
        b2_(0),
        b1_(1),
        b0_(-zero.real()),
        a2_(0),
        a1_(-pole.real()),
        a0_(1) {
        meta::expects(pole.imag() == 0, "Expecting real pole");
        meta::expects(zero.imag() == 0, "Expecting real zero");
    }

    template <typename T>
    constexpr biquad<T>::biquad(const std::complex<T>& pole_first, const std::complex<T>& zero_first,
                                const std::complex<T>& pole_second, const std::complex<T>& zero_second) :
        b0_(1),
        a0_(1) {
        if (pole_first.imag() != 0) {
            meta::expects(pole_second == std::conj(pole_first), "Expecting complex conjugates");
            a1_ = -2 * pole_first.real();
            a2_ = std::norm(pole_first);
        } else {
            meta::expects(pole_second.imag() == 0, "Expecting a complex number");
            a1_ = -(pole_first.real() + pole_second.real());
            a2_ = pole_first.real() * pole_second.real();
        }

        if (zero_first.imag() != 0) {
            meta::expects(zero_second == std::conj(zero_first), "Expecting complex conjugates");
            b1_ = -2 * zero_first.real();
            b2_ = std::norm(zero_first);
        } else {
            meta::expects(zero_second.imag() == 0, "Expecting a complex number");
            b1_ = -(zero_first.real() + zero_second.real());
            b2_ = zero_first.real() * zero_second.real();
        }
    }

    template <typename T>
    constexpr void biquad<T>::reset() noexcept {
        w0_ = 0;
        w1_ = 0;
    }

    template <typename T>
    constexpr bool biquad<T>::stability() const noexcept {
        return std::abs(a2_) < 1 && (std::abs(a1_) < (1 + a2_));
    }

    template <typename T>
    constexpr void biquad<T>::set_a0(const value_type value) noexcept {
        a0_ = value;
        reset();
    }

    template <typename T>
    constexpr void biquad<T>::set_a1(const value_type value) noexcept {
        a1_ = value;
        reset();
    }

    template <typename T>
    constexpr void biquad<T>::set_a2(const value_type value) noexcept {
        a2_ = value;
        reset();
    }

    template <typename T>
    constexpr void biquad<T>::set_b0(const value_type value) noexcept {
        b0_ = value;
        reset();
    }

    template <typename T>
    constexpr void biquad<T>::set_b1(const value_type value) noexcept {
        b1_ = value;
        reset();
    }

    template <typename T>
    constexpr void biquad<T>::set_b2(const value_type value) noexcept {
        b2_ = value;
        reset();
    }

    template <typename T>
    template <typename InputIt, typename OutputIt>
    constexpr void biquad<T>::filter(InputIt first, InputIt last, OutputIt d_first) {
        for (; first != last; ++first, ++d_first) {
            *d_first = tick(*first);
        }
    }

    template <typename T>
    constexpr typename biquad<T>::value_type biquad<T>::tick(const value_type value) noexcept {
        const auto out = b0_ * value + w0_;
        w0_            = b1_ * value - a1_ * out + w1_;
        w1_            = b2_ * value - a2_ * out;
        return out;
    }

    template <typename T>
    constexpr biquad<T>::operator bool() const noexcept {
        return stability();
    }

    template <typename T>
    constexpr typename biquad<T>::value_type biquad<T>::a0() const noexcept {
        return a0_;
    }

    template <typename T>
    constexpr typename biquad<T>::value_type biquad<T>::a1() const noexcept {
        return a1_;
    }

    template <typename T>
    constexpr typename biquad<T>::value_type biquad<T>::a2() const noexcept {
        return a2_;
    }

    template <typename T>
    constexpr typename biquad<T>::value_type biquad<T>::b0() const noexcept {
        return b0_;
    }

    template <typename T>
    constexpr typename biquad<T>::value_type biquad<T>::b1() const noexcept {
        return b1_;
    }

    template <typename T>
    constexpr typename biquad<T>::value_type biquad<T>::b2() const noexcept {
        return b2_;
    }
}} // namespace edsp::filter

#endif // EDSP_FILTER_BIQUAD_HPP
