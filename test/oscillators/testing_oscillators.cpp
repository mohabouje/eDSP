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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: testing_coscillators.cpp
 * Author: Mohammed Boujemaoui
 * Date: 05/10/2018
 */

#include <edsp/oscillator.hpp>

template class edsp::oscillators::square_oscillator<float>;
template class edsp::oscillators::sin_oscillator<float>;
template class edsp::oscillators::triangular_oscillator<float>;
template class edsp::oscillators::sawtooth_oscillator<float>;