option(COMPILE_FILTERS "Compiles the Filters module" ON)
if (COMPILE_FILTERS)
    set(HEADER_FILES  ${HEADER_FILES}
            include/filters/biquad.h
            include/filters/biquaddesigner.h
            include/filters/dcremoval.h
            include/filters/fir.h
            PARENT_SCOPE)

    set(SOURCE_FILES  ${SOURCE_FILES}
            src/filters/biquaddesigner.cpp
            src/filters/fir.cpp
            PARENT_SCOPE)
endif(COMPILE_FILTERS)