/*
* edsp, Yet another framework for building deep RNN networks written in modern C++.
*
* The 2-Clause BSD License
*
* Copyright (c) 2019 Mohammed Boujemaoui Boulaghmoudi,
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Filename: algorithm.c
* Author: Mohammed Boujemaoui
* Date: 26/03/19
*/

#include "algorithm.h"
#include <edsp/algorithm.hpp>


void array_scale(const real_t *input, int size, real_t *output, real_t factor) {
    edsp::amplifier(input, input + size, output, factor);
}


void array_scale_clip(const real_t *input, int size, real_t *output, real_t factor, real_t min, real_t max) {
    edsp::amplifier(input, input + size, output, factor, min, max);
}

void array_ceil(const real_t *input, int size, real_t *output) {
    edsp::ceil(input, input + size, output);
}

void array_floor(const real_t *input, int size, real_t *output) {
    edsp::floor(input, input + size, output);
}

void array_round(const real_t *input, int size, real_t *output) {
    edsp::round(input, input + size, output);
}

void array_clip(const real_t *input, int size, real_t *output, real_t min, real_t max) {
    edsp::clipper(input, input+size, output, min, max);
}

void array_concatenate(const real_t *left, int size_left, const real_t *right, int size_right, real_t *output) {
    edsp::concatenate(left, left + size_left, right, right + size_right, output);
}

void array_trunc(const real_t *input, int size, real_t *output) {
    edsp::fix(input, input + size, output);
}

void array_linspace(real_t *output, int size, real_t x1, real_t x2) {
    edsp::linspace(output, x1, x2, size);
}

void array_logspace(real_t *output, int size, real_t x1, real_t x2) {
    edsp::logspace(output, x1, x2, size);
}

void array_abs(const real_t *input, int size, real_t *output) {
    edsp::rectify(input, input + size, output);
}

void array_normalize(const real_t *input, int size, real_t *output) {
    edsp::normalize(input, input + size, output);
}

void array_padder(const real_t *input, int input_size, real_t *output, int output_size) {
    edsp::padder(input, input + input_size, output, output + output_size);
}

int equal(const real_t *left, int size, const real_t *right) {
    return edsp::equal(left, left + size, right, right + size);
}

int binary_search(const real_t *input, int size, real_t value) {
    const auto end = input + size;
    const auto iter = edsp::binary_search(input, end, value);
    if (iter != end) {
        return static_cast<int>(std::distance(input, iter));
    } else {
        return -1;
    }
}

int index_of(const real_t *input, int size, real_t value) {
    return edsp::index_of(input, input + size, value);
}

int linear_search(const real_t *input, int size, real_t value) {
    const auto end = input + size;
    const auto iter = edsp::linear_search(input, end, value);
    if (iter != end) {
        return static_cast<int>(std::distance(input, iter));
    } else {
        return -1;
    }
}

int contains(const real_t *input, int size, real_t value) {
    const auto end = input + size;
    const auto iter = edsp::linear_search(input, end, value);
    return iter != end;
}
