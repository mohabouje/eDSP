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
* Filename: decoder_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 09/10/18
*/
#ifndef EDSP_DECODER_IMPL_HPP
#define EDSP_DECODER_IMPL_HPP

#include <edsp/io/internal/audiofile_impl.hpp>
#include <edsp/io/internal/sndfile_impl.hpp>

namespace edsp { namespace io {

#if defined(USE_AUDIOFILE)
    template <typename T, std::size_t N>
    using decoder_impl = audiofile_decoder<T, N>;
#elif defined(USE_SNDFILE)
    template <typename T, std::size_t N>
    using decoder_impl = sndfile_decoder<T, N>;
#else
#    error "Compatible library not found!"
#endif

}} // namespace edsp::io

#endif //EDSP_DECODER_IMPL_HPP
