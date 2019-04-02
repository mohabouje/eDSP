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
* File: string_view.hpp
* Author: Mohammed Boujemaoui
* Date: 07/10/18
*/

#ifndef EDSP_STRING_VIEW_HPP
#define EDSP_STRING_VIEW_HPP

#include <edsp/thirdparty/nonstd/string_view.hpp>

namespace edsp { inline namespace types {

    using nonstd::string_view;

    template <typename Char>
    using basic_string_view = nonstd::basic_string_view<Char>;

}} // namespace edsp::types

#endif //EDSP_STRING_VIEW_HPP
