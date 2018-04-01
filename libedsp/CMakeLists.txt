
set(HEADER_FILES
        include/config.h
        include/version.h
        include/base/analog_filter.h
        include/base/constants.h
        include/base/sfinae.h
        include/base/transform.h
        include/base/types.h
        include/math/complex.h
        include/math/math.h
        include/math/stats.h
        include/math/trig.h
        include/properties/properties.h
        include/utility/converter.h
        include/utility/map.h
        include/utility/vector.h
)

set(SOURCE_FILES )


add_subdirectory(include/window)
add_subdirectory(include/frequency)
add_subdirectory(include/filters)
add_subdirectory(include/oscillators)
add_subdirectory(include/blocks)
add_library(libedsp ${HEADER_FILES} ${SOURCE_FILES})



include_directories(./include/)

find_library(FFTW_LIB NAMES lfftw3 libfftw3 fftw3 REQUIRED)
target_link_libraries(libedsp ${FFTW_LIB})
target_include_directories(libedsp PUBLIC ./include/)
