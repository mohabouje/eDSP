//
// Created by Mohammed Boujemaoui on 08/12/2017.
//

#include <benchmark/benchmark.h>
#include <window/window.h>
#include <numeric>

using namespace edsp;

template <class InputIterator>
constexpr bool find(InputIterator __first, InputIterator __last, typename std::iterator_traits<InputIterator>::value_type const& __Tp) {
    std::find(__first, __last, __Tp);
    for (; __first != __last; ++__first) {
        if (*__first == __Tp) return true;
    }
    return false;
}


static void do_hamming(benchmark::State &state) {
    constexpr std::size_t N = 1024;
    constexpr std::array<double, N> tmp{};
    find(std::begin(tmp), std::end(tmp), 8);
    std::accumulate()
}

static void do_hanning(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    window::hanning(std::begin(tmp), std::end(tmp));
}

static void do_hanningz(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    window::hanningz(std::begin(tmp), std::end(tmp));
}

static void do_gaussian(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    window::gaussian(std::begin(tmp), std::end(tmp));
}

static void do_blackman(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    window::blackman(std::begin(tmp), std::end(tmp));
}

static void do_blackmanharris(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    window::blackmanharris(std::begin(tmp), std::end(tmp));
}

static void do_parzen(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    window::parzen(std::begin(tmp), std::end(tmp));
}

static void do_welch(benchmark::State &state) {
    const std::size_t N = 1024;
    std::array<double, N> tmp{};
    window::welch(std::begin(tmp), std::end(tmp));
}


BENCHMARK(do_hamming);
BENCHMARK(do_hanning);
BENCHMARK(do_hanningz);
BENCHMARK(do_gaussian);
BENCHMARK(do_blackman);
BENCHMARK(do_blackmanharris);
BENCHMARK(do_parzen);
BENCHMARK(do_welch);
