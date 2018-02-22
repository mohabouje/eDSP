
set(HEADER_FILES config.h version.h)
set(SOURCE_FILES )


add_subdirectory(windowing)
add_subdirectory(oscillators)
add_subdirectory(blocks)
add_subdirectory(filters)
add_subdirectory(utility)
add_subdirectory(features)
add_subdirectory(base)
add_subdirectory(frequency)
add_subdirectory(math)


add_library(libedsp ${HEADER_FILES} ${SOURCE_FILES})


include_directories(.)


find_library(FFTW_LIB NAMES lfftw3 libfftw3 fftw3 REQUIRED)
target_link_libraries(libedsp ${FFTW_LIB})
target_include_directories(libedsp PUBLIC ./include/)
