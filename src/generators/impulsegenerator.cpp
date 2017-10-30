#include "impulsegenerator.h"
#include "math/container.h"
using namespace eDSP::generators;

template<typename T>
const std::vector<T> &ImpulseGenerator<T>::generate() {
    this->data[0] = this->amplitude;
    return this->data;
}

template<typename T>
ImpulseGenerator<T>::ImpulseGenerator(size_t size, T amplitude) :
        Generator<T>(size, amplitude) {
}
EDSP_DCL_TEMPLATE(eDSP::generators::ImpulseGenerator, float);
EDSP_DCL_TEMPLATE(eDSP::generators::ImpulseGenerator, double);
