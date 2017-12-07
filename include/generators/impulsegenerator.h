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
#include "base/constants.h"

EDSP_BEGING_NAMESPACE
	namespace generators {
        template <typename T, std::size_t N>
        class EDSP_EXPORT ImpulseGenerator : Generator<T, N> {
        public:
            explicit ImpulseGenerator(T amplitude) :
                    Generator<T,N>(0, 0, amplitude) {
            }
            ~ImpulseGenerator() override = default;
            const std::array<T, N> &generate() {
                this->data[0] = this->amplitude;
                return this->data;
            }
        };
	}
EDSP_END_NAMESPACE

#endif // EDSP_IMPULSEGENERATOR_H
