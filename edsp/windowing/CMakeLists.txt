option(COMPILE_WINDOWING_MODULE "Compiles the WINDOWING module" ON)
if (COMPILE_WINDOWING_MODULE)
    set(HEADER_FILES  ${HEADER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/window.h
            ${CMAKE_CURRENT_SOURCE_DIR}/hamming.h
            ${CMAKE_CURRENT_SOURCE_DIR}/hanning.h
            ${CMAKE_CURRENT_SOURCE_DIR}/blackman.h
            ${CMAKE_CURRENT_SOURCE_DIR}/kaiser.h
            ${CMAKE_CURRENT_SOURCE_DIR}/parzen.h
            ${CMAKE_CURRENT_SOURCE_DIR}/rectangular.h
            ${CMAKE_CURRENT_SOURCE_DIR}/gaussian.h
            ${CMAKE_CURRENT_SOURCE_DIR}/barthann.h
            ${CMAKE_CURRENT_SOURCE_DIR}/bohman.h
            ${CMAKE_CURRENT_SOURCE_DIR}/triangular.h
            ${CMAKE_CURRENT_SOURCE_DIR}/tukey.h
            ${CMAKE_CURRENT_SOURCE_DIR}/welch.h
            ${CMAKE_CURRENT_SOURCE_DIR}/blackman_harris.h
            ${CMAKE_CURRENT_SOURCE_DIR}/blackman_nuttall.h
            ${CMAKE_CURRENT_SOURCE_DIR}/flat_top.h
            ${CMAKE_CURRENT_SOURCE_DIR}/bartlett.h
            PARENT_SCOPE)

    set(SOURCE_FILES  ${SOURCE_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/hamming.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/hanning.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/blackman.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/parzen.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/rectangular.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/gaussian.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/barthann.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/bohman.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/triangular.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/tukey.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/welch.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/kaiser.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/blackman_harris.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/blackman_nuttall.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/flat_top.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/bartlett.cpp
            PARENT_SCOPE)


    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
endif(COMPILE_WINDOWING_MODULE)