if (COMPILE_WINDOWING_MODULE)
    set(HEADER_FILES  ${HEADER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/window.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/hamming.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/hanning.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/blackman.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/kaiser.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/parzen.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/rectangular.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/gaussian.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/barthann.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/bohman.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/triangular.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tukey.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/welch.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/blackman_harris.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/blackman_nuttall.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/flat_top.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/bartlett.hpp
            PARENT_SCOPE)
endif(COMPILE_WINDOWING_MODULE)
