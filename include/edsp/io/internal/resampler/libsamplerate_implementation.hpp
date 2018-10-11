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
* Filename: libsamplerate_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 11/10/18
*/

#ifndef EDSP_LIBSAMPLERATE_IMPL_HPP
#define EDSP_LIBSAMPLERATE_IMPL_HPP

#include <edsp/core/logger.hpp>
#include <samplerate.h>

namespace edsp { namespace io { namespace internal {

    inline namespace implementation {
        struct libsamplerate_implementation {
            using value_type = float;
            using size_type  = long;
            using error_type = int;

            libsamplerate_implementation(size_type channels, int quality, value_type factor);

            ~libsamplerate_implementation();

            template <typename InputIt, typename OutputIt>
            inline size_type process(InputIt first, InputIt last, OutputIt d_first);

            int quality() const;

            error_type reset();

            error_type error() const;

            const char* error_string() const;

            static bool valid_ratio(value_type ratio);

        private:
            void report_error(const char* function_name);

            SRC_DATA data_{};
            SRC_STATE* state_{nullptr};
            error_type error_{0};
            size_type channels_{0};
            int quality_{SRC_SINC_MEDIUM_QUALITY};
            value_type factor_{1};
        };

        libsamplerate_implementation::libsamplerate_implementation(long channels, int quality, value_type factor) :
            channels_(channels),
            quality_(quality),
            factor_(factor) {
            const auto quality_value = static_cast<std::underlying_type<int>::type>(quality);
            state_                   = src_new(quality_value, static_cast<int>(channels), &error_);
            report_error(__PRETTY_FUNCTION__);
        }

        libsamplerate_implementation::~libsamplerate_implementation() {
            src_delete(state_);
        }

        template <typename InputIt, typename OutputIt>
        long libsamplerate_implementation::process(InputIt first, InputIt last, OutputIt d_first) {
            const auto size         = std::distance(first, last);
            data_.input_frames      = size / channels_;
            data_.output_frames     = size / channels_;
            data_.data_in           = &(*first);
            data_.data_out          = &(*d_first);
            data_.src_ratio         = factor_;
            data_.input_frames_used = 0;
            data_.output_frames_gen = 0;
            data_.end_of_input      = 0;
            error_                  = src_process(state_, &data_);
            report_error(__PRETTY_FUNCTION__);
            return data_.output_frames_gen * channels_;
        }

        int libsamplerate_implementation::quality() const {
            return quality_;
        }

        int libsamplerate_implementation::reset() {
            error_ = src_reset(state_);
            report_error(__PRETTY_FUNCTION__);
            return error_;
        }

        int libsamplerate_implementation::error() const {
            return error_;
        }

        const char* libsamplerate_implementation::error_string() const {
            return src_strerror(error_);
        }

        bool libsamplerate_implementation::valid_ratio(float ratio) {
            return static_cast<bool>(src_is_valid_ratio(ratio));
        }

        void libsamplerate_implementation::report_error(const char* function_name) {
            if (error_ != 0) {
                eError() << "Error while running" << __PRETTY_FUNCTION__ << ":" << error_string();
            }
        }
    } // namespace implementation

    template <typename T>
    struct libsamplerate_resampler {
        using value_type = float;
        using size_type  = long;
        using error_type = int;

        libsamplerate_resampler(size_type channels, int quality, value_type factor) : impl(channels, quality, factor) {}

        ~libsamplerate_resampler() = default;

        template <typename InputIt, typename OutputIt>
        inline size_type process(InputIt first, InputIt last, OutputIt d_first) {
            const auto size = static_cast<std::size_t>(std::distance(first, last));
            input.resize(size);
            output.resize(size);

            std::copy(first, last, std::begin(input));
            const auto result = impl.process(std::cbegin(input), std::cend(input), std::begin(output));
            std::copy(std::cbegin(output), std::cend(output), d_first);
            return result;
        };

        int quality() const {
            return impl.quality();
        }

        error_type reset() {
            return impl.reset();
        }

        error_type error() const {
            return impl.error();
        }

        const edsp::string_view error_string() const {
            return impl.error_string();
        }

        static bool valid_ratio(value_type ratio) {
            return implementation::libsamplerate_implementation::valid_ratio(ratio);
        }

    private:
        implementation::libsamplerate_implementation impl;
        std::vector<typename libsamplerate_implementation::value_type> input;
        std::vector<typename libsamplerate_implementation::value_type> output;
    };

    template <>
    struct libsamplerate_resampler<typename implementation::libsamplerate_implementation::value_type> {
        using value_type = float;
        using size_type  = long;
        using error_type = int;

        libsamplerate_resampler(size_type channels, int quality, value_type factor) : impl(channels, quality, factor) {}

        ~libsamplerate_resampler() = default;

        template <typename InputIt, typename OutputIt>
        inline size_type process(InputIt first, InputIt last, OutputIt d_first) {
            return impl.process(first, last, d_first);
        };

        int quality() const {
            return impl.quality();
        }

        error_type reset() {
            return impl.reset();
        }

        error_type error() const {
            return impl.error();
        }

        const edsp::string_view error_string() const {
            return impl.error_string();
        }

        static bool valid_ratio(value_type ratio) {
            return implementation::libsamplerate_implementation::valid_ratio(ratio);
        }

    private:
        implementation::libsamplerate_implementation impl;
    };

}}} // namespace edsp::io::internal

#endif //EDSP_LIBSAMPLERATE_IMPL_HPP
