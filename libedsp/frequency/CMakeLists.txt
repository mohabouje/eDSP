option(COMPILE_FREQUENCY "Compiles the Frequency module" ON)
if (COMPILE_FREQUENCY)
    set(HEADER_FILES  ${HEADER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/autocorrelation.h
            ${CMAKE_CURRENT_SOURCE_DIR}/cepstrum.h
            ${CMAKE_CURRENT_SOURCE_DIR}/dct.h
            ${CMAKE_CURRENT_SOURCE_DIR}/dht.h
            ${CMAKE_CURRENT_SOURCE_DIR}/fft.h
            ${CMAKE_CURRENT_SOURCE_DIR}/idct.h
            ${CMAKE_CURRENT_SOURCE_DIR}/ifft.h
            ${CMAKE_CURRENT_SOURCE_DIR}/lpc.h
            ${CMAKE_CURRENT_SOURCE_DIR}/spectrogram.h
            PARENT_SCOPE)

    set(SOURCE_FILES  ${SOURCE_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/dct.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/idct.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/lpc.cpp
            PARENT_SCOPE)

    include_directories(include)
endif(COMPILE_FREQUENCY)