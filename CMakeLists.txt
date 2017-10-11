cmake_minimum_required(VERSION 3.8)
project(eDSP)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES test/main.cpp test/math/container_test.cpp src/config.h src/base/types.h src/version.h src/math/math_util.h src/math/container.h src/math/stats.h src/base/constants.h src/math/trig.h)

add_executable(runtest ${SOURCE_FILES})
add_library(edsp ${SOURCE_FILES} test/test_db.h test/math/stats_test.cpp test/math/trig_test.cpp src/base/algoritmtemplate.h src/base/interface/ierrornotifier.h src/base/interface/iinitializer.h src/base/error.h)

SET(BASEPATH "${CMAKE_SOURCE_DIR}")

# add include dirs
include_directories("${BASEPATH}/src/")
include_directories("${BASEPATH}/third_party/Catch/include/")