option(COMPILE_AUDIO_BLOCKS_MODULE "Compiles the AUDIO BLOCKS module" ON)
if (COMPILE_AUDIO_BLOCKS_MODULE)
    set(HEADER_FILES  ${HEADER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/delay.h
            ${CMAKE_CURRENT_SOURCE_DIR}/echo.h
            ${CMAKE_CURRENT_SOURCE_DIR}/envelope_detector.h
            ${CMAKE_CURRENT_SOURCE_DIR}/fadein.h
            ${CMAKE_CURRENT_SOURCE_DIR}/fadeout.h
            ${CMAKE_CURRENT_SOURCE_DIR}/gain.h
            ${CMAKE_CURRENT_SOURCE_DIR}/multichannel_to_mono_converter.h
            ${CMAKE_CURRENT_SOURCE_DIR}/mute.h
            ${CMAKE_CURRENT_SOURCE_DIR}/peak_picker.h
            PARENT_SCOPE)

    set(SOURCE_FILES  ${SOURCE_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/delay.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/echo.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/envelope_detector.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/fadeout.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/fadein.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/gain.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/multichannel_to_mono_converter.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/peak_picker.cpp
            PARENT_SCOPE)

    include_directories(include)
endif(COMPILE_AUDIO_BLOCKS_MODULE)