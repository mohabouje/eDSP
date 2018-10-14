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
* Filename: rolloff.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_ROLLOFF_HPP
#define EDSP_ROLLOFF_HPP

#include <edsp/feature/temporal/energy.hpp>

namespace edsp { namespace statistics {

    /**
     * @brief Computes the roll-off index of the elements in the range [first, last)
     *
     * The roll-off index is defined as the index under which some percentage (cutoff) of the total energy of
     * the signal is contained.
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @param percentage Number between [0, 1] representing the percentage of the total energy of the roll-off index..
     * @returns The estimated roll-off index.
     */
    template <typename ForwardIt, typename Floating>
    constexpr meta::value_type_t<ForwardIt> rolloff(ForwardIt first, ForwardIt last, Floating percentage) {
        using input_t         = meta::value_type_t<ForwardIt>;
        const auto energy = statistics::energy(first, last);
        const auto limit = percentage * energy;
        for (input_t acc_energy = 0; first != last; ++first) {
            acc_energy += (*first) * (*first);
            if (acc_energy >= limit)
                return first;
        }
        return last;
    }

}} // namespace edsp::statistics


#endif //EDSP_ROLLOFF_HPP
