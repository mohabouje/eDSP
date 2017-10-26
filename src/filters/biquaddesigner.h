//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_BIQUADDESIGNER_H
#define EDSP_BIQUADDESIGNER_H

#include "base/algoritmtemplate.h"
#include "base/constants.h"
#include "biquad.h"

EDSP_BEGING_NAMESPACE
    namespace Filters {
        namespace BiquadDesigner {
            template <typename T >
            Biquad<T> allpass(T frequency, T Q) {
                auto alpha = static_cast<T>(std::sin(frequency) / 2.0 * Q);
                auto cs    = static_cast<T>(std::cos(frequency));
                std::array<T, 3> a, b;
                b =  static_cast<T>(1.0 / (1.0 + alpha));
                b[1] =  static_cast<T>(-2.0 * cs * b[0]);
                b[2] =  static_cast<T>((1.0 - alpha) * b[0]);
                a[0] =  static_cast<T>((1.0 - alpha) * b[0]);
                a[1] =  static_cast<T>(-2.0 * cs * b[0]);
                a[2] =  static_cast<T>((1.0 + alpha) * b[0]);
                return Biquad<T>(a, b);
            }

            template <typename T>
            Biquad<T> lowpass(T frequency, T Q)  {
                auto K    = static_cast<T>(std::tan(Constants<T>::pi  * frequency));
                auto K2   = static_cast<T>(K * K);
                auto norm = static_cast<T>(1 / (1 + K / Q + K2));
                std::array<T, 3> a, b;
                a[0] = static_cast<T>(K2 * norm);
                a[1] = static_cast<T>(2 * a[0]);
                a[2] = static_cast<T>(a[0]);
                b[0] = static_cast<T>(1);
                b[1] = static_cast<T>(2 * (K2 - 1) * norm);
                b[2] = static_cast<T>((1 - K / Q + K2) * norm);
                return Biquad<T>(a,b);
            }

            template <typename T >
            Biquad<T> highpass(T frequency, T Q) {
                auto K    = static_cast<T>(std::tan(Constants<T>::pi  * frequency));
                auto K2   = static_cast<T>(K * K);
                auto norm = static_cast<T>(1 / (1 + K / Q + K2));
                std::array<T, 3> a, b;
                a[0] = static_cast<T>(1 * norm);
                a[1] = static_cast<T>(-2 * a[0]);
                a[2] = static_cast<T>(a[0]);
                b[0] = static_cast<T>(1);
                b[1] = static_cast<T>(2 * (K2 - 1) * norm);
                b[2] = static_cast<T>((1 - K / Q + K2) * norm);
                return Biquad<T>(a,b);
            }


            template <typename T>
            Biquad<T> bandpass(T frequency, T Q) {
                auto K    = static_cast<T>(std::tan(2 * Constants<T>::pi * frequency));
                auto K2   = static_cast<T>(K * K);
                auto  norm = static_cast<T>(1 / (1 + K / Q + K2));
                std::array<T, 3> a, b;
                a[0] = static_cast<T>(K / Q * norm);
                a[1] = static_cast<T>(0);
                a[2] = static_cast<T>(-a[0]);
                b[0] = static_cast<T>(1);
                b[1] = static_cast<T>(2 * (K2 - 1) * norm);
                b[2] = static_cast<T>((1 - K / Q + K2) * norm);
                return Biquad<T>(a, b);
            }

            template <typename T>
            Biquad<T> notch(T frequency, T Q) {
                auto K    = static_cast<T>(std::tan(Constants<T>::pi * frequency));
                auto K2   = static_cast<T>(K * K);
                auto norm = static_cast<T>(1 / (1 + K / Q + K2));
                std::array<T, 3> a, b;
                a[0] = static_cast<T>((1 + K2) * norm);
                a[1] = static_cast<T>(2 * (K2 - 1) * norm);
                a[2] = static_cast<T>(a[0]);
                b[0] = static_cast<T>(1);
                b[1] = static_cast<T>(a[1]);
                b[2] = static_cast<T>((1 - K / Q + K2) * norm);
                return Biquad<T>(a,b);
            }
        }
    }
EDSP_END_NAMESPACE


#endif //EDSP_BIQUADDESIGNER_H
