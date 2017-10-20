//
// Created by Mohammed Boujemaoui on 12/10/2017.
//

#include "energy.h"
#include "math/container.h"
using namespace eDSP::properties;

template <typename T>
T Energy<T>::compute(const std::vector<T> &data) const {
    return Math::Container::sum_squares(data);
}
