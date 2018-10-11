cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(extension VERSION 0.0.1 LANGUAGES C CXX)

set(LIB_NAME ${PROJECT_NAME})
set(VERSION_MAJOR       "0")
set(VERSION_MINOR       "0")
set(VERSION_PATCH       "1")

find_library(BENCHMARK NAMES lbenchmark libbenchmark benchmark)
if (BENCHMARK)
    set(BENCHMARK_LIBS ${BENCHMARK} -lpthread)
else()
    message(FATAL_ERROR "GOOGLE BENCHMARK library not found")
endif(BENCHMARK)

add_executable(edsp-fft-benchmark benchmark_fft.cpp)
target_link_libraries(edsp-fft-benchmark eDSP fftw3 fftw3f pffft ${BENCHMARK_LIBS})

find_library(BENCHMARK NAMES lbenchmark libbenchmark benchmark)
