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
* File: fixed_fixed_ring_buffer.hpp
* Author: Mohammed Boujemaoui
* Date: 07/10/18
*/

#ifndef EDSP_FIXED_RING_BUFFER_HPP
#define EDSP_FIXED_RING_BUFFER_HPP

#include <edsp/meta/unused.hpp>
#include <edsp/types/ring_span.hpp>
#include <array>

namespace edsp { inline namespace types {

    /**
     * @class fixed_ring_buffer
     * @brief This class implements a ring buffer, also called circular buffer.
     *
     * The term ring buffer refers to an area in memory which is used to store incoming data. When the buffer is filled,
     * new data is written starting at the beginning of the buffer and overwriting the old.
     *
     * The fixed_ring_buffer is a STL compliant container. It supports random access iterators, constant time insert and erase
     * operations at the beginning or the end of the buffer and interoperability with std algorithms.
     *
     * @tparam T  Type of element.
     * @tparam Allocator  Allocator type, defaults to std::allocator<T>.
     */
    template <typename T, std::size_t MaxSize>
    class fixed_ring_buffer {
    public:
        typedef typename ring_span<T>::value_type value_type;
        typedef typename ring_span<T>::pointer pointer;
        typedef typename std::add_const_t<pointer> const_pointer;
        typedef typename ring_span<value_type>::reference reference;
        typedef typename ring_span<value_type>::const_reference const_reference;
        typedef typename ring_span<value_type>::iterator iterator;
        typedef typename ring_span<value_type>::const_iterator const_iterator;
        typedef typename ring_span<value_type>::reverse_iterator reverse_iterator;
        typedef typename ring_span<value_type>::const_reverse_iterator const_reverse_iterator;
        typedef typename ring_span<value_type>::size_type size_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::array<T, MaxSize> container_type;

        fixed_ring_buffer()                             = default;
        fixed_ring_buffer(const fixed_ring_buffer&)     = default;
        fixed_ring_buffer(fixed_ring_buffer&&) noexcept = default;
        fixed_ring_buffer& operator=(const fixed_ring_buffer&) = default;
        fixed_ring_buffer& operator=(fixed_ring_buffer&&) noexcept = default;

        /**
         *  @brief Default destructor.
         *  The dtor only erases the elements, and note that if the
         *  elements themselves are pointers, the pointed-to memory is
         *  not touched in any way.  Managing the pointer is the user's
         *  responsibility.
         */
        ~fixed_ring_buffer() = default;

        /**
         *  Erases all the elements. Note that this function only erases the
         *  elements, and that if the elements themselves are pointers, the
         *  pointed-to memory is not touched in any way.  Managing the pointer is
         *  the user's responsibility.
         */
        void clear() {
            ring_ = edsp::ring_span<T>(std::begin(buffer_), std::end(buffer_));
        }

