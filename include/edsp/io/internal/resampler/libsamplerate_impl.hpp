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
* Filename: libsamplerate_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 11/10/18
*/

#ifndef EDSP_LIBSAMPLERATE_IMPL_HPP
#define EDSP_LIBSAMPLERATE_IMPL_HPP

#include <edsp/core/logger.hpp>
#include <samplerate.h>

namespace edsp { namespace io {

    template <typename T>
    struct libsamplerate_impl {};

    template <>
    struct libsamplerate_impl<float> {
        using value_type = float;
        using size_type  = long;
        using error_type = int;

        libsamplerate_impl(long channels, int quality, double factor) :
            channels_(channels),
            quality_(quality),
            ratio_(factor) {
            state_ = src_new(quality, static_cast<int>(channels), &error_);
            report_error(__PRETTY_FUNCTION__);
        }

        ~libsamplerate_impl() {
            src_delete(state_);
        }

        template <typename InputIt, typename OutputIt>
        std::pair<size_type, size_type> process(InputIt first, InputIt last, OutputIt d_first) {
            const auto size          = std::distance(first, last);
            const auto input_frames  = size / channels_;
            const auto output_frames = static_cast<std::size_t>(ratio_ * input_frames);
            data_.input_frames       = input_frames;
            data_.output_frames      = output_frames;
            data_.data_in            = const_cast<value_type*>(&(*first));
            data_.data_out           = &(*d_first);
            data_.src_ratio          = ratio_;
            data_.end_of_input       = 0;
            error_                   = src_process(state_, &data_);
            report_error(__PRETTY_FUNCTION__);
            return {data_.input_frames_used, data_.output_frames_gen};
        }

        int quality() const {
            return quality_;
        }

        value_type ratio() const {
            return ratio_;
        }

        size_type channels() const {
            return channels_;
        }

        error_type reset() {
            error_ = src_reset(state_);
            report_error(__PRETTY_FUNCTION__);
            return error_;
        }

        error_type error() const {
            return error_;
        }

        const char* error_string() const {
            return src_strerror(error_);
        }

        static bool valid_ratio(double ratio) {
            return static_cast<bool>(src_is_valid_ratio(ratio));
        }

    private:
        void report_error(const char* function_name) {
            if (error_ != 0) {
                eError() << "Error while running" << function_name << ":" << error_string();
            }
        }

        SRC_DATA data_{};
        SRC_STATE* state_{nullptr};
        error_type error_{0};
        size_type channels_{0};
        int quality_{SRC_SINC_MEDIUM_QUALITY};
        double ratio_{1};
    };

}} // namespace edsp::io

#endif //EDSP_LIBSAMPLERATE_IMPL_HPP
