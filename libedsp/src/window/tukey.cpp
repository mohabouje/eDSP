//
// Created by mohabouje on 22/03/18.
//

#include "window/tukey.h"
using namespace edsp;

void Tukey::set_ratio(const edsp::Window::value_type ratio) EDSP_NOEXCEPT {
    ratio_ = ratio;
}

Window::value_type Tukey::ratio() const EDSP_NOEXCEPT {
    return ratio_;
}

Tukey::~Tukey() {

}

void Tukey::compute() {
// TODO: implement
}

Tukey::Tukey(Window::size_type size) : Window(size) {}

Tukey::Tukey(Window::size_type size, Window::value_type ratio_) : Window(size), ratio_(ratio_) {}

