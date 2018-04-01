option(COMPILE_OSCILLATORS "Compiles the oscillators module" ON)
if (COMPILE_OSCILLATORS)
    set(HEADER_FILES  ${HEADER_FILES}
            include/oscillators/oscillator.h
            include/oscillators/sin.h
            include/oscillators/triangle.h
            include/oscillators/square.h
            include/oscillators/sawtooth.h
            PARENT_SCOPE)


    set(SOURCE_FILES  ${SOURCE_FILES}
            src/oscillators/sin.cpp
            src/oscillators/square.cpp
            src/oscillators/triangle.cpp
            src/oscillators/sawtooth.cpp
            PARENT_SCOPE)

endif(COMPILE_OSCILLATORS)