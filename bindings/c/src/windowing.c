/*
* eDSP, A cross-platform Digital Signal Processing library written in modern C++.
* Copyright (C) 2019 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 3 of the License, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along width
* this program.  If not, see <http://www.gnu.org/licenses/>
*
* Filename: windowing.c
* Author: Mohammed Boujemaoui
* Date: 26/03/19
*/

#include "cedsp/windowing.h"
#include <edsp/windowing.hpp>

void bartlett(real_t* window, int N) {
    edsp::windowing::bartlett(window, window + N);
}

void blackman(real_t* window, int N) {
    edsp::windowing::blackman(window, window + N);
}

void blackman_harris(real_t* window, int N) {
    edsp::windowing::blackman_harris(window, window + N);
}

void blackman_nutall(real_t* window, int N) {
    edsp::windowing::blackman_nutall(window, window + N);
}

void boxcar(real_t* window, int N) {
    edsp::windowing::boxcar(window, window + N);
}

void flattop(real_t* window, int N) {
    edsp::windowing::flattop(window, window + N);
}

void hamming(real_t* window, int N) {
    edsp::windowing::hamming(window, window + N);
}

void hanning(real_t* window, int N) {
    edsp::windowing::hanning(window, window + N);
}

void triangular(real_t* window, int N) {
    edsp::windowing::triangular(window, window + N);
}

void welch(real_t* window, int N) {
    edsp::windowing::welch(window, window + N);
}

void rectangular(real_t* window, int N) {
    edsp::windowing::rectangular(window, window + N);
}
