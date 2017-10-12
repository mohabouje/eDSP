//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#include "squaregenerator.h"
using namespace eDSP::generators;

template<typename T>
SquareGenerator::SquareGenerator(size_t size, T duttycycle, T sampleRate, T frequency, T amplitude) :
        duttyCycle(duttycycle),
        Generator(size, sampleRate, frequency, 0, amplitude)
{

}

template<typename T>
const std::vector<T> &SquareGenerator::generate() {
    const size_t samplesPerPeriod = static_cast<size_t>(sampleRate / frequency);
    const size_t samplesPerDuttyCycle = static_cast<size_t> (duttyCycle * samplesPerPeriod);
    for (size_t i = 0, size = data.size(); i < size; i++) {
        data[i] = amplitude * ((i % samplesPerPeriod) < samplesPerDuttyCycle ? 1 : -1);
    }
    return data;
}


