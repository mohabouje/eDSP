//
// Two-Sine Generator
// Generate a sum of two sines, sine_lo and sine_hi
// sine_lo frequency will be one octave below the specified frequency
// sine_hi frequency will be one octave above the specified frequency
// This can be needed to study biquad filters (high pass, low pass, crossovers...)

#ifndef EDSP_TWOSINGENERATOR_H
#define EDSP_TWOSINGENERATOR_H

#include "generator.h"

EDSP_BEGING_NAMESPACE
    namespace generators {
        template<typename T>
        class TwoSinGenerator : public Generator<T> {
        public:
            EDSP_DISABLE_DEFAULT(TwoSinGenerator)
            EDSP_DISABLE_COPY(TwoSinGenerator)
            TwoSinGenerator(size_t size, T sampleRate, T frequency, T phase, T amplitude);
            virtual ~TwoSinGenerator() = default;
            const std::vector<T>& generate();
            inline T getPhase() const { return phase; }
            void setPhase(T phase) { TwoSinGenerator::phase = phase; }

        private:
            T phase{0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_TWOSINGENERATOR_H

