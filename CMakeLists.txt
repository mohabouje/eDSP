cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(EasyDSP VERSION 0.0.0 LANGUAGES CXX)


set(EASYDSP_DEPENDENCIES  EasyMeta)
find_library(FFTW_LIB NAMES lfftw3f libfftw3f fftw3f)
if (FFTW_LIB)
    list(APPEND ${EASYDSP_DEPENDENCIES} ${FFTW_LIB})
else()
    message(FATAL_ERROR "Library FFTW not found")
endif(FFTW_LIB)


find_library(SAMPLERATE_LIB NAMES lsamplerate libsamplerate samplerate)
if (SAMPLERATE_LIB)
    list(APPEND ${EASYDSP_DEPENDENCIES} ${SAMPLERATE_LIB})
else()
    message(FATAL_ERROR "Library LibSampleRate not found")
endif(SAMPLERATE_LIB)


add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include/")
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include/")
target_link_libraries(${PROJECT_NAME} INTERFACE ${EASYDSP_DEPENDENCIES})

enable_testing()
add_subdirectory(test)
#add_subdirectory(python)
