if (COMPILE_FREQUENCY_MODULE)
    set(HEADER_FILES  ${HEADER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/transform.h
            ${CMAKE_CURRENT_SOURCE_DIR}/autocorrelation.h
            ${CMAKE_CURRENT_SOURCE_DIR}/cepstrum.h
            ${CMAKE_CURRENT_SOURCE_DIR}/dct.h
            ${CMAKE_CURRENT_SOURCE_DIR}/dht.h
            ${CMAKE_CURRENT_SOURCE_DIR}/dft.h
            ${CMAKE_CURRENT_SOURCE_DIR}/idct.h
            ${CMAKE_CURRENT_SOURCE_DIR}/idft.h
            ${CMAKE_CURRENT_SOURCE_DIR}/lpc.h
            ${CMAKE_CURRENT_SOURCE_DIR}/spectrogram.h
            PARENT_SCOPE)
endif(COMPILE_FREQUENCY_MODULE)
