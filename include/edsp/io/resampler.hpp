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
* Filename: resampler_impl.hpp
* Author: Mohammed Boujemaoui
* Date: 11/10/18
*/

#ifndef EDSP_RESAMPLER_HPP
#define EDSP_RESAMPLER_HPP

#include <edsp/io/internal/resampler/resampler_impl.hpp>

namespace edsp { namespace io {

    /**
     * @brief The resample_quality enum represents the different configurations that modifies the ressampling process
     * based in the output quality.
     */
    enum resample_quality {
        best_quality    = 0,
        medium_quality  = 1,
        sinc_fastest    = 2,
        zero_order_hold = 3,
        linear          = 4,
    };

    /**
     * @class resampler
     * @brief This class implements a resampler object to perform sample-rate conversion.
     *
     * The class resamples an input signal in a factor proportional to the desired sample-rate..
     */
    template <typename T>
    struct resampler {
        using value_type = T;
        using size_type  = long;
        using error_type = int;

        /**
         * @brief Creates a resampler with the given configuration
         * @param channels Number of channels.
         * @param quality  Quality of the resampling process.
         * @param factor   Resampling factor (output sample_rate / input sample_rate)
         */
        resampler(size_type channels, resample_quality quality, value_type factor) : impl(channels, quality, factor) {}

        /**
         * @brief Default destructor
         */
        ~resampler() = default;

        /**
         * @brief Resamples the input elements in the range [first, last) and stores the result in another range,
         * beginning at d_first.
         *
         * The output size is proportional to the input in a factor of \f$ \lambda \f$, where lambda is:
         *
         * \f[
         *  \lambda = \frac{f_{si}}{f_{so}}
         * \f]
         *
         * where \f$ f_{si} \f$  and \f$ f_{so} \f$ are the input size and the output size respectively.
         *
         * @note It is recommended to allocate at least \f$ \lambda N \f$ samples, where \f$ N \f$ is the input size.
         * The user can use the returned counter to resize the output buffer after the processing.
         *
         * @param first Input iterator defining the beginning of the input range.
         * @param last Input iterator defining the ending of the input range.
         * @param d_first Output iterator defining the beginning of the destination range.
         * @return Number of samples computed in the output range.
         */
        template <typename InputIt, typename OutputIt>
        std::pair<size_type, size_type> process(InputIt first, InputIt last, OutputIt d_first) {
            return impl.process(first, last, d_first);
        }

        /**
         * @brief Returns the quality used in the resampling process.
         * @return Resampling quality.
         */
        resample_quality quality() const {
            return static_cast<resample_quality>(impl.quality());
        }

        /**
         * @brief Resets the internal buffers
         * @return Returns non zero on error.
         */
        error_type reset() {
            return impl.reset();
        }

        /**
         * @brief Returns the internal error code.
         * @return Return non zero on error.
         */
        error_type error() const {
            return impl.error();
        }

        /**
         * @brief Returns a description of the internal error code.
         * @return Description of the internal error code.
         */
        const edsp::string_view error_string() const {
            return impl.error_string();
        }

        /**
         * @brief Returns the resampling factor or ratio.
         */
        value_type ratio() const {
            return impl.ratio();
        }

        /**
         * @brief Returns the number of channels
         */
        size_type channels() const {
            return impl.channels();
        }

        /**
         * @brief Checks if a ratio is valid
         * @param ratio Ratio to be tested
         * @return true if the ratio is valid, false otherwise.
         */
        static bool valid_ratio(value_type ratio) {
            return resampler_impl<T>::valid_ratio(ratio);
        }

    private:
        resampler_impl<T> impl;
    };

}} // namespace edsp::io

#endif //EDSP_RESAMPLER_HPP
