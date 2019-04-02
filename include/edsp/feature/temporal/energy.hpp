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
* Filename: energy.hpp
* Author: Mohammed Boujemaoui
* Date: 12/10/18
*/

#ifndef EDSP_ENERGY_HPP
#define EDSP_ENERGY_HPP

#include <iterator>
#include <numeric>

namespace edsp { namespace feature { inline namespace temporal {

    /**
     * @brief Computes the energy of the elements in the range [first, last)
     *
     * The energy estimates the signal power at a given time, it is estimated directly
     * from the signal frame around a given time:
     *
     * \f[
     * e = \sum\limits_{n=0}^{N-1} x^2(n)
     * \f]
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The energy of the elements in the range.
     */
    template <typename ForwardIt>
    constexpr auto energy(ForwardIt first, ForwardIt last) {
        using value_type = typename std::iterator_traits<ForwardIt>::value_type;
        return std::inner_product(first, last, first, static_cast<value_type>(0));
    }
}}} // namespace edsp::feature::temporal

#endif //EDSP_ENERGY_HPP
