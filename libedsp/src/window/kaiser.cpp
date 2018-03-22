//
// Created by mohabouje on 21/03/18.
//

#include "window/kaiser.h"
using namespace edsp;
Kaiser::Kaiser(edsp::Window::size_type size) : Window(size) {

}

Kaiser::Kaiser(Window::size_type size, Window::value_type beta) : Window(size), beta_(beta) {

}

void Kaiser::compute() {
    // TODO: implement
}

Kaiser::~Kaiser() {

}

void Kaiser::set_beta(Window::value_type beta) EDSP_NOEXCEPT {
    beta_ = beta;
}

Window::value_type Kaiser::beta() const EDSP_NOEXCEPT {
    return beta_;
}

