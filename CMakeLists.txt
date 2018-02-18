cmake_minimum_required(VERSION 3.8)
project(eDSP)
set(CMAKE_CXX_STANDARD 17)


# add include dirs
find_library(FFTW_LIB NAMES lfftw3 libfftw3 fftw3 REQUIRED)
find_library(BENCHMARK_LIB NAMES lbenchmark libbenchmark benchmark REQUIRED)

enable_testing ()
add_subdirectory (libedsp)
add_subdirectory (benchmark)
add_subdirectory (test)