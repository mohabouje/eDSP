//
// Created by mohabouje on 22/03/18.
//

#include "window/welch.h"
using namespace edsp;


Welch::Welch(Window::size_type size) : Window(size) {}

Welch::Welch(Window::size_type size, WindowType type) : Window(size, type) {

}

Welch::~Welch() = default;

void Welch::compute() {
    //TODO: Implement
}
