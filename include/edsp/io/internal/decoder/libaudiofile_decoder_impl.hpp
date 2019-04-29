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
* Filename: audiofile_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 07/10/18
*/

#ifndef EDSP_AUDIOFILE_IMPL_HPP
#define EDSP_AUDIOFILE_IMPL_HPP

#include <edsp/core/logger.hpp>
#include <edsp/meta/is_signed.hpp>
#include <edsp/meta/advance.hpp>
#include <edsp/meta/iterator.hpp>
#include <edsp/meta/data.hpp>
#include <audiofile.h>
#include <cmath>

namespace edsp { namespace io {

    template <typename T, std::ptrdiff_t N = 2048>
    struct libaudiofile_decoder {
        static_assert(std::is_arithmetic<T>::value, "Expected arithmetic types");

        using index_type = std::ptrdiff_t;
        using value_type = T;

        libaudiofile_decoder() = default;

        ~libaudiofile_decoder() {
            close();
        }

        index_type current() const noexcept {
            return static_cast<index_type>(afTellFrame(file_, AF_DEFAULT_TRACK));
        }

        index_type seek(libaudiofile_decoder::index_type position) noexcept {
            return afSeekFrame(file_, AF_DEFAULT_TRACK, position);
        }

        double sample_rate() const noexcept {
            return sample_rate_;
        }

        index_type channels() const noexcept {
            return channels_;
        }

        index_type frames() const noexcept {
            return frames_;
        }

        index_type samples() const noexcept {
            return channels_ * frames_;
        }

        bool is_open() const noexcept {
            return file_ != AF_NULL_FILEHANDLE;
        }

        bool open(const std::string& filepath) {
            close();
            file_ = afOpenFile(filepath.c_str(), "r", NULL);
            if (file_ == AF_NULL_FILEHANDLE) {
                eWarning() << "Could not open file " << filepath;
                return false;
            }

            frames_      = static_cast<index_type>(afGetFrameCount(file_, AF_DEFAULT_TRACK));
            channels_    = static_cast<index_type>(afGetVirtualChannels(file_, AF_DEFAULT_TRACK));
            sample_rate_ = afGetRate(file_, AF_DEFAULT_TRACK);
            update_format();
            return true;
        }

        void close() {
            if (!is_open()) {
                return;
            }

            afCloseFile(file_);
            file_        = AF_NULL_FILEHANDLE;
            channels_    = 0;
            frames_      = 0;
            sample_rate_ = 0;
            frame_size_  = 0;
        }

        template <typename OutputIt>
        index_type read(OutputIt first, OutputIt last) {
            using value_type = meta::value_type_t<OutputIt>;
            static_assert(std::is_same<value_type, underlying_tT>::value, "Expecting iterator of the same type");

            index_type total        = std::distance(first, last);
            index_type remaining    = total;
            index_type samples_read = 0;
            do {
                const auto counter = (remaining > N) ? N : remaining;
                samples_read       = afReadFrames(file_, AF_DEFAULT_TRACK, meta::data(buffer_), (int) counter);
                remaining -= samples_read;
                first = std::copy(std::cbegin(buffer_), std::cbegin(buffer_) + samples_read, first);
            } while (remaining > 0 && samples_read > 0);
            return total - remaining;
        }

        bool seekable() const noexcept {
            return true;
        }

    private:
        void update_format() {
            if (std::is_floating_point<T>::value) {
                if (std::is_same<T, float>::value) {
                    afSetVirtualSampleFormat(file_, AF_DEFAULT_TRACK, AF_SAMPFMT_FLOAT, sizeof(T) * 8);
                } else {
                    afSetVirtualSampleFormat(file_, AF_DEFAULT_TRACK, AF_SAMPFMT_DOUBLE, sizeof(T) * 8);
                }
            } else if (std::is_integral<T>::value) {
                if (meta::is_signed<T>::value) {
                    afSetVirtualSampleFormat(file_, AF_DEFAULT_TRACK, AF_SAMPFMT_TWOSCOMP, sizeof(T) * 8);
                } else {
                    afSetVirtualSampleFormat(file_, AF_DEFAULT_TRACK, AF_SAMPFMT_UNSIGNED, sizeof(T) * 8);
                }
            }

            frame_size_ = afGetVirtualFrameSize(file_, AF_DEFAULT_TRACK, 1);
        }

    private:
        /* Internal buffer used to read data */
        std::array<T, N> buffer_{};

        /* Number of channels */
        index_type channels_{0};

        /* File descriptor */
        AFfilehandle file_{AF_NULL_FILEHANDLE};

        /* Number of available frames */
        index_type frames_{0};

        /* Size of a frame in bytes */
        float frame_size_{0};

        /* Sample rate of the streaming */
        double sample_rate_{0};
    };

}} // namespace edsp::io

#endif //EDSP_AUDIOFILE_IMPL_HPP
