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
 * File: crest.hpp
 * Author: Mohammed Boujemaoui
 * Date: 14/6/2018
 */
#ifndef EDSP_STATISTICAL_CREST_HPP
#define EDSP_STATISTICAL_CREST_HPP

#include <edsp/statistics/mean.hpp>
#include <edsp/statistics/max.hpp>

namespace edsp { namespace feature { inline namespace statistics {

    /**
     * @brief Computes the crest value of the range [first, last)
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The crest value of the input range.
     */
    template <typename ForwardIt>
    constexpr auto crest(ForwardIt first, ForwardIt last) {
        using value_type = typename std::iterator_traits<ForwardIt>::value_type;
        const auto computed_accumulative =
            std::accumulate(first, last, static_cast<value_type>(0),
                            [](const auto prev, const auto current) { return prev + std::abs(current); });
        const auto computed_max = edsp::statistics::maxabs(first, last);
        return computed_max / computed_accumulative;
    }

}}} // namespace edsp::feature::statistics

#endif // EDSP_STATISTICAL_CREST_HPP
