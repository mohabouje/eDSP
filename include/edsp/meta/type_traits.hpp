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
 * File: type_traits.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/9/2018
 */
#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <type_traits>

namespace edsp { namespace meta {

    template <typename T>
    using remove_cv_t = typename std::remove_cv<T>::type;

    template <typename T>
    using remove_const_t = typename std::remove_const<T>::type;

    template <typename T>
    using remove_volatile_t = typename std::remove_volatile<T>::type;

    template <typename T>
    using add_cv_t = typename std::add_cv<T>::type;

    template <typename T>
    using add_const_t = typename std::add_const<T>::type;

    template <typename T>
    using add_volatile_t = typename std::add_volatile<T>::type;

    template <typename T>
    using remove_reference_t = typename std::remove_reference<T>::type;

    template <typename T>
    using add_lvalue_reference_t = typename std::add_lvalue_reference<T>::type;

    template <typename T>
    using add_rvalue_reference_t = typename std::add_rvalue_reference<T>::type;

    template <typename T>
    using remove_pointer_t = typename std::remove_pointer<T>::type;

    template <typename T>
    using add_pointer_t = typename std::add_pointer<T>::type;

    template <typename T>
    using make_signed_t = typename std::make_signed<T>::type;

    template <typename T>
    using make_unsigned_t = typename std::make_unsigned<T>::type;

    template <typename T>
    using remove_extent_t = typename std::remove_extent<T>::type;

    template <typename T>
    using remove_all_extents_t = typename std::remove_all_extents<T>::type;

    template <typename T>
    using decay_t = typename std::decay<T>::type;

    template <bool B, typename T = void>
    using enable_if_t = typename std::enable_if<B, T>::type;

    template <bool B, typename T, typename F>
    using conditional_t = typename std::conditional<B, T, F>::type;

    template <typename... T>
    using common_type_t = typename std::common_type<T...>::type;

    template <typename T>
    using underlying_type_t = typename std::underlying_type<T>::type;

    template <typename T>
    using result_of_t = typename std::result_of<T>::type;

}}     // namespace edsp::meta
#endif // TYPE_TRAITS_HPP
