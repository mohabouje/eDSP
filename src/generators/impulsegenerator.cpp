#include "impulsegenerator.h"

using namespace eDSP::generators;

template<typename T>
const std::vector<T> &ImpulseGenerator<T>::generate() {

    Generator<T>::data[0] = Generator<T>::amplitude;

    for (size_t i = 1, size = Generator<T>::data.size(); i < size; i++) {
        Generator<T>::data[i] = 0.0;
    }

    return Generator<T>::data;
}

template<typename T>
ImpulseGenerator<T>::ImpulseGenerator(size_t size, T amplitude) :
												Generator<T>(size, amplitude) {}
EDSP_DCL_TEMPLATE(eDSP::generators::ImpulseGenerator, float);
EDSP_DCL_TEMPLATE(eDSP::generators::ImpulseGenerator, double);
