//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_BIQUADDESIGNER_H
#define EDSP_BIQUADDESIGNER_H

#include "base/constants.h"
#include "biquad.h"
#include <cmath>
EDSP_BEGIN_NAMESPACE
    namespace filters {
        namespace designer {

            constexpr Biquad allpass(double frequency, double Q) {
                constexpr auto alpha = std::sin(frequency) / 2.0 * Q;
                constexpr auto cs    = std::cos(frequency;
                BiquadCoefficients a, b;
                b[0] = 1.0 / (1.0 + alpha);
                b[1] = -2.0 * cs * b[0];
                b[2] = (1.0 - alpha) * b[0];
                a[0] = (1.0 - alpha) * b[0];
                a[1] = -2.0 * cs * b[0];
                a[2] = (1.0 + alpha) * b[0];
                return Biquad(a, b);
            }

            constexpr Biquad lowpass(double frequency, double Q)  {
                constexpr auto K    = std::tan(Constants<double>::pi  * frequency);
                constexpr auto K2   = K * K;
                constexpr auto norm = 1. / (1. + K / Q + K2);
                BiquadCoefficients a, b;
                a[0] = K2 * norm;
                a[1] = 2. * a[0];
                a[2] = a[0];
                b[0] = 1.;
                b[1] = 2. * (K2 - 1.) * norm;
                b[2] = (1. - K / Q + K2) * norm;
                return Biquad(a,b);
            }

            constexpr Biquad highpass(double frequency, double Q) {
                constexpr auto K    = std::tan(Constants<double>::pi  * frequency);
                constexpr auto K2   = K * K;
                constexpr auto norm = 1. / (1. + K / Q + K2);
                BiquadCoefficients a, b;
                a[0] = norm;
                a[1] = -2. * a[0];
                a[2] = a[0];
                b[0] = 1.;
                b[1] = 2. * (K2 - 1.) * norm;
                b[2] = (1. - K / Q + K2) * norm;
                return Biquad(a,b);
            }

            constexpr Biquad bandpass(double frequency, double Q) {
                constexpr auto K    = std::tan(2. * Constants<double >::pi * frequency);
                constexpr auto K2   = K * K;
                constexpr auto  norm = 1. / (1. + K / Q + K2);
                BiquadCoefficients a, b;
                a[0] = K / Q * norm;
                a[1] = 0.;
                a[2] = -a[0];
                b[0] = 1.;
                b[1] = 2. * (K2 - 1.) * norm;
                b[2] = (1. - K / Q + K2) * norm;
                return Biquad(a, b);
            }

            constexpr Biquad notch(double frequency, double Q) {
                constexpr auto K    = std::tan(Constants<double>::pi * frequency);
                constexpr auto K2   = K * K;
                constexpr auto norm = 1. / (1. + K / Q + K2);
                BiquadCoefficients a, b;
                a[0] = (1. + K2) * norm;
                a[1] = 2. * (K2 - 1.) * norm;
                a[2] = a[0];
                b[0] = 1.;
                b[1] = a[1];
                b[2] = (1. - K / Q + K2) * norm;
                return Biquad(a,b);
            }


            constexpr Biquad peak(double frequency, double Q, double gain) {
                constexpr auto K = std::tan(Constants<double>::pi * frequency);
                constexpr auto K2 = K * K;
                constexpr auto V = std::exp(std::abs(gain) * (0.05) * std::log10(200));

                BiquadCoefficients a, b;
                if (gain >= 0) {
                    auto norm = 1 / (1 + 1 / Q * K + K2);
                    a[0] = (1 + V / Q * K + K2) * norm;
                    a[1] = 2 * (K2 - 1) * norm;
                    a[2] = (1 - V / Q * K + K2) * norm;
                    b[0] = 1;
                    b[1] = a[1];
                    b[2] = (1 - 1 / Q * K + K2) * norm;
                } else {
                    auto norm = 1 / (1 + V / Q * K + K2);
                    a[0] = (1 + 1 / Q * K + K2) * norm;
                    a[1] = 2 * (K2 - 1) * norm;
                    a[2] = (1 - 1 / Q * K + K2) * norm;
                    b[0] = 1;
                    b[1] = a[1];
                    b[2] = (1 - V / Q * K + K2) * norm;
                }
                return Biquad(a,b);
            }

            constexpr Biquad lowshelf(double frequency, double gain) {
                constexpr auto K = std::tan(Constants<double>::pi * frequency);
                constexpr auto K2 = K * K;
                constexpr auto V  = std::exp(std::fabs(gain) * (0.05f) * std::log10(200));

                BiquadCoefficients a, b;
                if (gain >= 0) {
                    constexpr auto norm = 1 / (1 + std::sqrt(2) * K + K2;
                    a[0] = (1 + std::sqrt(2 * V) * K + V * K2) * norm;
                    a[1] = 2 * (V * K2 - 1) * norm;
                    a[2] = (1 - std::sqrt(2 * V) * K + V * K2) * norm;
                    b[0] = 1;
                    b[1] = 2 * (K2 - 1) * norm;
                    b[2] = (1 - std::sqrt(2) * K + K2) * norm;
                } else {
                    constexpr auto norm = 1 / (1 + std::sqrt(2 * V) * K + V * K2);
                    a[0] = (1 + std::sqrt(2) * K + K2) * norm;
                    a[1] = 2 * (K2 - 1) * norm;
                    a[2] = (1 - std::sqrt(2) * K + K2) * norm;
                    b[0] = 1;
                    b[1] = 2 * (V * K2 - 1) * norm;
                    b[2] = (1 - std::sqrt(2 * V) * K + V * K2) * norm;
                }
                return Biquad(a, b);
            }

            constexpr Biquad highshelf(double frequency, double gain) {
                constexpr auto K = std::tan(Constants<double>::pi * frequency);
                constexpr auto K2 = K * K;
                constexpr auto V  = std::exp(std::fabs(gain) * (0.05f) * std::log10(200));

                BiquadCoefficients a, b;
                if (gain >= 0) {
                    constexpr auto norm =( 1 / (1 + std::sqrt(2) * K + K2);
                    a[0] = ((V + std::sqrt(2 * V) * K + K2) * norm;
                    a[1] = (2 * (K2 - V) * norm;
                    a[2] = ((V - std::sqrt(2 * V) * K + K2) * norm;
                    b[0] = (1;
                    b[1] = (2 * (K2 - 1) * norm;
                    b[2] = ((1 - std::sqrt(2) * K + K2) * norm;
                } else {
                    constexpr auto norm = (1 / (V + std::sqrt(2 * V) * K + K2);
                    a[0] = (1 + std::sqrt(2) * K + K2) * norm;
                    a[1] = 2 * (K2 - 1) * norm;
                    a[2] = (1 - std::sqrt(2) * K + K2) * norm;
                    b[0] = 1;
                    b[1] = 2 * (K2 - V) * norm;
                    b[2] = (V - std::sqrt(2 * V) * K + K2) * norm;
                }
                return Biquad(a, b);
            }


        }
    }
EDSP_END_NAMESPACE


#endif //EDSP_BIQUADDESIGNER_H
