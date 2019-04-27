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
* Filename: resampler_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 11/10/18
*/

#ifndef EDSP_RESAMPLER_IMPL_HPP
#define EDSP_RESAMPLER_IMPL_HPP

#if defined(USE_LIBSAMPLERATE)
#    include <edsp/io/internal/resampler/libsamplerate_impl.hpp>
#elif defined(USE_LIBRESAMPLE)
#    include <edsp/io/internal/resampler/libresample_resampler.hpp>
#endif

namespace edsp { namespace io {

#if defined(USE_LIBSAMPLERATE)
    template <typename T>
    using resampler_impl = libsamplerate_impl<T>;
#elif defined(USE_LIBRESAMPLE)
    template <typename T>
    using resampler_impl = libresample_impl<T>;
#else
#    error "Compatible library not found!"
#endif

}} // namespace edsp::io

#endif //EDSP_RESAMPLER_IMPL_HPP
