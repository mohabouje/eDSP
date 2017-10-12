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

            T getSampleRate() const final = delete;
            T getFrequency() const final = delete;
            T getAmplitude() const final = delete;
            void setSampleRate(T sampleRate) final = delete;
            void setFrequency(T frequency) final = delete;
            void setAmplitude(T amplitude) final = delete;
        };

    }
EDSP_END_NAMESPCE

#endif //EDSP_WHITENOISE_H
