/* 
 * EasyDSP, just another repository with a bunch of utilities written in modern C++.
 * Copyright (c) 2018  All rights reserved.
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
 * Created by Mohammed Boujemaoui Boulaghmoudi on 02/10/18.
 */

#ifndef EASYDSP_RING_BUFFER_HPP
#define EASYDSP_RING_BUFFER_HPP

#include <vector>
#include <list>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

namespace easy { namespace dsp {

    inline namespace internal {
        template <typename T, typename elem_type = typename T::value_type>
        class ring_buffer_iterator {
        public:
            typedef T ring_buffer_type;

            typedef ring_buffer_iterator<T, elem_type> self_type;

            typedef std::bidirectional_iterator_tag iterator_category;
            typedef elem_type value_type;
            typedef std::size_t size_type;
            typedef std::size_t difference_type;
            typedef value_type* pointer;
            typedef const value_type* const_pointer;
            typedef value_type& reference;
            typedef const value_type& const_reference;

            ring_buffer_iterator(ring_buffer_type* ring_buffer, size_type start_pos) :
                _ring_buffer(ring_buffer),
                _pos(start_pos) {}

            explicit ring_buffer_iterator(const ring_buffer_iterator<typename std::remove_const<T>::type>& other) :
                _ring_buffer(other._ring_buffer),
                _pos(other._pos) {}

            friend class ring_buffer_iterator<const T, const elem_type>;

            elem_type& operator*() {
                return (*_ring_buffer)[_pos];
            }

            elem_type* operator->() {
                return &(operator*());
            }

            self_type& operator++() {
                ++_pos;
                return *this;
            }

            self_type operator++(int) {
                self_type tmp(*this);
                ++(*this);
                return tmp;
            }

            self_type& operator--() {
                --_pos;
                return *this;
            }

            self_type operator--(int) {
                self_type tmp(*this);
                --(*this);
                return tmp;
            }

            self_type operator+(difference_type n) {
                self_type tmp(*this);
                tmp._pos += n;
                return tmp;
            }

            self_type& operator+=(difference_type n) {
                _pos += n;
                return *this;
            }

            self_type operator-(difference_type n) {
                self_type tmp(*this);
                tmp._pos -= n;
                return tmp;
            }

            self_type& operator-=(difference_type n) {
                _pos -= n;
                return *this;
            }

            bool operator==(const self_type& other) const {
                return (_ring_buffer == other._ring_buffer) && (_pos == other._pos);
            }

            bool operator!=(const self_type& other) const {
                return (_ring_buffer != other._ring_buffer) || (_pos != other._pos);
            }

        private:
            ring_buffer_type* _ring_buffer;
            size_type _pos;
        };

    } // namespace internal

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
    template <typename T, typename Allocator = std::allocator<T>>
    class ring_buffer {
    public:
        typedef ring_buffer<T, Allocator> self_type;
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef ring_buffer_iterator<self_type, self_type::value_type> iterator;
        typedef ring_buffer_iterator<const self_type, const self_type::value_type> const_iterator;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        constexpr ring_buffer()                   = default;
        constexpr ring_buffer(const ring_buffer&) = default;
        constexpr ring_buffer(ring_buffer&&)      = default;
        constexpr ring_buffer& operator=(const ring_buffer&) = default;
        constexpr ring_buffer& operator=(ring_buffer&&) = default;


        /**
         *  @brief Creates a %ring_buffer with default constructed elements.
         *  @param N The number of elements to initially create.
         *
         *  This constructor fills the %ring_buffer with N default
         *  constructed elements.
         */
        explicit ring_buffer(size_type N) : buffer_(N) {}


