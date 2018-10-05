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
 * Filename: testing_filter.cpp
 * Author: Mohammed Boujemaoui
 * Date: 05/10/2018
 */

#include <easy/dsp/filter.hpp>

template struct easy::dsp::filter::designer<float, easy::dsp::filter::DesignerType::RBJ, 10>;
template struct easy::dsp::filter::designer<float, easy::dsp::filter::DesignerType::Zolzer, 10>;
template struct easy::dsp::filter::designer<float, easy::dsp::filter::DesignerType::Butterworth, 10>;
template struct easy::dsp::filter::designer<float, easy::dsp::filter::DesignerType::ChebyshevI, 10>;
template struct easy::dsp::filter::designer<float, easy::dsp::filter::DesignerType::ChebyshevII, 10>;
template class easy::dsp::filter::moving_median<float>;
template class easy::dsp::filter::moving_average<float>;
template class easy::dsp::filter::moving_rms<float>;


template class easy::dsp::filter::biquad<float>;
template class easy::dsp::filter::biquad_cascade<float, 10>;
