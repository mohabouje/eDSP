//
// Created by Mohammed Boujemaoui on 08/12/2017.
//

#include <benchmark/benchmark.h>
#include <utility/vector.h>
#include <array>

using namespace eDSP;
static void do_floor(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    utility::floor(std::begin(tmp), std::end(tmp));
}

static void do_ceil(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    utility::ceil(std::begin(tmp), std::end(tmp));
}

static void do_sum(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    utility::sum(std::begin(tmp), std::end(tmp));
}

static void do_sum_squares(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    utility::sum_squares(std::begin(tmp), std::end(tmp));
}

static void do_inv(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    utility::inv(std::begin(tmp), std::end(tmp));
}

static void do_log10(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    utility::log10(std::begin(tmp), std::end(tmp));
}

static void do_log2(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    utility::log2(std::begin(tmp), std::end(tmp));
}

static void do_ln(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    utility::ln(std::begin(tmp), std::end(tmp));
}


static void do_square(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    utility::square(std::begin(tmp), std::end(tmp));
}


static void do_linspace(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    utility::linspace(std::begin(tmp), std::end(tmp), 0., 10.);
}


BENCHMARK(do_ceil);
BENCHMARK(do_floor);
BENCHMARK(do_sum);
BENCHMARK(do_sum_squares);
BENCHMARK(do_square);
BENCHMARK(do_inv);
BENCHMARK(do_linspace);
BENCHMARK(do_ln);
BENCHMARK(do_log2);
BENCHMARK(do_log10);


