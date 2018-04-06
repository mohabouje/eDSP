//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_BIQUADDESIGNER_H
#define EDSP_BIQUADDESIGNER_H

#include "biquad.h"

EDSP_BEGIN_NAMESPACE
    namespace filters {
        namespace designer {

            Biquad allpass(double frequency, double Q);

            Biquad lowpass(double frequency, double Q);

            Biquad highpass(double frequency, double Q);

            Biquad bandpass(double frequency, double Q);

            Biquad notch(double frequency, double Q);

            Biquad peak(double frequency, double Q, double gain);

            Biquad lowshelf(double frequency, double gain);

            Biquad highshelf(double frequency, double gain);


        }
    }
EDSP_END_NAMESPACE


#endif //EDSP_BIQUADDESIGNER_H
