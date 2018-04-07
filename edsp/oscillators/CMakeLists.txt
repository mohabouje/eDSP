option(COMPILE_OSCILLATORS_MODULE "Compiles the OSCILLATORS module" ON)
if (COMPILE_OSCILLATORS_MODULE)
    set(HEADER_FILES  ${HEADER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/oscillator.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/sin.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/triangle.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/square.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/sawtooth.hpp
            PARENT_SCOPE)

    include_directories(include)
endif(COMPILE_OSCILLATORS_MODULE)
