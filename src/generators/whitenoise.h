//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_WHITENOISE_H
#define EDSP_WHITENOISE_H

#include "config.h"
#include "generator.h"

EDSP_BEGING_NAMESPACE
    namespace generators {
        template <typename T>
        class WhiteNoise : public Generator<T> {
        public:
            explicit WhiteNoise(size_t size);
            WhiteNoise() = default;
            ~WhiteNoise() override = default;
            const std::vector<T>& compute();
        };
    }
EDSP_END_NAMESPCE

#endif //EDSP_WHITENOISE_H
