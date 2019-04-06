/* 
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 * File: ring_buffer.hpp
 * Author Mohammed Boujemaoui Boulaghmoudi on 02/10/18.
 */

#ifndef EDSP_RING_BUFFER_HPP
#define EDSP_RING_BUFFER_HPP

#include <edsp/meta/unused.hpp>
#include <edsp/types/ring_span.hpp>
#include <vector>

namespace edsp { inline namespace types {

    /**
     * @class ring_buffer
     * @brief This class implements a ring buffer, also called circular buffer.
     *
     * The term ring buffer refers to an area in memory which is used to store incoming data. When the buffer is filled,
     * new data is written starting at the beginning of the buffer and overwriting the old.
     *
     * The ring_buffer is a STL compliant container. It supports random access iterators, constant time insert and erase
     * operations at the beginning or the end of the buffer and interoperability with std algorithms.
     *
     * @tparam T  Type of element.
     * @tparam Allocator  Allocator type, defaults to std::allocator<T>.
     */
    // TODO: Check why the default copy constructor is disabled!
    template <typename T, typename Allocator = std::allocator<T>>
    class ring_buffer {
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
        typedef std::vector<T, Allocator> container_type;

        constexpr ring_buffer()                       = default;
        constexpr ring_buffer(const ring_buffer&)     = default;
        constexpr ring_buffer(ring_buffer&&) noexcept = default;
        constexpr ring_buffer& operator=(const ring_buffer&) = default;
        constexpr ring_buffer& operator=(ring_buffer&&) noexcept = default;

        /**
         *  @brief Creates a %ring_buffer with default constructed elements.
         *  @param N The number of elements to initially create.
         *
         *  This constructor fills the %ring_buffer with N default
         *  constructed elements.
         */
        explicit ring_buffer(size_type N) {
            buffer_.resize(N);
            ring_ = edsp::ring_span<T>(std::begin(buffer_), std::end(buffer_));
        }

        /**
         *  @brief  Creates a %ring_buffer with copies of an exemplar element.
         *  @param  N  The number of elements to initially create.
         *  @param  value  An element to copy.
         *  This constructor fills the %ring_buffer with N copies of value.
         */
        ring_buffer(size_type N, const value_type& value) {
            buffer_.resize(N);
            ring_ = edsp::ring_span<T>(std::begin(buffer_), std::end(buffer_), std::begin(buffer_), N);
            std::fill(begin(), end(), value);
        }

        /**
         *  @brief Default destructor.
         *  The dtor only erases the elements, and note that if the
         *  elements themselves are pointers, the pointed-to memory is
         *  not touched in any way.  Managing the pointer is the user's
         *  responsibility.
         */
        ~ring_buffer() = default;

        /**
         *  @brief Resizes the %ring_buffer to the specified number of elements.
         *  @param size Number of elements the %ring_buffer should contain.
         *
         */
        void resize(size_type size) {
            buffer_.resize(size);
            ring_ = edsp::ring_span<T>(std::begin(buffer_), std::end(buffer_));
        }

        /**
         *  Erases all the elements. Note that this function only erases the
         *  elements, and that if the elements themselves are pointers, the
         *  pointed-to memory is not touched in any way.  Managing the pointer is
         *  the user's responsibility.
         */
        void clear() {
            ring_ = edsp::ring_span<T>(std::begin(buffer_), std::end(buffer_), std::begin(buffer_), 0);
        }

        /**
         * @brief Returns a read/write iterator that points to the first
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the first element.
         */
        iterator begin() noexcept {
            return ring_.begin();
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the first element.
         */
        const_iterator begin() const noexcept {
            return ring_.begin();
        }

        /**
         * @brief Returns a read/write iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the last element.
         */
        iterator end() noexcept {
            return ring_.end();
        }

        /**
         * @brief Returns a read-only iterator that points to the last
         * element in the %ring_buffer.
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
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the first element.
         */
        const_reverse_iterator rbegin() const noexcept {
            return ring_.rbegin();
        }

        /**
         * @brief Returns a read/write iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the last element.
         */
        reverse_iterator rend() noexcept {
            return ring_.rend();
        }

        /*
         * @brief Returns a read-only iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the last element.
         */
        const_reverse_iterator rend() const noexcept {
            return ring_.rend();
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the first element.
         */
        const_iterator cbegin() const noexcept {
            return ring_.cbegin();
        }

        /**
         * @brief Returns a read-only te iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the last element.
         */
        const_iterator cend() const noexcept {
            return ring_.cend();
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the first element.
         */
        const_reverse_iterator crbegin() const noexcept {
            return ring_.crbegin();
        }

        /**
         * @brief Returns a read-only iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the last element.
         */
        const_reverse_iterator crend() const noexcept {
            return ring_.crend();
        }

        /**
         * @brief Returns the number of elements in the %ring_buffer.
         * @return Number of elements in the ring_buffer
         */
        constexpr size_type size() const {
            return ring_.size();
        }

        /**
         * Returns the size() of the largest possible %ring_buffer.
         * @return Maximum allowed size.
         */
        constexpr size_type max_size() const {
            return buffer_.max_size();
        }

        /**
         * Returns true if the %ring_buffer is empty.
         * @return true if the ring_buffer is empty, false otherwise.
         */
        constexpr bool empty() const {
            return ring_.empty();
        }

        /**
         * Returns true if the %ring_buffer is full.
         * @return true if the ring_buffer is full, false otherwise.
         */
        constexpr bool full() const {
            return ring_.full();
        }

        /**
         * Returns the total number of elements that the %ring_buffer can hold.
         * @return Number of elements that the ring_buffer can hold.
         */
        constexpr size_type capacity() const {
            return ring_.capacity();
        }

        /**
         *  @brief Subscript access to the data contained in the %ring_buffer.
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
         *  @brief Subscript access to the data contained in the %ring_buffer.
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
         *  @brief Provides access to the data contained in the %ring_buffer.
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
         *  @brief Provides access to the data contained in the %ring_buffer.
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
         *  element of the %ring_buffer.
         *  @returns Reference to the first element in the ring_buffer.
         */
        reference front() {
            return ring_.front();
        }

        /**
         *  @brief Returns a read-only reference to the data at the first
         *  element of the %ring_buffer.
         *  @returns Reference to the first element in the ring_buffer.
         */
        const_reference front() const {
            return ring_.front();
        }

        /**
         *  @brief Returns a read/write reference to the data at the last
         *  element of the %ring_buffer.
         *  @returns Reference to the last element in the ring_buffer.
         */
        reference back() {
            return ring_.back();
        }

        /**
         *  @brief Returns a read-only reference to the data at the last
         *  element of the %ring_buffer.
         *  @returns Reference to the last element in the ring_buffer.
         */
        const_reference back() const {
            return ring_.back();
        }

        /**
         *  @brief Inserts an object at the front of the %ring_buffer.
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
        *  @brief Inserts an object at the end of the %ring_buffer.
        *  @param arg  Arguments.
        *
        *  This function will insert an object of type T constructed
        *  with T(std::forward<Args>(args)...) before the specified location.
        */
        template <typename... Args>
        void emplace_back(Args... arg) {
            ring_.emplace_back(arg...);
        }

        /**
         *  @brief Add data to the end of the %ring_buffer.
         *  @param item  Data to be added.
         *
         *  This is a typical stack operation. The function creates an
         *  element at the end of the %ring_buffer and assigns the given data
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
         *  @brief Removes the last element of the ring_buffer.
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

#endif //EDSP_RING_BUFFER_HPP
