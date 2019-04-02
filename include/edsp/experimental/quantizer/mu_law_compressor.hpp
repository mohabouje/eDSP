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
 * File: mu_law_compressor.hpp
 * Author: Mohammed Boujemaoui
 * Date: 7/9/2018
 */
#ifndef EDSP_MU_LAW_COMPRESSOR_HPP
#define EDSP_MU_LAW_COMPRESSOR_HPP

#include <edsp/meta/expects.hpp>
#include <edsp/math/numeric.hpp>
#include <edsp/meta/iterator.hpp>
#include <algorithm>
#include <functional>

namespace edsp { namespace quantizer {

    /**
     * @brief The \f$ \mu \f$ law converts data in 16-bit linear formats to a 8-bit µ-law format.
     *
     * The compression process is performed as follows:
     * \f[
     * {\displaystyle y=F(x)=\operatorname {sgn}(x){\frac {\ln(1+\mu |x|)}{\ln(1+\mu )}}~~~~-1\leq x\leq 1}
     * \f]
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @param absolute_max_value Maximum value of the input
     * @param compression_factor Compression ratio
     */
    template <typename InputIt, typename OutputIt>
    constexpr void mu_law_compression(InputIt first, InputIt last, OutputIt d_first,
                                      meta::value_type_t<InputIt> absolute_max_value,
                                      meta::diff_type_t<InputIt> compression_factor) {
        meta::expects(absolute_max_value > 0, "Expected a maximum absolute value higher than zero");
        meta::expects(compression_factor > 0, "The compression factor should be a positive number");
        using value_type  = meta::value_type_t<InputIt>;
        const auto lambda = [absolute_max_value](const value_type input) -> value_type {
            const auto ratio = std::fabs(input) / absolute_max_value;
            return math::sign(input) * absolute_max_value *
                   std::log(static_cast<value_type>(1 + compression_factor * ratio)) /
                   std::log(static_cast<value_type>(1 + compression_factor));
        };
        std::transform(first, last, d_first, std::cref(lambda));
    }

    /**
     * @brief The \f$ \mu \f$ law converts data in 8-bit µ-law format to 16-bit linear formats.
     *
     * The de-compression process is performed as follows:
     *
     * \f[
     * {\displaystyle F^{-1}(y)=\operatorname {sgn}(y){1 \over \mu }{\Bigl (}(1+\mu )^{|y|}-1{\Bigr )}~~~~-1\leq y\leq 1}
     * \f]
     *
     * @param first Input iterator defining the beginning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output iterator defining the beginning of the destination range.
     * @param absolute_max_value Maximum value of the input
     * @param compression_factor Compression ratio
     * @return
     */
    template <typename InputIt, typename OutputIt>
    constexpr void inverse_mu_law_compression(InputIt first, InputIt last, OutputIt d_first,
                                              meta::value_type_t<InputIt> absolute_max_value,
                                              meta::diff_type_t<InputIt> compression_factor) {
        meta::expects(absolute_max_value > 0, "Expected a maximum absolute value higher than zero");
        meta::expects(compression_factor > 0, "The compression factor should be a positive number");
        using value_type  = meta::value_type_t<InputIt>;
        const auto lambda = [absolute_max_value](const value_type input) -> value_type {
            const auto ratio = std::fabs(input) / absolute_max_value;
            return math::sign(input) * absolute_max_value *
                   (std::pow(static_cast<value_type>(1 + compression_factor), ratio) - 1) /
                   std::log(static_cast<value_type>(1 + compression_factor));
        };
        std::transform(first, last, d_first, std::cref(lambda));
    }

}} // namespace edsp::quantizer

#endif // EDSP_MU_LAW_COMPRESSOR_HPP
