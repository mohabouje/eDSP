option(COMPILE_AUDIO_BLOCKS "Compiles the AudioBlocks module" ON)
if (COMPILE_AUDIO_BLOCKS)
    set(HEADER_FILES  ${HEADER_FILES}
            include/blocks/delay.h
            include/blocks/echo.h
            include/blocks/envelope_detector.h
            include/blocks/fadein.h
            include/blocks/fadeout.h
            include/blocks/gain.h
            include/blocks/multichannel_to_mono_converter.h
            include/blocks/mute.h
            include/blocks/peak_picker.h
            PARENT_SCOPE)

    set(SOURCE_FILES  ${SOURCE_FILES}
            src/blocks/delay.cpp
            src/blocks/echo.cpp
            src/blocks/envelope_detector.cpp
            src/blocks/fadeout.cpp
            src/blocks/fadein.cpp
            src/blocks/gain.cpp
            src/blocks/multichannel_to_mono_converter.cpp
            src/blocks/peak_picker.cpp
            PARENT_SCOPE)
endif(COMPILE_AUDIO_BLOCKS)