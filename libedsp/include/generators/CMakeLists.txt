option(COMPILE_GENERATORS "Compiles the Generators module" ON)
if (COMPILE_GENERATORS)
    set(HEADER_FILES  ${HEADER_FILES}
            include/generators/generators.h
            include/generators/generator.h
            include/generators/singenerator.h
            include/generators/time_series_generator.h
            include/generators/periodic_generator.h
            include/generators/triangular_pulse_generator.cpp
            include/generators/triangular_pulse_generator.h
            PARENT_SCOPE)


    set(SOURCE_FILES  ${SOURCE_FILES}
            src/generators/singenerator.cpp
            PARENT_SCOPE)
endif(COMPILE_GENERATORS)