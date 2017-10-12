//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#include "whitenoise.h"

using namespace eDSP::generators;
WhiteNoise::WhiteNoise(size_t size) : Generator(size) {

}

template <typename T>
const std::vector<T> &WhiteNoise::generate() {
    for (size_t i = 0, size = data.size(); i < size; i++) {
        data[i] = std::rand() / static_cast<T>(RAND_MAX);
    }
    return data;
}



