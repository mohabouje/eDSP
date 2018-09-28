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
 * Filename: dct.hpp
 * Created at: 10/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_DCT_HPP
#define EASYDSP_DCT_HPP

#include <easy/meta/iterator.hpp>
#include <easy/dsp/spectral/internal/fftw_impl.hpp>
#include <algorithm>

namespace easy { namespace dsp { inline namespace spectral {

    /**
     * @brief Computes the Discrete-Cosine-Transform of the range [first, last) and stores the result in another range,
     *  beginning at d_first.
     *
     * @param first Input iterator defining the beginnning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output irerator defining the beginning of the destination range.
     * @param type  Discrete cosine transform type
     * @see DCT_Type
     */
    template <typename InputIt, typename OutputIt>
    inline void dct(InputIt first, InputIt last, OutputIt d_first, DCT_Type type = DCT_Type::Type_II) {
        const auto nfft  = static_cast<typename fftw_plan<value_type_t<InputIt>>::size_type>(std::distance(first, last));
        fftw_plan<value_type_t<InputIt>> plan;
        plan.dct(fftw_cast(&(*first)), fftw_cast(&(*d_first)), nfft, type);
    }

    /**
     * @brief Computes the Inverse-Discrete-Cosine-Transform of the range [first, last) and stores the result in another range,
     *  beginning at d_first.
     *
     * @param first Input iterator defining the beginnning of the input range.
     * @param last Input iterator defining the ending of the input range.
     * @param d_first Output irerator defining the beginning of the destination range.
     * @param type  Discrete cosine transform type
     * @see DCT_Type
     */
    template <typename InputIt, typename OutputIt>
    inline void idct(InputIt first, InputIt last, OutputIt d_first, DCT_Type type = DCT_Type::Type_II) {
        const auto nfft  = static_cast<typename fftw_plan<value_type_t<InputIt>>::size_type>(std::distance(first, last));
        fftw_plan<value_type_t<InputIt>> plan;
        plan.idct(fftw_cast(&(*first)), fftw_cast(&(*d_first)), nfft, type);
        plan.idct_scale(fftw_cast(&(*d_first)), nfft, type);
    }

}}} // namespace easy::dsp

#endif // EASYDSP_DCT_HPP
