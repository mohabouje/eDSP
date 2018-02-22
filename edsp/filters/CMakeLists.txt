option(COMPILE_FREQUENCY "Compiles the Frequency module" ON)
if (COMPILE_FREQUENCY)
    set(HEADER_FILES  ${HEADER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/biquad.h
            ${CMAKE_CURRENT_SOURCE_DIR}/biquaddesigner.h
            ${CMAKE_CURRENT_SOURCE_DIR}/dcremoval.h
            ${CMAKE_CURRENT_SOURCE_DIR}/fir.h
            PARENT_SCOPE)

    set(SOURCE_FILES  ${SOURCE_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/biquaddesigner.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/fir.cpp
            PARENT_SCOPE)

    include_directories(include)
endif(COMPILE_FREQUENCY)