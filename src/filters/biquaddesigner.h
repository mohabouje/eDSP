//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_BIQUADDESIGNER_H
#define EDSP_BIQUADDESIGNER_H

#include <tclDecls.h>
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
                BiquadCoefficients<T> a, b;
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
                BiquadCoefficients<T> a, b;
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
                BiquadCoefficients<T> a, b;
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
                BiquadCoefficients<T> a, b;
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
                BiquadCoefficients<T> a, b;
                a[0] = static_cast<T>((1 + K2) * norm);
                a[1] = static_cast<T>(2 * (K2 - 1) * norm);
                a[2] = static_cast<T>(a[0]);
                b[0] = static_cast<T>(1);
                b[1] = static_cast<T>(a[1]);
                b[2] = static_cast<T>((1 - K / Q + K2) * norm);
                return Biquad<T>(a,b);
            }


            template <typename T>
            Biquad<T> peak(T frequency, T Q, T gain) {
                auto K = static_cast<T>(std::tan(Constants<T>::pi * frequency));
                auto K2 = static_cast<T>(K * K);
                auto V = static_cast<T>(std::exp(std::abs(gain) * static_cast<T>(0.05f) * std::log10(200)));

                BiquadCoefficients a, b;
                if (gain >= 0) {
                    auto norm = static_cast<T>(1 / (1 + 1 / Q * K + K2));
                    a[0] = static_cast<T>((1 + V / Q * K + K2) * norm);
                    a[1] = static_cast<T>(2 * (K2 - 1) * norm);
                    a[2] = static_cast<T>((1 - V / Q * K + K2) * norm);
                    b[0] = static_cast<T>(1);
                    b[1] = static_cast<T>(a[1]);
                    b[2] = static_cast<T>((1 - 1 / Q * K + K2) * norm);
                }
                else {
                    auto norm = static_cast<T>(1 / (1 + V / Q * K + K2));
                    a[0] = static_cast<T>((1 + 1 / Q * K + K2) * norm);
                    a[1] = static_cast<T>(2 * (K2 - 1) * norm);
                    a[2] = static_cast<T>((1 - 1 / Q * K + K2) * norm);
                    b[0] = static_cast<T>(1);
                    b[1] = static_cast<T>(a[1]);
                    b[2] = static_cast<T>((1 - V / Q * K + K2) * norm);
                }
                return Biquad<T>(a,b);
            }

            template <typename T>
            Biquad<T> lowshelf(T frequency, T gain) {
                auto K = static_cast<T>(std::tan(Constants<T>::pi * frequency));
                auto K2 = static_cast<T>(K * K);
                auto V  = static_cast<T>(std::exp(std::fabs(gain) * static_cast<T>(0.05f) * std::log10(200)));

                BiquadCoefficients a, b;
                if (gain >= 0) {
                    auto norm = 1 / (1 + std::sqrt(2) * K + K2);
                    a[0] = static_cast<T>((1 + std::sqrt(2 * V) * K + V * K2) * norm);
                    a[1] = static_cast<T>(2 * (V * K2 - 1) * norm);
                    a[2] = static_cast<T>((1 - std::sqrt(2 * V) * K + V * K2) * norm);
                    b[0] = static_cast<T>(1);
                    b[1] = static_cast<T>(2 * (K2 - 1) * norm);
                    b[2] = static_cast<T>((1 - std::sqrt(2) * K + K2) * norm);
                } else {
                    auto norm = static_cast<T>(1 / (1 + std::sqrt(2 * V) * K + V * K2));
                    a[0] = static_cast<T>((1 + std::sqrt(2) * K + K2) * norm);
                    a[1] = static_cast<T>(2 * (K2 - 1) * norm);
                    a[2] = static_cast<T>((1 - std::sqrt(2) * K + K2) * norm);
                    b[0] = static_cast<T>(1);
                    b[1] = static_cast<T>(2 * (V * K2 - 1) * norm);
                    b[2] = static_cast<T>((1 - std::sqrt(2 * V) * K + V * K2) * norm);
                }
                return Biquad<T>(a, b);
            }

            template<typename T>
            Biquad<T> highshelf(T frequency, T gain) {
                auto K = static_cast<T>(std::tan(Constants<T>::pi * frequency));
                auto K2 = static_cast<T>(K * K);
                auto V  = static_cast<T>(std::exp(std::fabs(gain) * static_cast<T>(0.05f) * std::log10(200)));

                BiquadCoefficients a, b;
                if (gain >= 0) {
                    auto norm =static_cast<T>( 1 / (1 + std::sqrt(2) * K + K2));
                    a[0] = static_cast<T>((V + std::sqrt(2 * V) * K + K2) * norm);
                    a[1] = static_cast<T>(2 * (K2 - V) * norm);
                    a[2] = static_cast<T>((V - std::sqrt(2 * V) * K + K2) * norm);
                    b[0] = static_cast<T>(1);
                    b[1] = static_cast<T>(2 * (K2 - 1) * norm);
                    b[2] = static_cast<T>((1 - std::sqrt(2) * K + K2) * norm);
                } else {
                    auto norm = static_cast<T>(1 / (V + std::sqrt(2 * V) * K + K2));
                    a[0]   = static_cast<T>((1 + std::sqrt(2) * K + K2) * norm);
                    a[1]   = static_cast<T>(2 * (K2 - 1) * norm);
                    a[2]   = static_cast<T>((1 - std::sqrt(2) * K + K2) * norm);
                    b[0] = static_cast<T>(1);
                    b[1]   = static_cast<T>(2 * (K2 - V) * norm);
                    b[2]   = static_cast<T>((V - std::sqrt(2 * V) * K + K2) * norm);
                }
                return Biquad<T>(a, b);
            }


        }
    }
EDSP_END_NAMESPACE


#endif //EDSP_BIQUADDESIGNER_H
