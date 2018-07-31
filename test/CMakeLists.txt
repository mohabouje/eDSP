cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(EasyDSP-Test VERSION 0.0.0 LANGUAGES CXX)
enable_testing()

set(SOURCE_FILES
        testing_dsp.cpp
        transform/testing_transforms.cpp
        filter/testing_biquad.cpp
        standard/testing_autocorrelation.cpp
        standard/testing_crosscorrelation.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES}
    pthread
    EasyDSP
    EasyMeta
    fftw3f)
