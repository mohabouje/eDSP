/**
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (c) 2018 All rights reserved.
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
 *
 * File: loudness.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_LOUDNESS_HPP
#define EDSP_LOUDNESS_HPP

#include <edsp/feature/temporal/energy.hpp>
#include <cmath>

namespace edsp { namespace feature { inline namespace perceptual {

    /**
     * @brief Computes the loudness of the elements in the range [first, last)
     *
     * The loudness is estimated with the Steven's Power Law. S.S. Stevens proposed a new law to relate sensation
     * magnitude to stimulus intensity.
     *
     * \f[
     *  S = k I^{\alpha}
     * \f]
     *
     * where:
     *  - S is the sensation magnitude
     *  - k is an arbitrary constant
     *  - I is the stimulus intensity
     *  - \f$ \alpha \f$ is the power exponent.
     *
     * To compute the loudness, we consider the energy of the signal as the stimulus intensity and
     * \f$ \alpha = 0.67 \f$ (sound pressure of 3000-Hz tone).
     *
     * @param first Forward iterator defining the begin of the range to examine.
     * @param last Forward iterator defining the end of the range to examine.
     * @returns The estimated loudness of the elements in the range.
     */
    template <typename ForwardIt>
    constexpr auto loudness(ForwardIt first, ForwardIt last) {
        const auto e = temporal::energy(first, last);
        return std::pow(e, 0.67);
    }

}}}

#endif //EDSP_LOUDNESS_HPP
