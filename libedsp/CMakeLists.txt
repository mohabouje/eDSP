set(HEADER_FILES
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
        )

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
        src/frequency/lpc.cpp)


include_directories(./include)
add_library(libedsp ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(libedsp ${FFTW_LIB})
