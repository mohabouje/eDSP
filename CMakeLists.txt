cmake_minimum_required(VERSION 3.8)
project(eDSP)

set(CMAKE_CXX_STANDARD 14)
set(SRC_FILES
        src/config.h
        src/version.h
        src/base/constants.h
        src/math/math.h
        src/math/stats.h
        src/math/trig.h
        src/math/complex.h
        src/properties/properties.h
        src/window/window.h
        src/generators/whitenoisegenerator.h
        src/generators/squaregenerator.h
        src/generators/generator.h
        src/generators/singenerator.h
        src/generators/brownnoisegenerator.h
        src/generators/impulsegenerator.h
        src/filters/biquad.h
        src/filters/biquaddesigner.h
        src/utility/template_util.h
        src/utility/map_util.h
        src/utility/vector_util.h
)

set(TEST_FILES
        test/test_util.h
        test/test_config.h
        test/test_db.h
        test/main.cpp
        test/math/stats_test.cpp
        test/utilitity/vectorutil_test.cpp
)

add_library(edsp ${SRC_FILES})
add_executable(runtest ${SRC_FILES} ${TEST_FILES})

SET(BASEPATH "${CMAKE_SOURCE_DIR}")

# add include dirs
include_directories("${BASEPATH}/src/")
include_directories("${BASEPATH}/third_party/Catch/include/")

# For Home Brew correct functionality
list(APPEND CMAKE_PREFIX_PATH /usr/local)
include_directories(/usr/local/include)

find_library(FFTW_LIB NAMES lfftw3 libfftw3 fftw3)
IF (FFTW_LIB)
    message("FFTW_LIB library found, build with fft support")
    set(FFTW_FILES
            src/transforms/fft.h
            src/transforms/ifft.h
            src/transforms/dct.h
            src/transforms/idct.h
            src/transforms/dht.h
            src/frequency/autocorrelation.h
            src/frequency/spectrogram.h
            src/frequency/linearpredictivecoding.h
            src/frequency/cepstrum.h
            )

    set(FFTW_TEST_FILES  test/transforms/fft_test.cpp)
    target_sources(edsp PUBLIC ${FFTW_FILES})
    target_link_libraries(edsp  ${FFTW_LIB})

    target_sources(runtest PUBLIC ${FFTW_FILES} ${FFTW_TEST_FILES})
    target_link_libraries(runtest ${FFTW_LIB})
ELSE()
    message("FFTW_LIB library not found")
ENDIF()