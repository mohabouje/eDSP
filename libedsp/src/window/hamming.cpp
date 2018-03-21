//
// Created by mohabouje on 21/03/18.
//

#include "window/hamming.h"
#include "base/constants.h"
#include <cmath>
using namespace edsp;
Hamming::Hamming(edsp::Window::size_type size) : Window(size) {

}

void Hamming::compute() {
    for (size_type sz = size(), i = 0; i < sz; ++i) {
        data_[i] = 0.53836 - 0.46164 * std::cos(2 * Constants<double>::pi * i / (sz - 1.0));
    }
}

Hamming::~Hamming() {

}
