#include "twosingenerator.h"
#include "base/constants.h"

using namespace eDSP::generators;

template<typename T>
const std::vector<T> &TwoSinGenerator<T>::generate() {
    T increment = 0, period = 1. / Generator<T>::sampleRate;
    T normPhase = 2.0 * Constants<T>::pi * this->phase;
    for (size_t i = 0, size = this->data.size(); i < size; i++) {
        this->data[i] =
        this->amplitude * std::sin(2.0 * Constants<T>::pi * (this->frequency * 0.5) * increment + normPhase) + // frequency_lo
		this->amplitude * std::sin(2.0 * Constants<T>::pi * (this->frequency * 2.0) * increment + normPhase);  // frequency_hi
        increment += period;
    }
    return this->data;
}

template<typename T>
TwoSinGenerator<T>::TwoSinGenerator(size_t size, T sampleRate, T frequency, T phase, T amplitude) : Generator<T>(size, sampleRate,
                                                                                                     frequency, phase,
                                                                                                     amplitude) {}
EDSP_DCL_TEMPLATE(eDSP::generators::TwoSinGenerator, float);
EDSP_DCL_TEMPLATE(eDSP::generators::TwoSinGenerator, double);

