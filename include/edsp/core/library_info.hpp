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
* Filename: library_info.hpp
* Author: Mohammed Boujemaoui
* Date: 09/10/18
*/

#ifndef EDSP_LIBRARY_INFO_HPP
#define EDSP_LIBRARY_INFO_HPP

#include <edsp/core/internal/config.hpp>
#include <edsp/core/logger.hpp>
#include <cstdint>

namespace edsp { inline namespace core {

    enum class fft_lib { fftw, pffft, accelerate, unknown };

    enum class codec_lib { audiofile, sndfile, unknown };

    enum class resample_lib { sample_rate, resample, unknown };

    inline logger& operator<<(logger& stream, fft_lib lib) {
        switch (lib) {
            case fft_lib::fftw:
                return stream << "FFTW";
            case fft_lib::pffft:
                return stream << "PFFFT";
            case fft_lib::accelerate:
                return stream << "Apple Accelerate Framework";
            case fft_lib::unknown:
            default:
                return stream << edsp::red << "not found" << edsp::endc;
        }
    }

    inline logger& operator<<(logger& stream, codec_lib lib) {
        switch (lib) {
            case codec_lib::audiofile:
                return stream << "Audio File Library";
            case codec_lib::sndfile:
                return stream << "Lib SndFile";
            case codec_lib::unknown:
            default:
                return stream << edsp::red << "not found" << edsp::endc;
        }
    }

    inline logger& operator<<(logger& stream, resample_lib lib) {
        switch (lib) {
            case resample_lib::sample_rate:
                return stream << "libsample_rate";
            case resample_lib::resample:
                return stream << "libresample";
            case resample_lib::unknown:
            default:
                return stream << edsp::red << "not found" << edsp::endc;
        }
    }

    struct library_info {
        static constexpr std::int32_t minor_version() noexcept {
            return E_VERSION_MINOR;
        }

        static constexpr std::int32_t major_version() noexcept {
            return E_VERSION_MINOR;
        }

        static constexpr std::int32_t patch_version() noexcept {
            return E_VERSION_PATCH;
        }

        static constexpr const char* version() noexcept {
            return E_VERSION_STR;
        }

        static constexpr const char* build_date() noexcept {
            return E_BUILD_DATE;
        }

        static constexpr const char* build_time() noexcept {
            return E_BUILD_TIME;
        }

        static constexpr fft_lib fft_library() noexcept {
#if defined(USE_LIBFFTW)
            return fft_lib::fftw;
#elif defined(USE_LIBPFFFT)
            return fft_lib::fftw;
#elif defined(USE_LIBACCELERATE)
            return fft_lib::fftw;
#else
            return fft_lib::unknown;
#endif
        }

        static constexpr codec_lib codec_library() noexcept {
#if defined(USE_LIBAUDIOFILE)
            return codec_lib::audiofile;
#elif defined(USE_LIBSNDFILE)
            return codec_lib::sndfile;
#else
            return codec_lib::unknown;
#endif
        }

        static constexpr resample_lib resample_library() noexcept {
#if defined(USE_LIBSAMPLERATE)
            return resample_lib::sample_rate;
#elif defined(USE_LIBRESAMPLE)
            return resample_lib::resample;
#else
            return resample_lib::unknown;
#endif
        }
    };
}} // namespace edsp::core

#endif //EDSP_LIBRARY_INFO_HPP
