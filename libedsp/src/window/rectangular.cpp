//
// Created by mohabouje on 21/03/18.
//

#include "window/rectangular.h"
using namespace edsp;
Rectangular::Rectangular(edsp::Window::size_type size) : Window(size) {

}

void Rectangular::compute() {
    std::fill(begin(), end(), 1.);
}

Rectangular::~Rectangular() {

}
