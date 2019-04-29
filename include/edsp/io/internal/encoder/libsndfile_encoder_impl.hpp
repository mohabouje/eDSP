/*
* eDSP, A cross-platform Digital Signal Processing library written in modern C++.
* Copyright (C) 2019 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
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
* Filename: libsndfile_encoder_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 15/01/19
*/

#ifndef EDSP_LIBSNDFILE_ENCODER_IMPL_HPP
#define EDSP_LIBSNDFILE_ENCODER_IMPL_HPP

#include <edsp/types/string_view.hpp>
#include <edsp/core/logger.hpp>
#include <edsp/meta/is_signed.hpp>
#include <edsp/meta/advance.hpp>
#include <edsp/meta/iterator.hpp>
#include <edsp/meta/is_null.hpp>

#include <sndfile.h>
#include <cmath>

namespace edsp { namespace io {

    inline namespace internal {
        template <typename T>
        struct writer {
            using value_type = T;
        };

        template <>
        struct writer<float> {
            using value_type            = float;
            static constexpr int FORMAT = SF_FORMAT_FLOAT;

            std::ptrdiff_t write(SNDFILE* file, const float* buffer, int length) {
                return sf_write_float(file, buffer, length);
            }
        };

        template <>
        struct writer<double> {
            using value_type            = double;
            static constexpr int FORMAT = SF_FORMAT_DOUBLE;

            std::ptrdiff_t write(SNDFILE* file, const double* buffer, int length) {
                return sf_write_double(file, buffer, length);
            }
        };

        template <>
        struct writer<std::int32_t> {
            using value_type            = int;
            static constexpr int FORMAT = SF_FORMAT_PCM_32;

            std::ptrdiff_t write(SNDFILE* file, const int* buffer, int length) {
                return sf_write_int(file, buffer, length);
            }
        };

        template <>
        struct writer<std::int16_t> {
            using value_type            = short;
            static constexpr int FORMAT = SF_FORMAT_PCM_16;

            std::ptrdiff_t write(SNDFILE* file, const short* buffer, int length) {
                return sf_write_short(file, buffer, length);
            }
        };

    } // namespace internal

    template <typename T>
    struct libsndfile_encoder {
        static_assert(std::is_arithmetic<T>::value, "Expected arithmetic types");

        using size_type  = std::size_t;
        using index_type = std::ptrdiff_t;
        using value_type = T;

        libsndfile_encoder(size_t sample_rate, size_t channels) {
            info_.samplerate = static_cast<int>(sample_rate);
            info_.channels   = static_cast<int>(channels);
            info_.format     = SF_FORMAT_WAV | internal::writer<T>::FORMAT;
        }

        ~libsndfile_encoder() {
            close();
        }

        bool open(const std::string& file_path) {
            close();

            file_ = sf_open(file_path.data(), SFM_WRITE, &info_);
            if (file_ == nullptr) {
                eWarning() << "Could not open file " << file_path;
            }
            return is_open();
        }

        bool is_open() const {
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

        index_type channels() const noexcept {
            return info_.channels;
        }

        double sample_rate() const noexcept {
            return info_.samplerate;
        }

        template <typename OutputIt>
        auto write(OutputIt first, OutputIt last) {
            using value_type = meta::value_type_t<OutputIt>;
            static_assert(std::is_same<value_type, T>::value, "Expecting iterator of the same type");

            const auto length = std::distance(first, last);
            const auto* data  = &(*first);
            return internal::writer<T>{}.write(file_, data, length);
        }

    private:
        using underlying_t = typename internal::writer<T>::value_type;

        /* File descriptor */
        SNDFILE* file_{nullptr};

        /* Information about the file */
        SF_INFO info_{};
    };
}} // namespace edsp::io

#endif //EDSP_LIBSNDFILE_ENCODER_IMPL_HPP
