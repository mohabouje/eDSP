/* 
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 * File: types.hpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 03/10/18.
 */

#ifndef EASYDSP_TYPES_HPP
#define EASYDSP_TYPES_HPP

namespace edsp { inline namespace spectral {

    /**
    * @brief The SpectralScale enum represent the scale used to
    * represent the power spectral density
    */
    enum class SpectralScale {
        Linear,     /*!< Linear scale */
        Logarithmic /*!< Logarithmic scale */
    };

    /**
    * @brief The ScaleOpt enum defines the normalization option of the correlation function.
    */
    enum class CorrelationScale {
        None,    /*!< Raw, unscaled cross-correlation. */
        Biased,  /*!< Biased estimate of the cross-correlation. */
        Unbiased /*!< Unbiased estimate of the cross-correlation. */
    };

    /**
    * @brief The DCT_Type enum represents the different implementations to compute the DCT
    */
    enum class DCT_Type { Type_I, Type_II, Type_III, Type_IV };
}} // namespace edsp::spectral

#endif //EASYDSP_TYPES_HPP
