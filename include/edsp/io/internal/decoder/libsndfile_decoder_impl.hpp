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
* Filename: sndfile_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 07/10/18
*/

#ifndef EDSP_SNDFILE_IMPL_HPP
#define EDSP_SNDFILE_IMPL_HPP

#include <edsp/types/string_view.hpp>
#include <edsp/core/logger.hpp>
#include <edsp/meta/is_signed.hpp>
#include <edsp/meta/advance.hpp>
#include <edsp/meta/iterator.hpp>
#include <sndfile.h>
#include <cmath>
#include <edsp/meta/is_null.hpp>

namespace edsp { namespace io {

    inline namespace internal {
        template <typename T>
        struct reader {
            using value_type = T;
        };

        template <>
        struct reader<float> {
            using value_type = float;
            std::ptrdiff_t read(SNDFILE* file, float* buffer, int length) {
                return sf_read_float(file, buffer, length);
            }
        };

        template <>
        struct reader<double> {
            using value_type = double;
            std::ptrdiff_t read(SNDFILE* file, double* buffer, int length) {
                return sf_read_double(file, buffer, length);
            }
        };

        template <>
        struct reader<std::int32_t> {
            using value_type = int;
            std::ptrdiff_t read(SNDFILE* file, int* buffer, int length) {
                return sf_read_int(file, buffer, length);
            }
        };

        template <>
        struct reader<std::int16_t> {
            using value_type = short;
            std::ptrdiff_t read(SNDFILE* file, short* buffer, int length) {
                return sf_read_short(file, buffer, length);
            }
        };

    } // namespace internal

    template <typename T, std::ptrdiff_t N = 2048>
    struct libsndfile_decoder {
        static_assert(std::is_arithmetic<T>::value, "Expected arithmetic types");
        using index_type = std::ptrdiff_t;
        using value_type = T;

        libsndfile_decoder() = default;
        ~libsndfile_decoder() {
            close();
        }

        bool open(const std::string& filepath) {
            close();

            file_ = sf_open(filepath.c_str(), SFM_READ, &info_);
            if (meta::is_null(file_)) {
                eWarning() << "Could not open file " << filepath;
            }
            return is_open();
        }

        bool is_open() const noexcept {
            return file_ != nullptr;
        }

        void close() {
            if (!is_open()) {
                return;
            }

            sf_close(file_);
        }

        const edsp::string_view& error() const {
            return sf_strerror(file_);
        }

        index_type samples() const noexcept {
            return info_.channels * info_.frames;
        }

        index_type frames() const noexcept {
            return info_.frames;
        }

        index_type channels() const noexcept {
            return info_.channels;
        }

        double sample_rate() const noexcept {
            return info_.samplerate;
        }

        index_type seek(libsndfile_decoder::index_type position) noexcept {
            return sf_seek(file_, position, SEEK_SET);
        }

        index_type current() const noexcept {
            return sf_seek(file_, 0, SEEK_CUR);
        }

        bool seekable() const noexcept {
            return static_cast<bool>(info_.seekable);
        }

        template <typename OutputIt>
        index_type read(OutputIt first, OutputIt last) {
            using value_type = meta::value_type_t<OutputIt>;
            static_assert(std::is_same<value_type, underlying_t>::value, "Expecting iterator of the same type");

            index_type total        = std::distance(first, last);
            index_type remaining    = total;
            index_type samples_read = 0;
            do {
                const auto counter = (remaining > N) ? N : remaining;
                samples_read       = internal::reader<T>{}.read(file_, meta::data(buffer_), counter);
                remaining -= samples_read;
                first = std::copy(std::cbegin(buffer_), std::cbegin(buffer_) + samples_read, first);
            } while (remaining > 0 && samples_read > 0);
            return total - remaining;
        }

    private:
        using underlying_t = typename reader<T>::value_type;

        /* Internal buffer used to read data */
        std::array<underlying_t, N> buffer_{};

        /* File descriptor */
        SNDFILE* file_{nullptr};

        /* Information about the file */
        SF_INFO info_{};
    };

}} // namespace edsp::io

#endif //EDSP_SNDFILE_IMPL_HPP
