set(HEADER_FILES
        include/config.h
        include/version.h
        include/base/analog_filter.h
        include/base/constants.h
        include/base/sfinae.h
        include/base/transform.h
        include/base/types.h
        include/blocks/delay.h
        include/blocks/echo.h
        include/blocks/envelope_detector.h
        include/blocks/fadein.h
        include/blocks/fadeout.h
        include/blocks/gain.h
        include/blocks/multichannel_to_mono_converter.h
        include/blocks/mute.h
        include/blocks/peak_picker.h
        include/filters/biquad.h
        include/filters/biquaddesigner.h
        include/filters/dcremoval.h
        include/filters/fir.h
        include/frequency/autocorrelation.h
        include/frequency/cepstrum.h
        include/frequency/dct.h
        include/frequency/dht.h
        include/frequency/fft.h
        include/frequency/idct.h
        include/frequency/ifft.h
        include/frequency/lpc.h
        include/frequency/spectrogram.h
        include/generators/generators.h
        include/math/complex.h
        include/math/math.h
        include/math/stats.h
        include/math/trig.h
        include/properties/properties.h
        include/utility/converter.h
        include/utility/map.h
        include/utility/vector.h
        include/window/window.h
        include/window/hamming.h
        include/window/hanning.h
        include/window/blackman.h
        include/window/kaiser.h
        include/window/parzen.h)

set(SOURCE_FILES
        src/blocks/delay.cpp
        src/blocks/echo.cpp
        src/blocks/envelope_detector.cpp
        src/blocks/fadeout.cpp
        src/blocks/fadein.cpp
        src/blocks/gain.cpp
        src/blocks/multichannel_to_mono_converter.cpp
        src/blocks/peak_picker.cpp

        src/filters/biquaddesigner.cpp
        src/filters/fir.cpp
        src/frequency/dct.cpp
        src/frequency/idct.cpp
        src/frequency/lpc.cpp
        src/window/hamming.cpp
        src/window/hanning.cpp
        src/window/blackman.cpp
        src/window/parzen.cpp
        src/window/rectangular.cpp include/window/rectangular.h src/window/gaussian.cpp include/window/gaussian.h src/window/barthann.cpp include/window/barthann.h src/window/bohman.cpp include/window/bohman.h src/window/triangular.cpp include/window/triangular.h src/window/tukey.cpp include/window/tukey.h src/window/welch.cpp include/window/welch.h src/window/kaiser.cpp src/window/blackman_harris.cpp include/window/blackman_harris.h src/window/blackman_nuttall.cpp include/window/blackman_nuttall.h src/window/flat_top.cpp include/window/flat_top.h src/window/bartlett.cpp include/window/bartlett.h)


add_library(libedsp ${HEADER_FILES} ${SOURCE_FILES})
include_directories(./include/)

find_library(FFTW_LIB NAMES lfftw3 libfftw3 fftw3 REQUIRED)
target_link_libraries(libedsp ${FFTW_LIB})
target_include_directories(libedsp PUBLIC ./include/)
