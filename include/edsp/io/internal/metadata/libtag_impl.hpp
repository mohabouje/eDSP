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

#ifndef EDSP_LIBTAG_IMPL_HPP
#define EDSP_LIBTAG_IMPL_HPP

#include <edsp/meta/data.hpp>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

namespace edsp { namespace io {

    class libtag_metadata {
    public:
        explicit libtag_metadata(const std::string& file) : ref_(meta::data(file)) {}

        std::string title() const {
            return ref_.tag()->title().to8Bit();
        }

        std::string artist() const {
            return ref_.tag()->artist().to8Bit();
        }

        std::string album() const {
            return ref_.tag()->album().to8Bit();
        }

        std::string genre() const {
            return ref_.tag()->genre().to8Bit();
        }

        size_t track() const {
            return ref_.tag()->track();
        }

        size_t year() const {
            return ref_.tag()->year();
        }

    private:
        TagLib::FileRef ref_;
    };

}} // namespace edsp::io

#endif /* EDSP_LIBTAG_IMPL_HPP */
