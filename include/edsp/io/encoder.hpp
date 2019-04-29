/*
* edsp, A cross-platform Digital Signal Processing library written in modern C++.
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
* Filename: encoder.hpp
* Author: Mohammed Boujemaoui
* Date: 15/01/19
*/

#ifndef EDSP_ENCODER_HPP
#define EDSP_ENCODER_HPP

#include <edsp/types/string_view.hpp>
#include <edsp/io/internal/encoder/encoder_impl.hpp>

namespace edsp { namespace io {

    /**
     * @class encoder
     * @brief This class implements a encoder object to write data in a supported audio format.
     *
     * @tparam T Value Type
     */
    template <typename T>
    class encoder {
    public:
        using index_type = std::ptrdiff_t;
        using value_type = T;

        encoder(size_t sample_rate, size_t channels) : impl_(sample_rate, channels) {}
        ~encoder() = default;

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
         * @brief Attempts to write data in the audio file from the elements in the range [first, last)
         * @param first Input iterator defining the beginning of the input range.
         * @param last Input iterator defining the ending of the input range.
         */
        template <typename InputIt>
        auto write(InputIt first, InputIt last) {
            return impl_.write(first, last);
        }

    private:
        encoder_impl<T> impl_;
    };
}} // namespace edsp::io

#endif //EDSP_ENCODER_HPP
