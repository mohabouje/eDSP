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
 * Filename: windowing.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EASYDSP_WINDOWING_HPP
#define EASYDSP_WINDOWING_HPP

#include "bartlett.hpp"
#include "blackman.hpp"
#include "flat_top.hpp"
#include "hamming.hpp"
#include "hanning.hpp"
#include "rectangular.hpp"
#include "triangular.hpp"

namespace easy { namespace dsp { namespace windowing {

    template <typename Window, typename... Args>
    Window make_window(Args... arg) {
        return Window(std::forward(arg...));
    }




}}}

#endif // EASYDSP_WINDOWING_HPP
