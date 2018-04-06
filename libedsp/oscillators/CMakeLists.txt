option(COMPILE_OSCILLATORS_MODULE "Compiles the OSCILLATORS module" ON)
if (COMPILE_OSCILLATORS_MODULE)
    set(HEADER_FILES  ${HEADER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/oscillator.h
            ${CMAKE_CURRENT_SOURCE_DIR}/sin.h
            ${CMAKE_CURRENT_SOURCE_DIR}/triangle.h
            ${CMAKE_CURRENT_SOURCE_DIR}/square.h
            ${CMAKE_CURRENT_SOURCE_DIR}/sawtooth.h
            PARENT_SCOPE)


    set(SOURCE_FILES  ${SOURCE_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/sin.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/square.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/sawtooth.cpp
            PARENT_SCOPE)

    include_directories(include)
endif(COMPILE_OSCILLATORS_MODULE)