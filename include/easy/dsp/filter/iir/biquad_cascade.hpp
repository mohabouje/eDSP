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
#include <easy/dsp/filter/iir/biquad.hpp>
#include <array>

namespace easy { namespace dsp { namespace filter {

    /**
     * @class BiquadCascade
     * @brief The BiquadCascade class implements a cascade of Biquad filters.
     *
     * This class implements arbitrary order recursive (IIR) filters as a cascade of second order Biquad sections. In this implementation
     * the output from the first filter is the input to the second, and so on.
     *
     * @tparam T Value type
     * @tparam N Number representing the maximum size (number of Biquad).
     */
    template <typename T, std::size_t N>
    struct BiquadCascade {
        using value_type      = Biquad<T>;
        using reference       = value_type&;
        using const_reference = const value_type&;
        using iterator        = value_type*;
        using const_iterator  = const value_type*;
        using size_type       = std::size_t;

        /**
         * @brief Creates an empty #BiquadCascade
         */
        constexpr BiquadCascade() = default;

        constexpr size_type size() const noexcept {
            return num_stage_;
        }

        /**
         * @brief Returns the maximum number of Biquads the BiquadCascade is able to hold.
         * @return Maximum number of elements.
         * @see N
         */
        constexpr size_type max_size() const noexcept {
            return N;
        }

        /**
         * @brief Returns the capacity the BiquadCascade.
         *
         * The capacity represents the maximum number of Biquad the containes is able to hold.
         * @return Capacity of the currently allocated storage..
         * @see max_size
         */
        constexpr size_type capacity() const noexcept {
            return N;
        }

        /**
         * @brief Clear the contents of the BiquadCascade.
         *
         * Leaves the capacity() of the vector unchanged.
         * @see capacity
         */
        constexpr void clear() {
            num_stage_ = 0;
        }

        /**
         * @brief Reset all the internal Biquads to the original state.
         */
        constexpr void reset() {
            for (auto i = 0ul; i < num_stage_; ++i) {
                cascade_[i].reset();
            }
        }

        /**
         * @brief Returns a constant reference to the Biquad at specified location pos. No bounds checking is performed.
         * @param index Position of the element to return.
         * @return Constant reference to the requested Biquad.
         */
        constexpr const_reference operator[](size_type index) const noexcept {
            return cascade_[index];
        }

        /**
         * @brief Returns a reference to the Biquad at specified location pos. No bounds checking is performed.
         * @param index Position of the element to return.
         * @return Reference to the requested Biquad.
         */
        constexpr reference operator[](size_type index) noexcept {
            return cascade_[index];
        }

        /**
         * @brief Returns an iterator to the first element of the container.
         * @return Iterator to the first element.
         */
        constexpr iterator begin() noexcept {
            return std::begin(cascade_);
        }

        /**
         * @brief Returns an iterator to the last element of the container.
         * @return Iterator to the last element.
         */
        constexpr iterator end() noexcept {
            return std::begin(cascade_) + size();
        }

        /**
         * @brief Returns a constant iterator to the first element of the container.
         * @return Iterator to the first element.
         */
        constexpr const_iterator cbegin() const noexcept {
            return std::cbegin(cascade_);
        }

        /**
         * @brief Returns a constant iterator to the first element of the container.
         * @return Iterator to the first element.
         */
        constexpr const_iterator begin() const noexcept {
            return std::cbegin(cascade_);
        }

        /**
         * @brief Returns a constant iterator to the last element of the container.
         * @return Iterator to the last element.
         */
        constexpr const_iterator cend() const noexcept {
            return std::cbegin(cascade_) + size();
        }

        /**
         * @brief Returns a constant iterator to the last element of the container.
         * @return Iterator to the last element.
         */
        constexpr const_iterator end() const noexcept {
            return std::cbegin(cascade_) + size();
        }

        /**
         * @brief Filters the signal in the range [first, last) and stores the result in another range, beginning at d_first.
         * @tparam InputIt Input iterator holding an arithmetic type.
         * @tparam OutputIt Output iterator holding an arithmetic type.
         * @param first Input iterator defining the beginning of the input range.
         * @param last Input iterator defining the ending of the input range.
         * @param d_first Output iterator defining the beginning of the destination range.
         * @return
         */
        template <typename InputIt, typename OutputIt>
        constexpr void filter(InputIt first, InputIt last, OutputIt d_first) {
            for (; first != last; ++first, ++d_first) {
                *d_first = tick(*first);
            }
        }

        /**
         * @brief Computes the output of filtering one digital time-step.
         * @param value Input value to be filtered.
         * @return Filtered value.
         */
        constexpr value_type tick(value_type value) noexcept {
            for (auto i = 0ul; i < num_stage_; ++i) {
                value = cascade_[i](value);
            }
            return value;
        }

        /**
         * @brief Appends the given Biquad at the end.
         * @param biquad Biquad to append.
         */
        constexpr void push_back(const Biquad<T>& biquad) {
            meta::ensure(num_stage_ < N, "No space available");
            cascade_[num_stage_] = biquad;
            num_stage_++;
        }

        /**
         * @brief Construct a Biquad in-place at the end.
         * @param arg Arguments to forward to the constructor of the element
         */
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
