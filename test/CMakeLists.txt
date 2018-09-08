cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(EasyDSP-Test VERSION 0.0.0 LANGUAGES CXX)
enable_testing()

set(SOURCE_FILES
        testing_catch.cpp
        transform/testing_transforms.cpp
        filter/testing_biquad.cpp
        filter/testing_biquad_designer.cpp
        filter/testing_butterworth.cpp
        filter/testing_chebyshev_i.cpp
        filter/testing_chebyshev_ii.cpp
        standard/testing_autocorrelation.cpp
        standard/testing_crosscorrelation.cpp
        oscillators/testing_oscillators.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
    pthread
    EasyDSP
    fftw3f)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(GTestApp ${PROJECT_NAME}-gtest)
set(SOURCE_FILES_GTEST
        testing_gtest.cpp
        transform/testing_fft.cpp
        windowing/testing_windowing.cpp)

add_executable(GTestApp ${SOURCE_FILES_GTEST})
target_link_libraries(GTestApp
    ${GTEST_LIBRARIES}
    pthread
    EasyDSP
    fftw3f
    fftw3)

target_compile_definitions(GTestApp PRIVATE CURRENT_TEST_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
