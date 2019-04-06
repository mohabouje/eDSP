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
 * File: biquad_cascade.hpp
 * Author: Mohammed Boujemaoui
 * Date: 30/8/2018
 */
#ifndef EDSP_BIQUAD_CASCADE_HPP
#define EDSP_BIQUAD_CASCADE_HPP

#include <edsp/meta/expects.hpp>
#include <edsp/meta/ensure.hpp>
#include <edsp/filter/biquad.hpp>
#include <array>
#include <edsp/meta/iterator.hpp>

namespace edsp { namespace filter {

    /**
     * @brief The BiquadCascade class implements a cascade of Biquad filters.
     *
     * This class implements arbitrary order recursive (IIR) filters as a cascade of second order Biquad sections. In this implementation
     * the output from the first filter is the input to the second, and so on.
     *
     * @tparam T Value type
     * @tparam N Number representing the maximum size (number of Biquad).
     */
    template <typename T, std::size_t N>
    class biquad_cascade {
    public:
        using value_type      = biquad<T>;
        using reference       = value_type&;
        using const_reference = const value_type&;
        using iterator        = value_type*;
        using const_iterator  = const value_type*;
        using size_type       = std::size_t;

        /**
         * @brief Creates an empty %biquad_cascade
         */
        constexpr biquad_cascade() = default;

        /**
         * @brief Default destructor
         */
        ~biquad_cascade() = default;

        /**
         * @brief Returns the number of Biquads
         * @return Number of biquads
         */
        constexpr size_type size() const noexcept;

        /**
         * @brief Returns the maximum number of Biquads the BiquadCascade is able to hold.
         * @return Maximum number of elements.
         * @see N
         */
        constexpr size_type max_size() const noexcept;

        /**
         * @brief Returns the capacity the BiquadCascade.
         *
         * The capacity represents the maximum number of Biquad the containes is able to hold.
         * @return Capacity of the currently allocated storage..
         * @see max_size
         */
        constexpr size_type capacity() const noexcept;

        /**
         * @brief Clear the contents of the BiquadCascade.
         *
         * Leaves the capacity() of the vector unchanged.
         * @see capacity
         */
        constexpr void clear();

        /**
         * @brief Reset all the internal Biquads to the original state.
         */
        constexpr void reset();

        /**
         * @brief Returns a constant reference to the Biquad at specified location pos. No bounds checking is performed.
         * @param index Position of the element to return.
         * @return Constant reference to the requested Biquad.
         */
        constexpr const_reference operator[](size_type index) const noexcept;

        /**
         * @brief Returns a reference to the Biquad at specified location pos. No bounds checking is performed.
         * @param index Position of the element to return.
         * @return Reference to the requested Biquad.
         */
        constexpr reference operator[](size_type index) noexcept;

        /**
         * @brief Returns an iterator to the first element of the container.
         * @return Iterator to the first element.
         */
        constexpr iterator begin() noexcept;

        /**
         * @brief Returns an iterator to the last element of the container.
         * @return Iterator to the last element.
         */
        constexpr iterator end() noexcept;

        /**
         * @brief Returns a constant iterator to the first element of the container.
         * @return Iterator to the first element.
         */
        constexpr const_iterator cbegin() const noexcept;

        /**
         * @brief Returns a constant iterator to the first element of the container.
         * @return Iterator to the first element.
         */
        constexpr const_iterator begin() const noexcept;

        /**
         * @brief Returns a constant iterator to the last element of the container.
         * @return Iterator to the last element.
         */
        constexpr const_iterator cend() const noexcept;

        /**
         * @brief Returns a constant iterator to the last element of the container.
         * @return Iterator to the last element.
         */
        constexpr const_iterator end() const noexcept;

