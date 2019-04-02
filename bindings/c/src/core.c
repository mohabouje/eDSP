/**
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
* Filename: version.c
* Author: Mohammed Boujemaoui
* Date: 2019-03-31
*/

#include "cedsp/core.h"
#include <edsp/core/library_info.hpp>
#include <edsp/core/system.hpp>
#include <edsp/meta/data.hpp>


int get_minor_version() {
    return edsp::library_info::minor_version();
}

int get_major_version() {
    return edsp::library_info::major_version();
}

int get_patch_version() {
    return edsp::library_info::patch_version();
}

const char *get_version() {
    return edsp::library_info::version();
}

const char *get_build_date() {
    return edsp::library_info::build_time();
}

const char *get_build_time() {
    return edsp::library_info::build_time();
}

const char *get_fft_library() {
    const auto fft = edsp::library_info::fft_library();
    switch (fft) {
        case edsp::core::fft_lib::fftw: return "fftw";
        case edsp::core::fft_lib::pffft: return "pffft";
        case edsp::core::fft_lib::accelerate: return "accelerate";
        case edsp::core::fft_lib::unknown: return "unknown";
    }
    return "";
}

const char *get_codec_library() {
    const auto codec = edsp::library_info::codec_library();
    switch (codec) {
        case edsp::core::codec_lib::audiofile: return "audiofile";
        case edsp::core::codec_lib::sndfile:  return "sndfile";
        case edsp::core::codec_lib::unknown:  return "unknown";
    }
    return "";
}
const char *get_resample_library() {
    const auto resample = edsp::library_info::resample_library();
    switch (resample) {
        case edsp::core::resample_lib::sample_rate:  return "samplerate";;
        case edsp::core::resample_lib::resample:  return "resample";;
        case edsp::core::resample_lib::unknown:  return "unknown";;
    }
    return "";
}

const char *get_environment(const char *tag, int *error) {
    const auto expect = edsp::system_env::get_env(tag);
    const char* result = nullptr;
    if (expect) {
        result = edsp::meta::data(expect.value());
        if (error) {
            *error = 0;
        }
    } else {
        if (error) {
            *error = static_cast<int>(expect.error());
        }
    }
    return result;
}

int set_environment(const char *tag, const char *data) {
    return static_cast<int>(edsp::system_env::set_env(tag, data));
}

int exist_environment(const char *tag) {
    return edsp::system_env::exist(tag);
}

