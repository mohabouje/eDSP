//
// Created by Mohammed Boujemaoui on 07/12/2017.
//

#include <benchmark/benchmark.h>

#include "window/window.h"
#include "math/complex.h"
#include <utility/vector.h>
#include <frequency/fft.h>
#include <frequency/ifft.h>
#include <frequency/dct.h>
#include <frequency/idct.h>
#include <frequency/dht.h>

using namespace edsp;
static void do_fft(benchmark::State &state) {
    constexpr std::size_t N = 1024;
    std::array<double, N> tmp{};
    std::array<std::complex<double>, N> out{};
    utility::linspace(std::begin(tmp), std::end(tmp), 0, 100);
    frequency::FFT fft;
    fft.compute_r2c(std::begin(tmp), std::end(tmp), std::begin(out));
}

static void do_ifft(benchmark::State &state) {
    constexpr std::size_t N = 1024;
    std::array<double, N> out{};
    std::array<std::complex<double>, N> tmp{};
    frequency::IFFT ifft;
    ifft.compute_c2r(std::begin(tmp), std::end(tmp), std::begin(out));
}


static void do_dct(benchmark::State &state) {
    constexpr std::size_t N = 1024;
    std::array<double, N> tmp{}, out{};
    utility::linspace(std::begin(tmp), std::end(tmp), 0, 100);
    frequency::DCT dct{};
    dct.compute_r2r(std::begin(tmp), std::end(tmp), std::begin(out));
}

static void do_idct(benchmark::State &state) {
    constexpr std::size_t N = 1024;
    std::array<double, N> tmp{}, out{};
    utility::linspace(std::begin(tmp), std::end(tmp), 0, 100);
    frequency::IDCT idct;
    idct.compute_r2r(std::begin(tmp), std::end(tmp), std::begin(out));
}


static void do_dht(benchmark::State &state) {
    constexpr std::size_t N = 1000;
    std::array<double, N> tmp{}, out{};
    utility::linspace(std::begin(tmp), std::end(tmp), 0., (double)N);
    frequency::DHT dht;
    dht.compute_r2r(std::begin(tmp), std::end(tmp), std::begin(out));
}

BENCHMARK(do_fft);
BENCHMARK(do_ifft);
BENCHMARK(do_dct);
BENCHMARK(do_idct);
BENCHMARK(do_dht);


