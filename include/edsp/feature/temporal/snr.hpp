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
* Filename: snr.hpp
* Author: Mohammed Boujemaoui
* Date: 10/10/18
*/

#ifndef EDSP_SNR_HPP
#define EDSP_SNR_HPP

#include <edsp/meta/iterator.hpp>
#include <edsp/statistics/variance.hpp>
#include <edsp/converter/pow2db.hpp>
#include <vector>

namespace edsp { namespace feature { inline namespace temporal {

    /**
     * @brief Compute the SNR of the signals in the range [first1, last1) and the signal starting in first2.
     *
     * Signal-to-noise ratio (abbreviated SNR or S/N) is a measure used in science and engineering that compares
     * the level of a desired signal to the level of background noise. SNR is defined as the ratio of signal power
     * to the noise power, often expressed in decibels. A ratio higher than 1:1 (greater than 0 dB) indicates more
     * signal than noise.
     *
     * If the variance of the signal and noise are known, and the signal and noise are both zero-mean, SNR can be:
     * \f[
     * \mathrm{SNR} = \frac{\sigma^2_\mathrm{signal}}{\sigma^2_\mathrm{noise}}.
     * \f]
     *
     * @param first1 Input iterator defining the beginning of the first input range.
     * @param last1 Input iterator defining the ending of the first input range.
     * @param first2 Input iterator defining the beginning of the second input range.
     * @returns SNR of the signals.
     */
    template <typename InputIt, typename Allocator = std::allocator<meta::value_type_t<InputIt>>>
    constexpr meta::value_type_t<InputIt> snr(InputIt first1, InputIt last1, InputIt first2) {
        using value_type = meta::value_type_t<InputIt>;
        const auto N     = std::distance(first1, last1);
        std::vector<value_type, Allocator> noise(N);
        std::transform(first1, last1, first2, std::begin(noise),
                       [](const value_type left, const value_type right) { return left - right; });

        const auto var_ref   = statistics::variance(first1, first2);
        const auto var_noise = statistics::variance(std::cbegin(noise), std::cend(noise));
        return converter::pow2db(var_ref / var_noise);
    }

}}}    // namespace edsp::feature::temporal
#endif //EDSP_SNR_HPP
