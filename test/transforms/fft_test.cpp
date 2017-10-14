//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include <catch.hpp>
#include "transforms/fft.h"

using namespace eDSP::transforms;
SCENARIO("Testing FFT") {

    FFT<double> fft(512);
    fft.setSize(45);


}