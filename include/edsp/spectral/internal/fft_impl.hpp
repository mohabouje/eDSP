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
* Filename: fft_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 09/10/18
*/

#ifndef EDSP_FFT_IMPL_HPP
#define EDSP_FFT_IMPL_HPP

#include <edsp/spectral/internal/fftw_impl.hpp>

namespace edsp { inline namespace spectral {

#if defined(USE_FFTW)
    template <typename T>
    using fft_impl = spectral::fftw_impl<T>;
#elif defined(USE_KISS)
# error "Not implemented yet"
#elif defined(USE_APPLE)
#error  "Not implemented yet"
#else
#    error "Library not found"
#endif

}} // namespace edsp::spectral

#endif //EDSP_FFT_IMPL_HPP
