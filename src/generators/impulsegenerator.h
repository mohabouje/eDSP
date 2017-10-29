//
// Impulse Generator
// Will generate an impulse signal
//  - First sample 		= amplitude
//  - Other samples 	= zero
//  - Length of signal 	= size
// This is often needed to study impulse response of filters, delays...
//

#ifndef EDSP_IMPULSEGENERATOR_H
#define EDSP_IMPULSEGENERATOR_H

#include "generator.h"

EDSP_BEGING_NAMESPACE
	namespace generators {
        template <typename T>
        class ImpulseGenerator : Generator<T> {
        public:
            explicit ImpulseGenerator(size_t size, T amplitude);
            ImpulseGenerator() = default;
            ~ImpulseGenerator() override = default;
            const std::vector<T>& generate();
        };
	}
EDSP_END_NAMESPACE

#endif // EDSP_IMPULSEGENERATOR_H
