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
* Filename: audspace.hpp
* Author: Mohammed Boujemaoui
* Date: 18/10/18
*/

#ifndef EDSP_AUDSPACE_HPP
#define EDSP_AUDSPACE_HPP

#include <edsp/auditory/barkspace.hpp>
#include <edsp/auditory/melspace.hpp>
#include <edsp/auditory/erbspace.hpp>
#include <edsp/auditory/centspace.hpp>

// TODO: take a look into http://www.ee.ic.ac.uk/hp/staff/dmb/voicebox/voicebox.html
namespace edsp { namespace auditory {

    /**
     * The auditory_scale enum represents the different scales used to convert frequencies to auditory units.
     */
    enum auditory_scale {
        mel,  /*<! Frequencies will be represent on a Mel scale */
        erb,  /*<! Frequencies will be represent on a ERB scale */
        bark, /*<! Frequencies will be represent on a Bark scale */
        cent  /*<! Frequencies will be represent on a Cent scale */
    };

    /**
     * @brief This function computes an array of N frequencies uniformly spaced between [x1,x2] on a Bark
     * scale and stores the result in another range, beginning at d_first.
     *
     * @param min Minimum frequency.
     * @param max Maximum frequency..
     * @param N Number of frequencies to generate.
     * @param scale Auditory scale to use.
     * @param d_first The beginning of the destination range
     */
    template <typename OutputIt, typename Numeric, typename Integer>
    constexpr void audspace(OutputIt d_first, Numeric min, Numeric max, Integer N, auditory_scale scale) {
        switch (scale) {
            case auditory_scale::mel:
                melspace(d_first, min, max, N);
                break;
            case auditory_scale::erb:
                erbspace(d_first, min, max, N);
                break;
            case auditory_scale::bark:
                barkspace(d_first, min, max, N);
                break;
            case auditory_scale::cent:
                centspace(d_first, min, max, N);
                break;
        }
    }

}} // namespace edsp::auditory

#endif //EDSP_AUDSPACE_HPP
