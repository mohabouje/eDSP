//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_MUTE_H
#define EDSP_MUTE_H

#include "config.h"

EDSP_BEGIN_NAMESPACE
    namespace algorithm {
        class Mute {
        public:
            Mute() = default;

            template <class InputIterator, class OutputIterator>
            void compute(const InputIterator first, const InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    compute(*first, *out);
                };
            }

            template <typename T>
            void compute(const T in, T& out) {
                out = static_cast<T>(0);
            }
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_MUTE_H
