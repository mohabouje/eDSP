//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include "levels/zerocrossingrate.h"
#include "math/math_util.h"
using namespace eDSP::properties;

template <typename T>
T ZeroCrossingRate<T>::compute(const std::vector<T> &data) const {
    int tmp = 0;
    for (size_t i = 0, size = data.size(); i < size; i++) {
        tmp += (Math::Util::sign(data[i]) != Math::Util::sign(data[i - 1])) ? 1 : 0;
    }
    return tmp / static_cast<T>(data.size()) * (norm ? 1 : 100);
}

template <typename T>
ZeroCrossingRate<T>::ZeroCrossingRate(bool normalized) : AlgorithmTemplate(true, Error()), norm(normalized) {}

template <typename T>
ZeroCrossingRate<T>::ZeroCrossingRate() : AlgorithmTemplate(true, Error()) { }
