//
// Created by Mohammed Boujemaoui on 12/10/2017.
//

#ifndef EDSP_SINGENERATOR_H
#define EDSP_SINGENERATOR_H

#include "generator.h"

EDSP_BEGING_NAMESPACE
    namespace generators {
        template<typename T>
        class SinGenerator : public Generator<T> {
        public:
            EDSP_DISABLE_DEFAULT(SinGenerator)
            EDSP_DISABLE_COPY(SinGenerator)
            SinGenerator(size_t size, T sampleRate, T frequency, T phase, T amplitude);
            virtual ~SinGenerator() = default;
            const std::vector<T>& generate();
            inline T getPhase() const { return phase; }
            void setPhase(T phase) { SinGenerator::phase = phase; }

        private:
            T phase{0};
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_SINGENERATOR_H
