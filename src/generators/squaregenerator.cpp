//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#include "squaregenerator.h"
using namespace eDSP::generators;

template<typename T>
SquareGenerator<T>::SquareGenerator(size_t size, T duttycycle, T sampleRate, T frequency, T amplitude) :
        duttyCycle(duttycycle),
        Generator<T>(size, sampleRate, frequency, 0, amplitude)
{

}

template<typename T>
const std::vector<T> &SquareGenerator<T>::generate() {
    auto samplesPerPeriod = static_cast<size_t>(this->sampleRate / this->frequency);
    auto samplesPerDuttyCycle = static_cast<size_t> (duttyCycle * samplesPerPeriod);
    for (size_t i = 0, size = this->data.size(); i < size; i++) {
        this->data[i] = this->amplitude * ((i % samplesPerPeriod) < samplesPerDuttyCycle ? 1 : -1);
    }
    return this->data;
}

EDSP_DCL_TEMPLATE(eDSP::generators::SquareGenerator, float);
EDSP_DCL_TEMPLATE(eDSP::generators::SquareGenerator, double);
