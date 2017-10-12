//
// Created by Mohammed Boujemaoui on 12/10/2017.
//

#include "singenerator.h"
using namespace eDSP::generators;

template<typename T>
const std::vector<T> &SinGenerator::generate() {
    T increment = 0.0, period = 1.0f / sampleRate;
    T normPhase = 2 * Constants<T>::pi * phase;
    for (size_t i = 0, size = data.size(); i < size; i++, increment += period) {
        data[i] = amplitude * std::sin(2 * Constants<T>::pi * frequency * increment + normPhase);
    }
}

template<typename T>
SinGenerator::SinGenerator(size_t size, T sampleRate, T frequency, T phase, T amplitude) : Generator(size, sampleRate,
                                                                                                     frequency, phase,
                                                                                                     amplitude) {}

