//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include "loudness.h"
#include "math/container.hpp"
using namespace eDSP::properties;

template <typename T>
T Loudness<T>::compute(const std::vector<T> &data) const {
    static constexpr T StevenLawLevel = static_cast<T>(0.67);
    return std::pow(math::sum_squares(data), StevenLawLevel);
}
