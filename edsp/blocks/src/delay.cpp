//
// Created by mohabouje on 18/02/18.
//

#include "blocks/delay.h"

using namespace edsp::blocks;

Delay::Delay(std::size_t delay, std::size_t maximum_delay) :
        delay_(delay),
        max_delay_(maximum_delay),
        buffer_{std::vector<double>(maximum_delay, 0.)}
{
}

void Delay::set_maximum_delay(const std::size_t value) {
    if (max_delay_ != value) {
        max_delay_ = value;
        buffer_.resize(value);
        reset();
    }
}

void Delay::reset() {
    utility::set(std::begin(buffer_), std::end(buffer_), 0);
    input_point_ = 0;
    output_point_ = 0;
}
