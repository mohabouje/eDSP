//
// Created by mohabouje on 21/03/18.
//


#include "window/blackman.h"
#include "base/constants.h"
#include <cmath>
using namespace edsp;
Blackman::Blackman(edsp::Window::size_type size) : Window(size) {

}

void Blackman::compute() {
    for (size_type sz = size(), i = 0; i < sz; ++i) {
        data_[i] = 0.42 - 0.5 * std::cos(2 * Constants<double>::pi * i / (sz - 1.0f))
                   + 0.08 * std::cos((4 * Constants<double>::pi * i) / (sz - 1.0f));
    }
}

Blackman::~Blackman() {

}
