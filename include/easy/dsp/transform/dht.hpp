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
 * Filename: dht.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_DHT_HPP
#define EASYDSP_DHT_HPP

#include "fftw_impl.hpp"

namespace easy { namespace dsp {

    template <typename InputIterator, typename OutputIterator>
    inline void dht(InputIterator first, InputIterator last, OutputIterator out) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        fftw_plan<value_type> plan;
        plan.dht(fftw_cast(&(*first)), fftw_cast(&(*out)),
                 static_cast<typename fftw_plan<value_type>::size_type>(std::distance(first, last)));
    };

    template <typename Container>
    inline void dht(const Container& input, Container& output) {
        dht(std::cbegin(input), std::cend(input), std::begin(output));
    };

}} // namespace easy::dsp

#endif // EASYDSP_DHT_HPP
