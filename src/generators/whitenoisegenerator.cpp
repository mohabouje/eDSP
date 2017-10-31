//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#include "whitenoisegenerator.h"

using namespace eDSP::generators;

template<typename T>
WhiteNoiseGenerator<T>::WhiteNoiseGenerator(size_t size) : Generator<T>(size) {

}

template <typename T>
const std::vector<T> &WhiteNoiseGenerator<T>::generate() {
    for (size_t i = 0, size = this->data.size(); i < size; i++) {
        this->data[i] = std::rand() / static_cast<T>(RAND_MAX);
    }
    return this->data;
}

EDSP_DCL_TEMPLATE(eDSP::generators::WhiteNoiseGenerator, float);
EDSP_DCL_TEMPLATE(eDSP::generators::WhiteNoiseGenerator, double);