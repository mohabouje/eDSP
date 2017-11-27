cmake_minimum_required(VERSION 3.8)
project(eDSP)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES ${FFTW_INCLUDES}
        src/config.h
        src/base/types.h
        src/version.h
        src/math/math_util.hpp
        src/math/container.hpp
        src/math/stats.hpp
        src/base/constants.h
        src/math/trig.hpp
        src/base/algoritmtemplate.h
        src/base/ierrornotifier.h
        src/base/iinitializer.h
        src/base/error.h src/window/window.hpp
        src/generators/whitenoisegenerator.cpp
        src/generators/whitenoisegenerator.h
        src/generators/squaregenerator.cpp
        src/generators/squaregenerator.h
        src/generators/generator.h
        src/generators/singenerator.cpp
        src/generators/singenerator.h
        src/generators/twosingenerator.cpp
        src/generators/twosingenerator.h
        src/generators/brownnoisegenerator.cpp
        src/generators/brownnoisegenerator.h
        src/generators/impulsegenerator.h
        src/generators/impulsegenerator.cpp
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
        src/filters/biquad.h
        src/filters/biquaddesigner.h
        src/math/complex.hpp
)

set(TEST_DIR test)
set(TEST_FILES
        ${TEST_DIR}/main.cpp
        ${TEST_DIR}/test_db.h
        ${TEST_DIR}/math/stats_test.cpp
        ${TEST_DIR}/math/trig_test.cpp
        ${TEST_DIR}/math/container_test.cpp
        ${TEST_DIR}/test_util.h
        ${TEST_DIR}/test_config.h
        )

add_executable(runtest ${SOURCE_FILES} ${TEST_FILES})
add_library(edsp ${SOURCE_FILES})

SET(BASEPATH "${CMAKE_SOURCE_DIR}")

# add include dirs
include_directories("${BASEPATH}/src/")
include_directories("${BASEPATH}/third_party/Catch/include/")

# For Home Brew correct functionality
list(APPEND CMAKE_PREFIX_PATH /usr/local)
include_directories(/usr/local/include)

find_library(FFTW_LIB NAMES lfftw3 libfftw3 fftw3)
IF (FFTW_LIB)
    message("FFTW_LIB library found, build ")
    set(FFTW_FILES
            src/transforms/fft.hpp
            src/transforms/ifft.hpp
            src/transforms/dct.hpp
            src/transforms/idct.hpp
            src/transforms/dht.hpp
           # src/frequency/autocorrelation.cpp
           # src/frequency/autocorrelation.h
           # src/frequency/spectrogram.cpp
           # src/frequency/spectrogram.h
           # src/frequency/linearpredictivecoding.cpp
           # src/frequency/linearpredictivecoding.h
           # src/frequency/cepstrum.cpp
           # src/frequency/cepstrum.h
            )

    set(FFTW_TEST_FILES
            test/transforms/fft_test.cpp)
    target_sources(edsp PUBLIC ${FFTW_FILES})
    target_link_libraries(edsp ${FFTW_LIB})

    target_sources(runtest PUBLIC ${FFTW_FILES} ${FFTW_TEST_FILES})
    target_link_libraries(runtest ${FFTW_LIB})
ELSE()
    message("FFTW_LIB library not found")
ENDIF()