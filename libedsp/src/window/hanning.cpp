//
// Created by mohabouje on 21/03/18.
//

#include "window/hanning.h
#include "base/constants.h"
#include <cmath>
using namespace edsp;
Hanning::Hanning(edsp::Window::size_type size) : Window(size) {

}

void Hanning::compute() {
    for (auto  sz = size(), i = 0; i < sz; ++i) {
        data_[i] = 0.5 - 0.5 * std::cos(2 * Constants<double>::pi * i / (sz - 1.0));
    }
}

Hanning::~Hanning() {

}
