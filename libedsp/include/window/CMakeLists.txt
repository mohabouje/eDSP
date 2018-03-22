option(COMPILE_WINDOWING "Compiles the Windowing module" ON)
if (COMPILE_WINDOWING)
    set(HEADER_FILES  ${HEADER_FILES}
            include/window/window.h
            include/window/hamming.h
            include/window/hanning.h
            include/window/blackman.h
            include/window/kaiser.h
            include/window/parzen.h
            include/window/rectangular.h
            include/window/gaussian.h
            include/window/barthann.h
            include/window/bohman.h
            include/window/triangular.h
            include/window/tukey.h
            include/window/welch.h
            include/window/blackman_harris.h
            include/window/blackman_nuttall.h
            include/window/flat_top.h
            include/window/bartlett.h
            PARENT_SCOPE)

    set(SOURCE_FILES  ${SOURCE_FILES}
            src/window/hamming.cpp
            src/window/hanning.cpp
            src/window/blackman.cpp
            src/window/parzen.cpp
            src/window/rectangular.cpp
            src/window/gaussian.cpp
            src/window/barthann.cpp
            src/window/bohman.cpp
            src/window/triangular.cpp
            src/window/tukey.cpp
            src/window/welch.cpp
            src/window/kaiser.cpp
            src/window/blackman_harris.cpp
            src/window/blackman_nuttall.cpp
            src/window/flat_top.cpp
            src/window/bartlett.cpp
            PARENT_SCOPE)
endif(COMPILE_WINDOWING)