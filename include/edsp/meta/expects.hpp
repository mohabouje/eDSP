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
 * File: expects.hpp
 * Author: Mohammed Boujemaoui
 * Date: 2018-07-29
 */

#ifndef EDSP_META_EXPECTS_H
#define EDSP_META_EXPECTS_H

#include <edsp/core/logger.hpp>
#include <edsp/meta/data.hpp>
#include <edsp/meta/unused.hpp>
#include <cassert>
#include <string>

namespace edsp { namespace meta {

    constexpr void expects(bool condition) {
        meta::unused(condition);
        assert(condition);
    }

    constexpr void expects(bool condition, const edsp::string_view& msg) {
        if (!condition) {
            eCritical() << msg;
        }
        assert(condition && msg.data());
    }

}} // namespace edsp::meta

#endif
