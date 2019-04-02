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
* Filename: decoder_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 09/10/18
*/
#ifndef EDSP_DECODER_IMPL_HPP
#define EDSP_DECODER_IMPL_HPP

#if defined(USE_LIBAUDIOFILE)
#    include <edsp/io/internal/decoder/libaudiofile_decoder_impl.hpp>
#elif defined(USE_LIBSNDFILE)
#    include <edsp/io/internal/decoder/libsndfile_decoder_impl.hpp>
#endif

namespace edsp { namespace io {

#if defined(USE_LIBAUDIOFILE)
    template <typename T, std::size_t N>
    using decoder_impl = libaudiofile_decoder<T, N>;
#elif defined(USE_LIBSNDFILE)
    template <typename T, std::size_t N>
    using decoder_impl = libsndfile_decoder<T, N>;
#else
#    error "Compatible library not found!"
#endif

}} // namespace edsp::io

#endif //EDSP_DECODER_IMPL_HPP
