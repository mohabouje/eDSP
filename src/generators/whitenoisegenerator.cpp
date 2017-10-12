//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#include "whitenoisegenerator.h"

using namespace eDSP::generators;
WhiteNoiseGenerator::WhiteNoiseGenerator(size_t size) : Generator(size) {

}

template <typename T>
const std::vector<T> &WhiteNoiseGenerator::generate() {
    for (size_t i = 0, size = data.size(); i < size; i++) {
        data[i] = std::rand() / static_cast<T>(RAND_MAX);
    }
    return data;
}



