//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include "loudness.h"
#include "math/container.h"
using namespace eDSP::levels;

template <typename T>
T Loudness<T>::compute(const std::vector<T> &data) const {
    static constexpr T StevenLawLevel = static_cast<T>(0.67);
    return std::pow(Math::Container::sum_squares(data), StevenLawLevel);
}