        /**
         * @brief Filters the signal in the range [first, last) and stores the result in another range, beginning at d_first.
         * @tparam InputIt Input iterator holding an arithmetic type.
         * @tparam OutputIt Output iterator holding an arithmetic type.
         * @param first Input iterator defining the beginning of the input range.
         * @param last Input iterator defining the ending of the input range.
         * @param d_first Output iterator defining the beginning of the destination range.
         */
        template <typename InputIt, typename OutputIt>
        constexpr void filter(InputIt first, InputIt last, OutputIt d_first);

        /**
         * @brief Computes the output of filtering one digital time-step.
         * @param value Input value to be filtered.
         * @return Filtered value.
         */
        constexpr T tick(T value) noexcept;

        /**
         * @brief Appends the given Biquad at the end.
         * @param biquad Biquad to append.
         */
        constexpr void push_back(const biquad<T>& biquad);

        /**
         * @brief Construct a Biquad in-place at the end.
         * @param arg Arguments to forward to the constructor of the element
         */
        template <typename... Arg>
        constexpr void emplace_back(Arg... arg);

    private:
        std::size_t num_stage_{0};
        std::array<biquad<T>, N> cascade_{};
    };

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::size_type biquad_cascade<T, N>::size() const noexcept {
        return num_stage_;
    }

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::size_type biquad_cascade<T, N>::max_size() const noexcept {
        return N;
    }

    template <typename T, size_t N>
    template <typename... Arg>
    constexpr void biquad_cascade<T, N>::emplace_back(Arg... arg) {
        meta::ensure(num_stage_ < N, "No space available");
        cascade_[num_stage_] = biquad<T>(arg...);
        num_stage_++;
    }

    template <typename T, size_t N>
    constexpr void biquad_cascade<T, N>::push_back(const biquad<T>& biquad) {
        meta::ensure(num_stage_ < N, "No space available");
        cascade_[num_stage_] = biquad;
        num_stage_++;
    }

    template <typename T, size_t N>
    constexpr T biquad_cascade<T, N>::tick(T value) noexcept {
        for (auto i = 0ul; i < num_stage_; ++i) {
            value = cascade_[i].tick(value);
        }
        return value;
    }

    template <typename T, size_t N>
    template <typename InputIt, typename OutputIt>
    constexpr void biquad_cascade<T, N>::filter(InputIt first, InputIt last, OutputIt d_first) {
        for (; first != last; ++first, ++d_first) {
            *d_first = tick(*first);
        }
    }

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::const_iterator biquad_cascade<T, N>::end() const noexcept {
        return std::cbegin(cascade_) + size();
    }

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::const_iterator biquad_cascade<T, N>::cend() const noexcept {
        return std::cbegin(cascade_) + size();
    }

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::const_iterator biquad_cascade<T, N>::begin() const noexcept {
        return std::cbegin(cascade_);
    }

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::const_iterator biquad_cascade<T, N>::cbegin() const noexcept {
        return std::cbegin(cascade_);
    }

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::iterator biquad_cascade<T, N>::end() noexcept {
        return std::begin(cascade_) + size();
    }

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::iterator biquad_cascade<T, N>::begin() noexcept {
        return std::begin(cascade_);
    }

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::reference biquad_cascade<T, N>::
        operator[](biquad_cascade::size_type index) noexcept {
        return cascade_[index];
    }

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::const_reference biquad_cascade<T, N>::
        operator[](biquad_cascade::size_type index) const noexcept {
        return cascade_[index];
    }

    template <typename T, size_t N>
    constexpr void biquad_cascade<T, N>::reset() {
        for (auto i = 0ul; i < num_stage_; ++i) {
            cascade_[i].reset();
        }
    }

    template <typename T, size_t N>
    constexpr void biquad_cascade<T, N>::clear() {
        num_stage_ = 0;
    }

    template <typename T, size_t N>
    constexpr typename biquad_cascade<T, N>::size_type biquad_cascade<T, N>::capacity() const noexcept {
        return N;
    }
}}     // namespace edsp::filter
#endif // EDSP_BIQUAD_CASCADE_HPP
