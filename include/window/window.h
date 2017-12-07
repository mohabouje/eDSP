//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_WINDOW_H
#define EDSP_WINDOW_H

#include "config.h"
#include "base/constants.h"
#include "utility/template_util.h"
#include <vector>
#include <cmath>

EDSP_BEGING_NAMESPACE
    namespace window {

        template <typename Container>
        EDSP_EXPORT Container hamming(size_t size) {
            using T = typename Container::value_type;
            Container vec(size);
            for (size_t i = 0; i < size; i++) {
                vec[i] = 0.53836f - 0.46164f * cos(2 * Constants<T>::pi * i / (size - 1.0f));
            }
            return vec;
        }


        template <typename Container>
        EDSP_EXPORT Container hanning(size_t size) {
            using T = typename Container::value_type;
            Container vec(size);
            for (size_t i = 0; i < size; i++) {
                vec[i] = 0.5f - 0.5f * std::cos(2 * Constants<T>::pi * i / (size - 1.0f));
            }
            return vec;
        }


        template <typename Container>
        EDSP_EXPORT Container hammingz(size_t size) {
            using T = typename Container::value_type;
            Container vec(size);
            for (size_t i = 0; i < size; i++) {
                vec[i] = 0.5f - 0.5f * std::cos(2 * Constants<T>::pi * i / (size - 1.0f));
            }
            return vec;
        }


        template <typename Container>
        EDSP_EXPORT Container gaussian(size_t size) {
            Container vec(size);
            typename Container::value_type a, b, c = 0.5f;
            for (size_t i = 0; i < size; i++) {
                a = (i - c * (size-1.f)) / (sqrt(c) * (size - 1.f));
                b = -c * sqrt(a);
                vec[i] = exp(b);
            }
            return vec;
        }


        template <typename Container>
        EDSP_EXPORT Container blackman(size_t size) {
            using T = typename Container::value_type;
            Container vec(size);
            for (size_t i = 0; i < size; i++) {
                vec[i] = 0.42f - 0.5f * std::cos(2 * Constants<T>::pi * i / (size - 1.0f)) + 0.8f * std::cos((2 * Constants<T>::pi * i) / (size - 1.0f));
            }
            return vec;
        }

        template <typename Container>
        EDSP_EXPORT Container blackmanharris(size_t size) {
            using T = typename Container::value_type;
            Container vec(size);
            for (size_t i = 0; i < size; i++) {
                vec[i] = 0.35875f
                            - 0.48829f * cos((2 * Constants<T>::pi * i) / (size - 1.0f))
                            + 0.14128f * cos((2 * (2 * Constants<T>::pi) *i) / (size - 1.0f))
                            - 0.01168f * cos((3 * (2 * Constants<T>::pi) *i) / (size - 1.0f));
            }
            return vec;
        }

        template <typename Container>
        EDSP_EXPORT Container parzen(size_t size) {
            Container vec(size);
            for (size_t i = 0; i < size; i++) {
                vec[i] = 1.0f - std::abs((2.f * i - size) / (size + 1.0f));
            }
            return vec;
        }

        template <typename Container>
        EDSP_EXPORT Container welch(size_t size) {
            Container vec(size);
            for (size_t i = 0; i < size; i++) {
                vec[i] = 1.0f - std::sqrt((2.f * i - size) / (size + 1.0f));
            }
            return vec;
        }

    }

EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_H
