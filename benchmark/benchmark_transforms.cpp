//
// Created by Mohammed Boujemaoui on 07/12/2017.
//

#include <benchmark/benchmark.h>

#include "window/window.h"
#include "math/complex.h"
#include <transforms/fft.h>
#include <transforms/ifft.h>
#include <transforms/dct.h>
#include <transforms/idct.h>
#include <transforms/dht.h>

using namespace eDSP;
static void do_fft(benchmark::State &state) {

    const auto a = window::hamming<std::vector<double>>(1024);
    transforms::FFT<double, 4096> fft;
    const auto& b = fft.compute(math::complex::real_to_complex(a));
    int c = 7;
 }

BENCHMARK(do_fft);