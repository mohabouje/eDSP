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
* Filename: library_info.hpp
* Author: Mohammed Boujemaoui
* Date: 09/10/18
*/

#ifndef EDSP_LIBRARY_INFO_HPP
#define EDSP_LIBRARY_INFO_HPP

#include <edsp/core/internal/config.hpp>
#include <cstdint>

namespace edsp { inline namespace core {

    struct library_info {

        static constexpr std::int32_t minor() noexcept {
            return E_VERSION_MINOR;
        }

        static constexpr std::int32_t major() noexcept {
            return E_VERSION_MINOR;
        }

        static constexpr std::int32_t patch() noexcept {
            return E_VERSION_MINOR;
        }

        static constexpr const char* version() noexcept {
            return E_VERSION_STR;
        }

        static constexpr const char* build_date() noexcept {
            return E_BUILD_DATE;
        }

        static constexpr const char* build_time() noexcept {
            return E_BUILD_TIME;
        }


    };


}}

#endif //EDSP_LIBRARY_INFO_HPP
