/**
 * Copyright (C) 2019 Mohammed Boujemaoui Boulaghmoudi
 * 
 * This file is part of eDSP.
 * 
 * eDSP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * eDSP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with eDSP.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EDSP_METADATA_IMPL_HPP
#define EDSP_METADATA_IMPL_HPP

#if defined(USE_TAGLIB)
#    include <edsp/io/internal/metadata/libtag_impl.hpp>
#endif

namespace edsp { namespace io {

#if defined(USE_TAGLIB)
    using metadata_impl = libtag_metadata;
#else
#    error "Compatible library not found!"
#endif

}} // namespace edsp::io

#endif /* EDSP_METADATA_IMPL_HPP */
