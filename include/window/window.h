//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_WINDOW_H
#define EDSP_WINDOW_H

#include "config.h"
#include "base/constants.h"
#include <vector>
#include <cmath>
#include <iterator>
#include <array>

#ifdef EDSP_X64
    using real = double;
#else
    using real = float;
#endif


EDSP_BEGIN_NAMESPACE
    namespace window {
        template <class ForwardIterator>
        constexpr void hamming(ForwardIterator __first, ForwardIterator __last) {
            for (auto i = 0l, size = std::distance(__first, __last)   ; __first != __last; ++i, ++__first) {
                *__first = 0.53836f - 0.46164f * cos(2 * Constants<float>::pi * i / (size - 1.0f));
            }
        }

        template <class ForwardIterator>
        constexpr void hanning(ForwardIterator __first, ForwardIterator __last) {
            for (auto i = 0l, size = std::distance(__first, __last); __first != __last; ++i, ++__first) {
                *__first = 0.5f - 0.5f * std::cos(2 * Constants<float>::pi * i / (size - 1.0f));
            }
        }


        template <class ForwardIterator>
        constexpr void hanningz(ForwardIterator __first, ForwardIterator __last) {
            for (auto i = 0l, size = std::distance(__first, __last); __first != __last; ++i, ++__first) {
                *__first = 0.5f - 0.5f * std::cos(2 * Constants<float>::pi * i / (size - 1.0f));
            }
        }

        template <class ForwardIterator>
        constexpr void gaussian(ForwardIterator __first, ForwardIterator __last) {
            for (auto i = 0l, size = std::distance(__first, __last); __first != __last; ++i, ++__first) {
                const auto a = (i -  0.5f * (size-1.0f)) / (sqrt(0.5f) * (size - 1.0f));
                *__first = exp(-0.5f * sqrt(a));
            }
        }

        template <class ForwardIterator>
        constexpr void blackman(ForwardIterator __first, ForwardIterator __last) {
            for (auto i = 0l, size = std::distance(__first, __last); __first != __last; ++i, ++__first) {
                *__first = 0.42f - 0.5f * std::cos(2 * Constants<float>::pi * i / (size - 1.0f))
                           + 0.8f * std::cos((2 * Constants<float>::pi * i) / (size - 1.0f));
            }
        }

        template <class ForwardIterator>
        constexpr void blackmanharris(ForwardIterator __first, ForwardIterator __last) {
            for (auto i = 0l, size = std::distance(__first, __last); __first != __last; ++i, ++__first) {
                *__first = 0.35875f
                        - 0.48829f * cos((2 * Constants<float>::pi * i) / (size - 1.0f))
                        + 0.14128f * cos((2 * (2 * Constants<float>::pi) *i) / (size - 1.0f))
                        - 0.01168f * cos((3 * (2 * Constants<float>::pi) *i) / (size - 1.0f));
            }
        }

        template <class ForwardIterator>
        constexpr void parzen(ForwardIterator __first, ForwardIterator __last) {
            for (auto i = 0l, size = std::distance(__first, __last); __first != __last; ++i, ++__first) {
                *__first = 1.0f - std::abs((2.f * i - size) / (size + 1.0f));
            }
        }

        template <class ForwardIterator>
        constexpr void welch(ForwardIterator __first, ForwardIterator __last) {
            for (auto i = 0l, size = std::distance(__first, __last)   ; __first != __last; ++i, ++__first) {
                *__first = 1.0f - std::sqrt((2.f * i - size) / (size + 1.0f));
            }
        }
    }

EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_H