        /**
         * @brief Returns a read/write iterator that points to the first
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the first element.
         */
        iterator begin() noexcept {
            return ring_.begin();
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the first element.
         */
        const_iterator begin() const noexcept {
            return ring_.begin();
        }

        /**
         * @brief Returns a read/write iterator that points to the last
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the last element.
         */
        iterator end() noexcept {
            return ring_.end();
        }

        /**
         * @brief Returns a read-only iterator that points to the last
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the last element.
         */
        const_iterator end() const noexcept {
            return ring_.end();
        }

        /*
         * @brief Returns a read/write iterator that points to the first
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the first element.
         */
        reverse_iterator rbegin() noexcept {
            return ring_.rbegin();
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the first element.
         */
        const_reverse_iterator rbegin() const noexcept {
            return ring_.rbegin();
        }

        /**
         * @brief Returns a read/write iterator that points to the last
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the last element.
         */
        reverse_iterator rend() noexcept {
            return ring_.rend();
        }

        /*
         * @brief Returns a read-only iterator that points to the last
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the last element.
         */
        const_reverse_iterator rend() const noexcept {
            return ring_.rend();
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the first element.
         */
        const_iterator cbegin() const noexcept {
            return ring_.cbegin();
        }

        /**
         * @brief Returns a read-only te iterator that points to the last
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the last element.
         */
        const_iterator cend() const noexcept {
            return ring_.cend();
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the first element.
         */
        const_reverse_iterator crbegin() const noexcept {
            return ring_.crbegin();
        }

        /**
         * @brief Returns a read-only iterator that points to the last
         * element in the %fixed_ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the last element.
         */
        const_reverse_iterator crend() const noexcept {
            return ring_.crend();
        }

        /**
         * @brief Returns the number of elements in the %fixed_ring_buffer.
         * @return Number of elements in the fixed_ring_buffer
         */
        size_type size() const {
            return ring_.size();
        }

        /**
         * Returns the size() of the largest possible %fixed_ring_buffer.
         * @return Maximum allowed size.
         */
        size_type max_size() const {
            return MaxSize;
        }

        /**
         * Returns true if the %fixed_ring_buffer is empty.
         * @return true if the fixed_ring_buffer is empty, false otherwise.
         */
        bool empty() const {
            return ring_.empty();
        }

        /**
         * Returns true if the %fixed_ring_buffer is full.
         * @return true if the fixed_ring_buffer is full, false otherwise.
         */
        bool full() const {
            return ring_.full();
        }

        /**
         * Returns the total number of elements that the %fixed_ring_buffer can hold.
         * @return Number of elements that the fixed_ring_buffer can hold.
         */
        size_type capacity() const {
            return ring_.capacity();
        }

        /**
         *  @brief Subscript access to the data contained in the %fixed_ring_buffer.
         *  @param i The index of the element for which data should be
         *  accessed.
         *  @return  Read/write reference to data.
         *
         *  This operator allows for easy, array-style, data access.
         *  Note that data access with this operator is unchecked and
         *  out_of_range lookups are not defined. (For checked lookups
         *  see at().)
         */
        reference operator[](std::size_t i) {
            return ring_[i];
        }

        /**
         *  @brief Subscript access to the data contained in the %fixed_ring_buffer.
         *  @param i The index of the element for which data should be
         *  accessed.
         *  @return  Read/write reference to data.
         *
         *  This operator allows for easy, array-style, data access.
         *  Note that data access with this operator is unchecked and
         *  out_of_range lookups are not defined. (For checked lookups
         *  see at().)
         */
        const_reference operator[](std::size_t i) const {
            return ring_[i];
        }

        /**
         *  @brief Provides access to the data contained in the %fixed_ring_buffer.
         *  @param i The index of the element for which data should be
         *  accessed.
         *  @return  Read/write reference to data.
         *  @throw  std::out_of_range  If @a __n is an invalid index.
         *
         *  This function provides for safer data access.  The parameter
         *  is first checked that it is in the range of the vector.  The
         *  function throws out_of_range if the check fails.
         */
        reference at(std::size_t i) {
            return ring_.at(i);
        }

        /**
         *  @brief Provides access to the data contained in the %fixed_ring_buffer.
         *  @param i The index of the element for which data should be
         *  accessed.
         *  @return  Read/write reference to data.
         *  @throw  std::out_of_range  If @a __n is an invalid index.
         *
         *  This function provides for safer data access.  The parameter
         *  is first checked that it is in the range of the vector.  The
         *  function throws out_of_range if the check fails.
         */
        const_reference at(std::size_t i) const {
            return ring_.at(i);
        }

        /**
         *  @brief Returns a read/write reference to the data at the first
         *  element of the %fixed_ring_buffer.
         *  @returns Reference to the first element in the fixed_ring_buffer.
         */
        reference front() {
            return ring_.front();
        }

        /**
         *  @brief Returns a read-only reference to the data at the first
         *  element of the %fixed_ring_buffer.
         *  @returns Reference to the first element in the fixed_ring_buffer.
         */
        const_reference front() const {
            return ring_.front();
        }

        /**
         *  @brief Returns a read/write reference to the data at the last
         *  element of the %fixed_ring_buffer.
         *  @returns Reference to the last element in the fixed_ring_buffer.
         */
        reference back() {
            return ring_.back();
        }

        /**
         *  @brief Returns a read-only reference to the data at the last
         *  element of the %fixed_ring_buffer.
         *  @returns Reference to the last element in the fixed_ring_buffer.
         */
        const_reference back() const {
            return ring_.back();
        }

        /**
         *  @brief Inserts an object at the front of the %fixed_ring_buffer.
         *  @param arg  Arguments.
         *  @return  An iterator that points to the inserted data.
         *
         *  This function will insert an object of type T constructed
         *  with T(std::forward<Args>(args)...) before the specified location.
         */
        template <typename... Args>
        void emplace_front(Args... arg) {
            ring_.emplace_front(arg...);
        }

        /**
        *  @brief Inserts an object at the end of the %fixed_ring_buffer.
        *  @param arg  Arguments.
        *  @return  An iterator that points to the inserted data.
        *
        *  This function will insert an object of type T constructed
        *  with T(std::forward<Args>(args)...) before the specified location.
        */
        template <typename... Args>
        void emplace_back(Args... arg) {
            ring_.emplace_back(arg...);
        }

        /**
         *  @brief Add data to the end of the %fixed_ring_buffer.
         *  @param item  Data to be added.
         *
         *  This is a typical stack operation. The function creates an
         *  element at the end of the %fixed_ring_buffer and assigns the given data
         *  to it.
         */
        void push_back(const value_type& item) {
            ring_.push_back(item);
        }

        /**
         *  @brief Removes the first element of the ring.
         *
         *  This is a typical stack operation.
         *
         *  Note that no data is returned, and if the first element's data
         *  is needed, it should be retrieved before pop_front() is
         *  called.
         */
        void pop_front() {
            ring_.pop_front();
        }

        /**
         *  @brief Removes the last element of the fixed_ring_buffer.
         *
         *  This is a typical stack operation.
         *
         *  Note that no data is returned, and if the first element's data
         *  is needed, it should be retrieved before pop_front() is
         *  called.
         */
        void pop_back() {
            ring_.pop_back();
        }

        /**
         * @brief Returns a const reference to the internal buffer
         * @return Internal container.
         */
        const container_type& buffer() const {
            return buffer_;
        }

        /**
         * @brief Returns a const pointer to the underlying data of the internal buffer
         * @return Array holding the internal data.
         */
        const_pointer* data() const {
            return buffer_.data();
        }

    private:
        container_type buffer_{};
        edsp::ring_span<T> ring_{std::begin(buffer_), std::end(buffer_)};
    };

}} // namespace edsp::types

#endif //EDSP_FIXED_RING_BUFFER_HPP
