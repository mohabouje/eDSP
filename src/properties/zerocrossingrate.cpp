//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include "zerocrossingrate.h"
#include "math/math_util.hpp"
using namespace eDSP::properties;

template <typename T>
T ZeroCrossingRate<T>::compute(const std::vector<T> &data) const {
    int tmp = 0;
    for (size_t i = 0, size = data.size(); i < size; i++) {
        tmp += (math::sign(data[i]) != math::sign(data[i - 1])) ? 1 : 0;
    }
    return tmp / static_cast<T>(norm ? data.size() : 1);
}

template <typename T>
ZeroCrossingRate<T>::ZeroCrossingRate(bool normalized) : AlgorithmTemplate(true, Error()), norm(normalized) {}
