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
* Filename: rolloff.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_ROLLOFF_HPP
#define EDSP_ROLLOFF_HPP

#include <edsp/feature/temporal/energy.hpp>
#include <iostream>
#include <edsp/math/numeric.hpp>

namespace edsp { namespace feature { inline namespace statistics {

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
    constexpr auto rolloff(ForwardIt first, ForwardIt last, Floating percentage) {
        using value_type  = typename std::iterator_traits<ForwardIt>::value_type;
        const auto energy = feature::energy(first, last);
        const auto size   = static_cast<value_type>(std::distance(first, last));
        const auto limit  = percentage * energy;

        auto position = first;
        for (value_type acc_energy = 0; position != last and acc_energy <= limit; ++position) {
            acc_energy += math::square(*position);
        }
        return static_cast<value_type>(std::distance(first, position) - 1) / size;
    }

}}} // namespace edsp::feature::statistics

#endif //EDSP_ROLLOFF_HPP
