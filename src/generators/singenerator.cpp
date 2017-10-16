//
// Created by Mohammed Boujemaoui on 12/10/2017.
//

#include "singenerator.h"
#include "base/constants.h"

using namespace eDSP::generators;

template<typename T>
const std::vector<T> &SinGenerator<T>::generate() {
    T increment = 0.0, period = 1.0f / Generator<T>::sampleRate;
    T normPhase = 2 * Constants<T>::pi * phase;
    for (size_t i = 0, size = Generator<T>::data.size(); i < size; i++) {
        Generator<T>::data[i] = Generator<T>::amplitude * std::sin(2 * Constants<T>::pi * Generator<T>::frequency * increment + normPhase);
        increment += period;
    }
    return Generator<T>::data;
}

template<typename T>
SinGenerator<T>::SinGenerator(size_t size, T sampleRate, T frequency, T phase, T amplitude) : Generator<T>(size, sampleRate,
                                                                                                     frequency, phase,
                                                                                                     amplitude) {}
EDSP_DCL_TEMPLATE(eDSP::generators::SinGenerator, float);
EDSP_DCL_TEMPLATE(eDSP::generators::SinGenerator, double);