        /**
         *  @brief  Creates a %ring_buffer with copies of an exemplar element.
         *  @param  N  The number of elements to initially create.
         *  @param  value  An element to copy.
         *  This constructor fills the %ring_buffer with N copies of value.
         */
        ring_buffer(size_type N, const value_type& value) : buffer_(N) {
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
         *  Erases all the elements. Note that this function only erases the
         *  elements, and that if the elements themselves are pointers, the
         *  pointed-to memory is not touched in any way.  Managing the pointer is
         *  the user's responsibility.
         */
        void clear() {
            size_ = 0;
            tail_ = 0;
            _head = 1;
        }

        /**
         * @brief Returns a read/write iterator that points to the first
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the first element.
         */
        iterator begin() noexcept {
            return iterator(this, 0);
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the first element.
         */
        const_iterator begin() const noexcept {
            return const_iterator(this, 0);
        }

        /**
         * @brief Returns a read/write iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the last element.
         */
        iterator end() noexcept {
            return iterator(this, size());
        }

        /**
         * @brief Returns a read-only iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the last element.
         */
        const_iterator end() const noexcept {
            return const_iterator(this, size());
        }


        /**
         * @brief Returns a read/write iterator that points to the first
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the first element.
         */
        reverse_iterator rbegin() noexcept {
            return reverse_iterator(end());
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the first element.
         */
        const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(end());
        }

        /**
         * @brief Returns a read/write iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the last element.
         */
        reverse_iterator rend() noexcept {
            return reverse_iterator(begin());
        }

        /**
         * @brief Returns a read-only iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the last element.
         */
        const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(begin());
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the first element.
         */
        const_iterator cbegin() const noexcept {
            return const_iterator(this, 0);
        }

        /**
         * @brief Returns a read-only te iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in ordinary element order.
         * @returns Iterator pointing to the last element.
         */
        iterator cend() noexcept {
            return iterator(this, size());
        }

        /**
         * @brief Returns a read-only iterator that points to the first
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the first element.
         */
        const_reverse_iterator crbegin() const noexcept {
            return const_reverse_iterator(end());
        }

        /**
         * @brief Returns a read-only iterator that points to the last
         * element in the %ring_buffer.
         *
         * Iteration is done in reverse element order.
         * @returns Iterator pointing to the last element.
         */
        const_reverse_iterator crend() const noexcept {
            return const_reverse_iterator(begin());
        }

        /**
         * @brief Returns the number of elements in the %ring_buffer.
         * @return Number of elements in the ring_buffer
         */
        constexpr size_type size() const {
            return size_;
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
            return size() == 0;
        }

        /**
         * Returns true if the %ring_buffer is full.
         * @return true if the ring_buffer is full, false otherwise.
         */
        constexpr bool full() const {
            return size() == capacity();
        }

        /**
         * Returns the total number of elements that the %ring_buffer can hold.
         * @return Number of elements that the ring_buffer can hold.
         */
        constexpr size_type capacity() const {
            return buffer_.size();
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
            return buffer_[_position(i)];
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
            return buffer_[_position(i)];
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
            if (i >= capacity()) {
                throw std::out_of_range("ring_buffer::at");
            }

            return buffer_[_position(i)];
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
            if (i >= capacity()) {
                throw std::out_of_range("ring_buffer::at");
            }

            return buffer_[_position(i)];
        }

        /**
         *  @brief Returns a read/write reference to the data at the first
         *  element of the %ring_buffer.
         *  @returns Reference to the first element in the ring_buffer.
         */
        reference front() {
            return *begin();
        }

        /**
         *  @brief Returns a read-only reference to the data at the first
         *  element of the %ring_buffer.
         *  @returns Reference to the first element in the ring_buffer.
         */
        const_reference front() const {
            return *begin();
        }

        /**
         *  @brief Returns a read/write reference to the data at the last
         *  element of the %ring_buffer.
         *  @returns Reference to the last element in the ring_buffer.
         */
        reference back() {
            return capacity() ? *(end() - 1) : *end();
        }

        /**
         *  @brief Returns a read-only reference to the data at the last
         *  element of the %ring_buffer.
         *  @returns Reference to the last element in the ring_buffer.
         */
        const_reference back() const {
            return capacity() ? *end() - 1 : *end();
        }

        /**
        *  @brief Inserts an object at the end of the %ring_buffer.
        *  @param  args  Arguments.
        *  @return  An iterator that points to the inserted data.
        *
        *  This function will insert an object of type T constructed
        *  with T(std::forward<Args>(args)...) before the specified location.
        */
        template <typename... Args>
        void emplace_back(Args... arg) {
            _increment_tail();
            if (size_ == max_size()) {
                _increment_head();
            }
            buffer_[tail_] = T(arg...);
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
            _increment_tail();
            if (size_ == max_size()) {
                _increment_head();
            }
            buffer_[tail_] = item;
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
            _increment_head();
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
            _increment_tail();
        }


    private:
        std::vector<T, Allocator> buffer_{};
        std::size_t size_ = 0;
        std::size_t tail_ = 0;
        std::size_t _head = 1;

        void _increment_tail() {
            ++tail_;
            ++size_;
            if (tail_ == capacity()) {
                tail_ = 0;
            }
        }

        void _increment_head() {
            ++_head;
            --size_;
            if (_head == capacity()) {
                _head = 0;
            }
        }

        std::size_t _position(std::size_t i) const {
            return (_head + i) % capacity();
        }
    };

}} // namespace easy::dsp

#endif //EASYDSP_RING_BUFFER_HPP
