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
    for (size_t i = 0, size = Generator<T>::data.size(); i < size; i++) {
        Generator<T>::data[i] = std::rand() / static_cast<T>(RAND_MAX);
    }
    return Generator<T>::data;
}

EDSP_DCL_TEMPLATE(eDSP::generators::WhiteNoiseGenerator, float);
EDSP_DCL_TEMPLATE(eDSP::generators::WhiteNoiseGenerator, double);