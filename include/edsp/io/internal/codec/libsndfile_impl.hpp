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

        template <>
        struct reader<std::uint32_t> : public reader<std::int32_t> {};

        template <>
        struct reader<std::int64_t> : public reader<std::int32_t> {};

        template <>
        struct reader<std::uint64_t> : public reader<std::int32_t> {};

        template <>
        struct reader<std::uint16_t> : public reader<std::int16_t> {};

        template <>
        struct reader<std::int8_t> : public reader<std::int16_t> {};

        template <>
        struct reader<std::uint8_t> : public reader<std::int16_t> {};

    } // namespace internal

    template <typename T, std::size_t N = 2048>
    struct libsndfile_decoder {
        static_assert(std::is_arithmetic<T>::value, "Expected arithmetic types");

        using index_type = std::ptrdiff_t;
        using value_type = T;

        libsndfile_decoder() = default;
        ~libsndfile_decoder();

        void close();

        bool open(const edsp::string_view& filepath);

        bool is_open() const noexcept;

        index_type samples() const noexcept;

        index_type frames() const noexcept;

        index_type channels() const noexcept;

        double duration() const noexcept;

        double samplerate() const noexcept;

        index_type seek(index_type position) noexcept;

        index_type current() const noexcept;

        bool seekable() const noexcept;

        template <typename OutputIt>
        index_type read(OutputIt first, OutputIt last);

    private:
        using underlying_t = typename reader<T>::value_type;

        /* Internal buffer used to read data */
        std::array<underlying_t, N> buffer_{};

        /* File descriptor */
        SNDFILE* file_{nullptr};

        /* Information about the file */
        SF_INFO info_{};
    };

    template <typename T, size_t N>
    typename libsndfile_decoder<T, N>::index_type libsndfile_decoder<T, N>::current() const noexcept {
        return sf_seek(file_, 0, SEEK_CUR);
    }

    template <typename T, size_t N>
    typename libsndfile_decoder<T, N>::index_type
        libsndfile_decoder<T, N>::seek(libsndfile_decoder::index_type position) noexcept {
        return sf_seek(file_, position, SEEK_SET);
    }

    template <typename T, size_t N>
    double libsndfile_decoder<T, N>::samplerate() const noexcept {
        return info_.samplerate;
    }

    template <typename T, size_t N>
    double libsndfile_decoder<T, N>::duration() const noexcept {
        return static_cast<double>(info_.frames) / info_.samplerate;
    }

    template <typename T, size_t N>
    typename libsndfile_decoder<T, N>::index_type libsndfile_decoder<T, N>::channels() const noexcept {
        return info_.channels;
    }

    template <typename T, size_t N>
    typename libsndfile_decoder<T, N>::index_type libsndfile_decoder<T, N>::frames() const noexcept {
        return info_.frames;
    }

    template <typename T, size_t N>
    typename libsndfile_decoder<T, N>::index_type libsndfile_decoder<T, N>::samples() const noexcept {
        return info_.channels * info_.frames;
    }

    template <typename T, size_t N>
    bool libsndfile_decoder<T, N>::is_open() const noexcept {
        return file_ != nullptr;
    }

    template <typename T, size_t N>
    bool libsndfile_decoder<T, N>::open(const edsp::string_view& filepath) {
        close();
        file_ = sf_open(filepath.data(), SFM_READ, &info_);
        if (meta::is_null(file_)) {
            eWarning() << "Could not open file " << filepath;
            return false;
        }
        return true;
    }

    template <typename T, size_t N>
    void libsndfile_decoder<T, N>::close() {
        if (!is_open()) {
            return;
        }

        sf_close(file_);
    }

    template <typename T, size_t N>
    template <typename OutputIt>
    typename libsndfile_decoder<T, N>::index_type libsndfile_decoder<T, N>::read(OutputIt first, OutputIt last) {
        index_type total        = std::distance(first, last);
        index_type remaining    = total;
        index_type samples_read = 0;
        do {
            const auto expected_samples = (remaining >= N) ? N : remaining;
            const auto expected_frames  = std::trunc(expected_samples / info_.channels);
            const auto frames_read      = internal::reader<T>{}.read(file_, meta::data(buffer_), (int) expected_frames);
            samples_read                = frames_read * info_.channels;
            remaining -= samples_read;
            for (auto i = 0; i < samples_read; ++i, ++first) {
                *first = static_cast<meta::value_type_t<OutputIt>>(buffer_[i]);
            }
        } while (remaining > 0 && samples_read > 0);
        return total - remaining;
    }

    template <typename T, size_t N>
    libsndfile_decoder<T, N>::~libsndfile_decoder() {
        close();
    }

    template <typename T, size_t N>
    bool libsndfile_decoder<T, N>::seekable() const noexcept {
        return static_cast<bool>(info_.seekable);
    }

}} // namespace edsp::io

#endif //EDSP_SNDFILE_IMPL_HPP
