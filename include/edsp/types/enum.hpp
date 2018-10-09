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
* You should have received a copy of the GNU General Public License along withº
* this program.  If not, see <http://www.gnu.org/licenses/>
*
* Filename: enum.hpp
* Author: Mohammed Boujemaoui
* Date: 09/10/18
*/

#ifndef EDSP_SMART_ENUM_HPP
#define EDSP_SMART_ENUM_HPP

#include <edsp/core/logger.hpp>
#include <edsp/thirdparty/better-enums/enum.h>

#define EDSP_SMART_ENUM(Enum, Underlying, ...)                                     \
    BETTER_ENUM(Enum, Underlying, __VA_ARGS__)                                    \
    edsp::logger& operator<<(edsp::logger& os, const Enum c) {                     \
        return os << c._to_string();                                               \
    }


#endif //EDSP_SMART_ENUM_HPP
