//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include "power.h"
#include "math/container.h"
using namespace eDSP::properties;

template <typename T>
T Power<T>::compute(const std::vector<T> &data) const {
    return Math::Container::sum_squares(data) / static_cast<T>(data.size());
}