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
* Filename: power.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_POWER_HPP
#define EDSP_POWER_HPP

#include <edsp/feature/temporal/energy.hpp>

namespace edsp { namespace feature { inline namespace temporal {

    /**
     * @brief Computes the instant power of the elements in the range [first, last)
     *
     * The instant power can be computed as follows:
     * \f[
     * P_x = \frac{1}{N} \sum\limits_{n=0}^{N-1} x^2(n)
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The instant power of the elements in the range.
     * @see energy
     */
    template <typename ForwardIt>
    constexpr auto power(ForwardIt first, ForwardIt last) {
        using value_type = typename std::iterator_traits<ForwardIt>::value_type;
        const auto size  = std::distance(first, last);
        return energy(first, last) / static_cast<value_type>(size);
    }
}}} // namespace edsp::feature::temporal

#endif //EDSP_POWER_HPP
