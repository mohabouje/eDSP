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
* Filename: libresample_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 11/10/18
*/

#ifndef EDSP_LIBRESAMPLE_IMPL_HPP
#define EDSP_LIBRESAMPLE_IMPL_HPP

#include <edsp/core/logger.hpp>
#include <libresample.h>

namespace edsp { namespace io {

    template <typename T>
    struct libresample_impl {};

    template <>
    struct libresample_impl<float> {
        using value_type = float;
        using size_type  = long;
        using error_type = int;

        libresample_impl(long channels, int quality, value_type factor) :
            channels_(channels),
            quality_(quality),
            factor_(factor) {
            handle_ = resample_open((quality == 0), factor, factor);
            report_error(__PRETTY_FUNCTION__);
        }

        ~libresample_impl() {
            resample_close(handle_);
        }

        template <typename InputIt, typename OutputIt>
        std::pair<size_type, size_type> process(InputIt first, InputIt last, OutputIt d_first) {
            const auto size = std::distance(first, last);
            int sr_used     = 0;
            const auto output_size =
                resample_process(handle_, factor_, &(*first), (int) size, 0, &sr_used, &(*d_first), (int) size);
            report_error(__PRETTY_FUNCTION__);
            return {size, output_size};
        }

        value_type ratio() const {
            return factor_;
        }

        int quality() const {
            return quality_;
        }

        int reset() {
            report_error(__PRETTY_FUNCTION__);
            return error_;
        }

        int error() const {
            return error_;
        }

        const char* error_string() const {
            static const char* error_message = "Not implemented yet";
            return error_message;
        }

        bool valid_ratio(float ratio) {
            return true;
        }

        size_type channels() const {
            return channels_;
        }

    private:
        void report_error(const char* function_name) {
            if (error_ != 0) {
                eError() << "Error while running" << function_name << ":" << error_string();
            }
        }

        void* handle_{nullptr};
        error_type error_{0};
        size_type channels_{0};
        value_type factor_{1.0};
        int quality_{0};
    };

}} // namespace edsp::io

#endif //EDSP_LIBRESAMPLE_IMPL_HPP
