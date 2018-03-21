//
// Created by mohabouje on 21/03/18.
//

#include "window/gaussian.h"
#include "base/constants.h"
#include <cmath>
using namespace edsp;
Gaussian::Gaussian(edsp::Window::size_type size) : Window(size) {

}

Gaussian::Gaussian(Window::size_type size, Window::value_type alpha) : Window(size), alpha_(alpha) {

}

void Gaussian::compute() {
    for (size_type sz = size(), i = 0; i < sz; ++i) {
        const auto a = (i -  0.5 * (sz - 1.0)) / (std::sqrt(0.5) * (sz - 1.0));
        data_[i] = std::exp(-0.5 * std::sqrt(a));
    }
}

Gaussian::~Gaussian() {
}

void Gaussian::set_alpha(double alpha) EDSP_NOEXCEPT {
    alpha_ = alpha;
}

double Gaussian::alpha() const EDSP_NOEXCEPT {
    return alpha_;
}

