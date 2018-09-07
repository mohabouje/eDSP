/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi
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
 * Filename: mu_law_compressor.hpp
 * Author: Mohammed Boujemaoui
 * Date: 7/9/2018
 */
#ifndef EASYDSP_MU_LAW_COMPRESSOR_HPP
#define EASYDSP_MU_LAW_COMPRESSOR_HPP

#include <easy/meta/expects.hpp>
#include <easy/dsp/math/math.hpp>
#include <easy/meta/iterator.hpp>
#include <algorithm>

namespace easy { namespace dsp { namespace quantizer {

    template <typename InputIterator,
              typename OutputIterator>
    constexpr void mu_law_compression(InputIterator first, InputIterator last, OutputIterator out,
                                      value_type_t<Iterator> absolute_max_value,
                                      diff_type_t<Iterator> compression_factor) {
        meta::expects(absolute_max_value > 0, "Expected a maximum absolute value higher than zero");
        meta::expects(compression_factor > 0, "The compression factor should be a positive number");
        using value_type = value_type_t<Iterator>;
        const auto lambda = [absolute_max_value](const value_type input) -> value_type {
            const auto ratio = std::fabs(input) / absolute_max_value;
            return math::sign(input) * absolute_max_value
                    * std::log(static_cast<value_type>(1 + compression_factor * ratio))
                    / std::log(static_cast<value_type>(1 + compression_factor));
        };
        std::transform(first, last, out, std::cref(lambda));
    }

    template <typename InputIterator,
              typename OutputIterator>
    constexpr void inverse_mu_law_compression(InputIterator first, InputIterator last, OutputIterator out,
                                      value_type_t<Iterator> absolute_max_value,
                                      diff_type_t<Iterator> compression_factor) {
        meta::expects(absolute_max_value > 0, "Expected a maximum absolute value higher than zero");
        meta::expects(compression_factor > 0, "The compression factor should be a positive number");
        using value_type = value_type_t<Iterator>;
        const auto lambda = [absolute_max_value](const value_type input) -> value_type {
            const auto ratio = std::fabs(input) / absolute_max_value;
            return math::sign(input) * absolute_max_value
                    * (std::pow(static_cast<value_type>(1 + compression_factor), ratio) - 1)
                    / std::log(static_cast<value_type>(1 + compression_factor));
        };
        std::transform(first, last, out, std::cref(lambda));
    }



}}}


#endif // EASYDSP_MU_LAW_COMPRESSOR_HPP
