cmake_minimum_required(VERSION 3.8)
project(eDSP)
set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_PREFIX_PATH /usr/local)
include_directories(/usr/local/include)

# add include dirs
include_directories("${CMAKE_SOURCE_DIR}/include/")
find_library(FFTW_LIB NAMES lfftw3 libfftw3 fftw3)
find_library(BENCHMARK_LIB NAMES lbenchmark libbenchmark benchmark)

enable_testing ()
add_subdirectory (benchmark)
add_subdirectory (test)