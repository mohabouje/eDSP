cmake_minimum_required(VERSION 3.8)
project(eDSP)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES ${FFTW_INCLUDES}
        src/config.h
        src/base/types.h
        src/version.h
        src/math/math_util.h
        src/math/container.h
        src/math/stats.h
        src/base/constants.h
        src/math/trig.h
        src/base/algoritmtemplate.h
        src/base/ierrornotifier.h
        src/base/iinitializer.h
        src/base/error.h src/window/window.h
        src/generators/whitenoisegenerator.cpp
        src/generators/whitenoisegenerator.h
        src/generators/squaregenerator.cpp
        src/generators/squaregenerator.h
        src/generators/generator.h
        src/generators/singenerator.cpp
        src/generators/singenerator.h
        src/generators/brownnoisegenerator.cpp
        src/generators/brownnoisegenerator.h
        src/properties/energy.cpp
        src/properties/energy.h
        src/properties/loudness.cpp
        src/properties/loudness.h
        src/properties/power.cpp
        src/properties/power.h
        src/properties/strongpeak.cpp
        src/properties/strongpeak.h
        src/properties/zerocrossingrate.cpp
        src/properties/zerocrossingrate.h
        src/transforms/fft.cpp
        src/transforms/fft.h
        src/transforms/ifft.cpp
        src/transforms/ifft.h
        src/transforms/dct.cpp
        src/transforms/dct.h
        src/transforms/idct.cpp
        src/transforms/idct.h
        src/transforms/dht.cpp
        src/transforms/dht.h
        src/frequency/autocorrelation.cpp
        src/frequency/autocorrelation.h
        src/frequency/cepstrum.cpp
        src/frequency/cepstrum.h
)

set(TEST_DIR test)
set(TEST_FILES
        ${TEST_DIR}/main.cpp
        ${TEST_DIR}/test_db.h
        ${TEST_DIR}/math/stats_test.cpp
        ${TEST_DIR}/math/trig_test.cpp
        ${TEST_DIR}/math/container_test.cpp
        ${TEST_DIR}/transforms/fft_test.cpp
        ${TEST_DIR}/test_util.h
        ${TEST_DIR}/test_config.h
)

add_executable(runtest ${SOURCE_FILES} ${TEST_FILES})
add_library(edsp ${SOURCE_FILES} src/frequency/spectrogram.cpp src/frequency/spectrogram.h src/frequency/linearpredictivecoding.cpp src/frequency/linearpredictivecoding.h)

SET(BASEPATH "${CMAKE_SOURCE_DIR}")

# For Home Brew correct functionality
list(APPEND CMAKE_PREFIX_PATH /usr/local)
include_directories(/usr/local/include)

# add include dirs
include_directories("${BASEPATH}/src/")
include_directories("${BASEPATH}/third_party/Catch/include/")

# FFTW integration
include_directories( ${FFTW_INCLUDES} )
target_link_libraries(edsp ${FFTW_LIBRARIES})
target_link_libraries(runtest ${FFTW_LIBRARIES})

