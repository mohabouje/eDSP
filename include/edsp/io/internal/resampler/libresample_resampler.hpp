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
* Filename: libresample_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 11/10/18
*/

#ifndef EDSP_LIBRESAMPLE_IMPL_HPP
#define EDSP_LIBRESAMPLE_IMPL_HPP

#include <edsp/core/logger.hpp>
#include <libresample.h>

namespace edsp { namespace io { namespace internal {

    namespace implementation {
        struct libresample_implementation {
            using value_type = float;
            using size_type  = long;
            using error_type = int;

            libresample_implementation(size_type channels, int quality, value_type factor);

            ~libresample_implementation();

            template <typename InputIt, typename OutputIt>
            inline size_type process(InputIt first, InputIt last, OutputIt d_first);

            int quality() const;

            error_type reset();

            error_type error() const;

            const char* error_string() const;

            static bool valid_ratio(value_type ratio);

        private:
            void report_error(const char* function_name);

            void* handle_;
            error_type error_{0};
            size_type channels_{0};
            value_type factor_{1.0};
            int quality_{0};
        };

        libresample_implementation::libresample_implementation(long channels, int quality, value_type factor) :
            channels_(channels),
            quality_(quality),
            factor_(factor) {
            handle_ = resample_open((quality == 0), factor, factor);
            report_error(__PRETTY_FUNCTION__);
        }

        libresample_implementation::~libresample_implementation() {
            resample_close(handle_);
        }

        template <typename InputIt, typename OutputIt>
        long libresample_implementation::process(InputIt first, InputIt last, OutputIt d_first) {
            const auto size = std::distance(first, last);
            int sr_used     = 0;
            const auto output_size =
                resample_process(handle_, factor_, &(*first), (int) size, 0, &sr_used, &(*d_first), (int) size);
            report_error(__PRETTY_FUNCTION__);
            return output_size;
        }

        int libresample_implementation::quality() const {
            return quality_;
        }

        int libresample_implementation::reset() {
            report_error(__PRETTY_FUNCTION__);
            return error_;
        }

        int libresample_implementation::error() const {
            return error_;
        }

        const char* libresample_implementation::error_string() const {
            return "";
        }

        bool libresample_implementation::valid_ratio(float ratio) {
            return static_cast<bool>(src_is_valid_ratio(ratio));
        }

        void libresample_implementation::report_error(const char* function_name) {
            if (error_ != 0) {
                eError() << "Error while running" << __PRETTY_FUNCTION__ << ":" << error_string();
            }
        }
    } // namespace implementation

    template <typename T>
    struct libresample_resampler {
        using value_type = float;
        using size_type  = long;
        using error_type = int;

        libresample_resampler(size_type channels, int quality, value_type factor) : impl(channels, quality, factor) {}

        ~libresample_resampler() = default;

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
            return implementation::libresample_implementation::valid_ratio(ratio);
        }

    private:
        implementation::libresample_implementation impl;
        std::vector<typename implementation::libresample_implementation::value_type> input;
        std::vector<typename implementation::libresample_implementation::value_type> output;
    };

    template <>
    struct libresample_resampler<typename implementation::libresample_implementation::value_type> {
        using value_type = float;
        using size_type  = long;
        using error_type = int;

        libresample_resampler(size_type channels, int quality, value_type factor) : impl(channels, quality, factor) {}

        ~libresample_resampler() = default;

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
            return implementation::libresample_implementation::valid_ratio(ratio);
        }

    private:
        implementation::libresample_implementation impl;
    };

}}} // namespace edsp::io::internal

#endif //EDSP_LIBRESAMPLE_IMPL_HPP
