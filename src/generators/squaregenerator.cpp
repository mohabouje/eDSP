//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#include "squaregenerator.h"
using namespace eDSP::generators;

template<typename T>
SquareGenerator::SquareGenerator(size_t size, T duttycycle, T sampleRate, T frequency,
                                                       T amplitude) : dc(duttycycle), Generator(size, sampleRate, frequency, amplitude) {

}

template<typename T>
const std::vector<T> &SquareGenerator::compute() {
    const size_t samplesPerPeriod = static_cast<size_t>(sampleRate / frequency);
    const size_t samplesPerDuttyCycle = static_cast<size_t> (dc * samplesPerPeriod);
    for (size_t i = 0, size = data.size(); i < size; i++) {
        const size_t t = i % samplesPerPeriod;
        data[i] = amplitude * (t < samplesPerDuttyCycle ? 1.0 : -1.0);
    }
    return data;
}
