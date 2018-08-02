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
 * Filename: levinson.hpp
 * Author: Mohammed Boujemaoui
 * Date: 1/8/2018
 */
#ifndef EASYDSP_LEVINSON_HPP
#define EASYDSP_LEVINSON_HPP

#include <easy/meta/expects.hpp>
#include <easy/meta/advance.hpp>
#include <easy/meta/complex.hpp>
#include <easy/meta/data.hpp>
#include <easy/meta/math.hpp>

#include <algorithm>
#include <vector>
#include <math.h>
#include <complex.h>

namespace easy { namespace dsp { namespace math {

    template <typename InputIterator, typename Integer, typename OutputIterator,
              typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    constexpr value_type levinson(InputIterator first, InputIterator last, Integer order, OutputIterator out) {
        const auto size = std::distance(first, last);
        meta::expects(size >= order, "The input array should be bigger than the order");
        meta::expects(order > 0, "Order must be a positive number");
        std::fill(out, out + (order + 1), static_cast<value_type>(0));
        std::vector<value_type> temp_buffer(order + 1, 0);

        value_type* temp = meta::data(temp_buffer);
        value_type* r    = &(*first);
        value_type* lpc  = &(*out);
        value_type E     = r[0];
        lpc[0]           = 1;

        for (std::size_t i = 1, until = (order + 1); i < until; ++i) {
            auto k = r[i];
            for (std::size_t j = 1; j < i; j++) {
                k += r[i - j] * lpc[j];
            }

            k /= E;
            lpc[i] = -k;

            for (std::size_t j = 1; j < i; j++) {
                temp[j] = lpc[j] - k * lpc[i - j];
            }

            std::copy(temp, temp + i, lpc);
            E *= (1 - meta::square(k));
        }

        return E;
    }

}}} // namespace easy::dsp::math

#endif // EASYDSP_LEVINSON_HPP
