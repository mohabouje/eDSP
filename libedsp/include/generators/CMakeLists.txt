option(COMPILE_GENERATORS "Compiles the Generators module" ON)
if (COMPILE_GENERATORS)
    set(HEADER_FILES  ${HEADER_FILES}
            include/generators/generators.h
            include/generators/generator.h
            include/generators/sin_generator.h
            include/generators/time_series_generator.h
            include/generators/periodic_generator.h
            include/generators/triangular_pulse_generator.h
            include/generators/square_pulse_generator.h
            include/generators/sawtooth_generator.h
            PARENT_SCOPE)


    set(SOURCE_FILES  ${SOURCE_FILES}
            src/generators/sin_generator.cpp
            src/generators/square_pulse_generator.cpp
            src/generators/triangular_pulse_generator.cpp
            src/generators/square_pulse_generator.cpp
            src/generators/sawtooth_generator.cpp
            PARENT_SCOPE)
endif(COMPILE_GENERATORS)