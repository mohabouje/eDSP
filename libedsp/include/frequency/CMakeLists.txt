option(COMPILE_FREQUENCY "Compiles the Frequency module" ON)
if (COMPILE_FREQUENCY)
    set(HEADER_FILES  ${HEADER_FILES}
            include/frequency/autocorrelation.h
            include/frequency/cepstrum.h
            include/frequency/dct.h
            include/frequency/dht.h
            include/frequency/fft.h
            include/frequency/idct.h
            include/frequency/ifft.h
            include/frequency/lpc.h
            include/frequency/spectrogram.h
            PARENT_SCOPE)

    set(SOURCE_FILES  ${SOURCE_FILES}
            src/frequency/dct.cpp
            src/frequency/idct.cpp
            src/frequency/lpc.cpp
            PARENT_SCOPE)
endif(COMPILE_FREQUENCY)