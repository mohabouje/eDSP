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
 * File: spectral_irregularity.hpp
 * Created by: Mohammed Boujemaoui Boulaghmoudi
 * Created at: 14/10/18
 */

#ifndef EDSP_SPECTRAL_IRREGULARITY_HPP
#define EDSP_SPECTRAL_IRREGULARITY_HPP

#include <iterator>
namespace edsp { namespace feature { inline namespace spectral {

    /**
     * @brief Computes the spectral irregularity of the of the magnitude spectrum
     * represented by the elements in the range [first, last)
     *
     * The spectral irregularity quantifies the variations of the logarithmically-scaled rate-map across frequencies. This
     * implementation is based on [Jensen 1999] where the spectral irregularity is estimated as the sum of the square
     * of the difference in amplitude between adjoining partials.
     *
     *
     * @see [Jensen, 1999] K. Jensen, Timbre Models of Musical Sounds, Ph.D.
     *       dissertation, University of Copenhagen, Rapport Nr. 99/7.
     *
     * @param first Forward iterator defining the begin of the magnitude spectrum.
     * @param last Forward iterator defining the end of the magnitude spectrum.
     * @return Estimated spectral irregularity.
     */
    template <typename ForwardIt>
    constexpr auto spectral_irregularity(ForwardIt first, ForwardIt last) {
        // TODO: implement the irregularity function outside this.
        using value_type       = typename std::iterator_traits<ForwardIt>::value_type;
        value_type square_diff = 0, square_ampl = 0;
        for (auto until = (last - 1); first != until; ++first) {
            const value_type diff = (*first + 1) - (*first);
            square_diff += diff * diff;
            square_ampl += (*first) * (*first);
        }
        return square_diff / square_ampl;
    }

}}} // namespace edsp::feature::spectral

#endif //EDSP_SPECTRAL_IRREGULARITY_HPP
