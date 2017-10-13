//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include "levels/zerocrossingrate.h"
#include "math/math_util.h"
using namespace eDSP::levels;

template <typename T>
T ZeroCrossingRate::compute(const std::vector<T> &data) const {
    int tmp = 0;
    for (size_t i = 0, size = data.size(); i < size; i++) {
        tmp += (Math::Util::sign(data[i]) != Math::Util::sign(data[i - 1])) ? 1 : 0;
    }
    return tmp / static_cast<T>(data.size()) * (norm ? 1 : 100);
}

ZeroCrossingRate::ZeroCrossingRate(bool normalized) : AlgorithmTemplate(true, Error()), norm(normalized) {}

ZeroCrossingRate::ZeroCrossingRate() : AlgorithmTemplate(true, Error()) { }
