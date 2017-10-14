//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include "strongpeak.h"
#include <iterator>
#include <algorithm>
using namespace eDSP::levels;

template <typename T>
std::pair<int, T> StrongPeak<T>::compute(const std::vector<T> &data) const {
    const typename std::vector<T>::const_iterator it = std::max_element(data.begin(), data.end());
    return std::pair<int, T>(std::distance(data.begin(), it), *it);
}


