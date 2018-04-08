if (COMPILE_FEATURES_MODULE)
    set(HEADER_FILES  ${HEADER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/feature.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/power.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/duration.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/energy.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/zero_crossing_rate.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/loudness.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/is_silence.hpp
            PARENT_SCOPE)
endif(COMPILE_FEATURES_MODULE)
