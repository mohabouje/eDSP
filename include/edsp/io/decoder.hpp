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
* Filename: decoder.hpp
* Author: Mohammed Boujemaoui
* Date: 07/10/18
*/

#ifndef EDSP_DECODER_HPP
#define EDSP_DECODER_HPP

#include <edsp/types/string_view.hpp>
#include <edsp/io/internal/decoder/decoder_impl.hpp>

namespace edsp { namespace io {

    /**
     * @class decoder
     * @brief This class implements a decoder object to read data from supported audio files.
     *
     * @tparam T Value Type
     * @tparam N Size of the internal buffer.
     */
    template <typename T, std::size_t N = 1024>
    class decoder {
    public:
        using index_type = std::ptrdiff_t;
        using value_type = T;

        explicit decoder() = default;
        ~decoder()         = default;

        /**
         * @brief Opens an audio file.
         * @param file_path Path to the file to be opened.
         * @return true if the file has been opened, false otherwise.
         */
        bool open(const std::string& file_path) {
            return impl_.open(file_path);
        }

        /**
         * @brief Closes the audio file.
         */
        void close() {
            impl_.close();
        }

        /**
         * @brief Checks if the there is an audio file opened.
         * @return true if an audio file has been opened.
         */
        bool is_open() const noexcept {
            return impl_.is_open();
        }

        /**
         * @brief Returns the number of samples in the audio file.
         * @note The number of samples is proportional to the number of channels and frames.
         * @return Number of samples in the audio file.
         */
        index_type samples() const noexcept {
            return impl_.samples();
        }

        /**
         * @brief Returns the number of frames in the audio file.
         *
         * Each sample frame of audio consists of a fixed number of samples (equal to the number of audio channels in
         * the track. For monaural data, a sample frame consists of one audio sample. For stereophonic data, a sample
         * frame consists of a stereo pair.
         *
         * @returns Number of frames in the audio file.
         */
        index_type frames() const noexcept {
            return impl_.frames();
        }

        /**
         * @brief Returns the number of channels in the audio file.
         *
         * The number of channels is a positive integer which specifies the number of interleaved audio channels
         * in the given audio track.
         * @return Number of channels in the audio file.
         */
        index_type channels() const noexcept {
            return impl_.channels();
        }

        /**
         * @brief Returns the sampling rate of the audio file in Hz.
         * @return Sampling rate of the audio file in Hz.
         */
        double sample_rate() const noexcept {
            return impl_.sample_rate();
        }

        /**
         * @brief Checks if the audio file is seekable.
         * @return true if the audio file is seekable, false otherwise.
         */
        bool seekable() const noexcept {
            return impl_.seekable();
        }

        /**
         * @brief Updates the current frame position for a track in an audio file.
         * @param position Frame position in the audio track.
         * @returns On success, returns the frame position in the audio track. On failure,
         * return the value -1
         */
        index_type seek(index_type position) noexcept {
            return impl_.seek(position);
        }

        /**
         * @brief Returns the current frame position of the track in an audio file.
         * @returns On success, returns the frame position in the audio track. On failure,
         * return the value -1
         */
        index_type current() const noexcept {
            return impl_.current();
        }

        /**
         * @brief Attempts to read data from the audio file and stores the results in the range [first, last)
         *
         * The function will try to read up to N samples, where N is the size of the range [first, last).
         *
         * @param d_first Output iterator defining the beginning of the output range.
         * @param d_last Output iterator defining the ending of the output range.
         * @return Number of samples read with success.
         */
        template <typename OutputIt>
        index_type read(OutputIt d_first, OutputIt d_last) {
            return impl_.read(d_first, d_last);
        }

    private:
        decoder_impl<T, N> impl_;
    };
}} // namespace edsp::io

#endif //EDSP_DECODER_HPP
