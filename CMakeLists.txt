cmake_minimum_required(VERSION 3.8)
project(eDSP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/config.h src/base/types.h src/version.h src/math/math_util.h src/math/container.h)

add_executable(runtest ${SOURCE_FILES})
add_library(edsp ${SOURCE_FILES} src/math/stats.h)

SET(BASEPATH "${CMAKE_SOURCE_DIR}")

# add include dirs
include_directories("${BASEPATH}/src/")
include_directories("${BASEPATH}/third_party/Catch/include/")