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
 * File: is_iterator.hpp
 * Author: Mohammed Boujemaoui
 * Date: 31/7/2018
 */
#ifndef EDSP_META_IS_ITERATOR_HPP
#define EDSP_META_IS_ITERATOR_HPP

#include <iterator>

namespace edsp { namespace meta {

    template <typename T>
    struct is_iterator {
        static char test(...);

        template <typename U, typename = typename std::iterator_traits<U>::difference_type,
                  typename = typename std::iterator_traits<U>::pointer,
                  typename = typename std::iterator_traits<U>::reference,
                  typename = typename std::iterator_traits<U>::value_type,
                  typename = typename std::iterator_traits<U>::iterator_category>
        static long test(U&&);

        constexpr static bool value = std::is_same<decltype(test(std::declval<T>())), long>::value;
    };

    template <typename T>
    constexpr bool is_iterator_v = is_iterator<T>::value;

    template <typename T, typename = typename std::enable_if<is_iterator<T>::value>::type>
    using is_input_iterator =
        std::is_same<typename std::iterator_traits<T>::iterator_category, std::input_iterator_tag>;

    template <typename T>
    constexpr bool is_input_iterator_v = is_input_iterator<T>::value;

    template <typename T, typename = typename std::enable_if<is_iterator<T>::value>::type>
    using is_output_iterator =
        std::is_same<typename std::iterator_traits<T>::iterator_category, std::output_iterator_tag>;

    template <typename T>
    constexpr bool is_output_iterator_v = is_output_iterator<T>::value;

    template <typename T, typename = typename std::enable_if<is_iterator<T>::value>::type>
    using is_forward_iterator =
        std::is_same<typename std::iterator_traits<T>::iterator_category, std::forward_iterator_tag>;

    template <typename T>
    constexpr bool is_forward_iterator_v = is_forward_iterator<T>::value;

    template <typename T, typename = typename std::enable_if<is_iterator<T>::value>::type>
    using is_bidirectional_iterator =
        std::is_same<typename std::iterator_traits<T>::iterator_category, std::bidirectional_iterator_tag>;

    template <typename T>
    constexpr bool is_bidirectional_iterator_v = is_bidirectional_iterator<T>::value;

    template <typename T, typename = typename std::enable_if<is_iterator<T>::value>::type>
    using is_random_access_iterator =
        std::is_same<typename std::iterator_traits<T>::iterator_category, std::random_access_iterator_tag>;

    template <typename T>
    constexpr bool is_random_access_iterator_v = is_random_access_iterator<T>::value;

}} // namespace edsp::meta

#endif // EDSP_META_IS_ITERATOR_HPP
