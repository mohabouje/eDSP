//
// Created by mohabouje on 22/03/18.
//

#include "window/welch.h"
using namespace edsp;

Welch::WelchType Welch::type() const EDSP_NOEXCEPT {
    return type_;
}

void Welch::set_type(const Welch::WelchType type) EDSP_NOEXCEPT {
    type_ = type;
}

Welch::Welch(Window::size_type size) : Window(size) {}

Welch::Welch(Window::size_type size, Welch::WelchType type_) : Window(size), type_(type_) {}

Welch::~Welch() {

}

void Welch::compute() {
    //TODO: Implement
}
