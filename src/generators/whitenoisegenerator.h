//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_WHITENOISE_H
#define EDSP_WHITENOISE_H

#include "generator.h"

EDSP_BEGING_NAMESPACE
    namespace generators {
        template <typename T>
        class WhiteNoiseGenerator : public Generator<T> {
        public:
            explicit WhiteNoiseGenerator(size_t size);
            WhiteNoiseGenerator() = default;
            ~WhiteNoiseGenerator() override = default;
            const std::vector<T>& generate();
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_WHITENOISE_H
