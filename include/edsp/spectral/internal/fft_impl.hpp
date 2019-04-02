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
* Filename: fft_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 09/10/18
*/

#ifndef EDSP_FFT_IMPL_HPP
#define EDSP_FFT_IMPL_HPP

#if defined(USE_LIBFFTW)
#    include <edsp/spectral/internal/libfftw_impl.hpp>
#elif defined(USE_LIBPFFFT)
#    include <edsp/spectral/internal/libpffft_impl.hpp>
#endif

namespace edsp { inline namespace spectral { namespace internal {

#if defined(USE_LIBFFTW)
    template <typename T>
    using fft_impl = spectral::fftw_impl<T>;
#elif defined(USE_LIBPFFFT)
    template <typename T>
    using fft_impl = spectral::pffft_impl<T>;
#elif defined(USE_LIBACCELERATE)
#    error "Not implemented yet"
#else
#    error "Library not found"
#endif

}}} // namespace edsp::spectral::internal

#endif //EDSP_FFT_IMPL_HPP
