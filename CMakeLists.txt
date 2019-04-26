cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(edsp VERSION 0.0.1 LANGUAGES CXX)


option(ENABLE_COVERAGE "Enable the code coverage" OFF)
option(ENABLE_OPTIMIZATIONS "Enable all the optimizations, in release mode" ON)
option(ENABLE_WARNINGS "Enable all warning during compilation" ON)
option(ENABLE_DEBUG_INFORMATION "Enable debug information, useful for profiling and debugging tools" OFF)

option(BUILD_C_BINDINGS "Enable the compilation of the bindings for C" ON)
option(BUILD_PYTHON_BINDINGS "Enable the compilation of the bindings for Python" ON)
option(BUILD_DOCS "Enable to build docs" OFF)
option(BUILD_EXAMPLES "Enable the option to build the examples" ON)
option(BUILD_BENCHMARK "Enable the option to build the benchmarks" OFF)

option(USE_PYTHON3 "Forces the usage of Python3" OFF)
option(USE_BOOST_NUMPY_DEPRECATED "Uses the original boost-numpy package" OFF)
option(USE_LIBSNDFILE "Use the library SndFile to encodedecode audio files" ON)
option(USE_LIBAUDIOFILE "Use the library AudioFile to encode/decode audio files" OFF)
option(USE_LIBPFFFT "Use the library PFFT to encode/decode audio files" OFF)
option(USE_LIBFFTW "Use the library FFTW to encode/decode audio files" ON)
option(USE_LIBSAMPLERATE "Use the library libsamplerate to resample audio data" ON)
option(USE_LIBRESAMPLE "Use the library libresample to resample audio data" OFF)
option(USE_TAGLIB "Use the library taglib to read audio metadata" ON)

# TODO add an option to check if single or double precision


# Add some useful definitions
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Add all the warnings, if it is enabled
if (ENABLE_WARNINGS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-show-option -pedantic -Wall -Wextra -Wunreachable-code")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-show-option -pedantic -Wall -Wextra -Wunreachable-code -Wno-register")
endif (ENABLE_WARNINGS)

# Add optimization, if enabled and release mode
if (ENABLE_OPTIMIZATIONS)
    set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_RELEASE} -march=native -o3 -ofast -frename-registers -funroll-loops")
    set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -march=native -o3 -ofast -frename-registers -funroll-loops")
endif(ENABLE_OPTIMIZATIONS)

# Add the debug information, if it is enabled
if (ENABLE_DEBUG_INFORMATION)
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif (ENABLE_DEBUG_INFORMATION)

if (ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -fprofile-arcs -coverage")
endif(ENABLE_COVERAGE)

# Set the default build type
if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  endif()
endif()

# Make a .so output!
if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "-I/usr/local/include")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif(APPLE)

# Starting the library configuration
set(VERSION_MAJOR  0)
set(VERSION_MINOR  0)
set(VERSION_PATCH  1)

set(EDSP_LIBRARY edsp)
set(LIB_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

# Starting the dependencies list
set(EDSP_DEPENDENCIES)
if (USE_LIBFFTW)
    set(USE_LIBPFFFT OFF)
    find_library(FFTW_LIB NAMES lfftw3 libfftw3 fftw3)
    if (FFTW_LIB)
        add_definitions(-DUSE_LIBFFTW)
        set(EDSP_DEPENDENCIES "${EDSP_DEPENDENCIES};${FFTW_LIB}")
    else()
        message(FATAL_ERROR "Library FFTW not found")
    endif(FFTW_LIB)
endif()

if (USE_LIBPFFFT)
    find_library(PFFFT_LIB NAMES lpffft libpffft pffft)
    if (PFFFT_LIB)
        add_definitions(-DUSE_LIBPFFFT)
        set(EDSP_DEPENDENCIES "${EDSP_DEPENDENCIES};${PFFFT_LIB}")
    else()
        message(FATAL_ERROR "Library PFFFT not found")
    endif(PFFFT_LIB)
endif()

if (USE_LIBSNDFILE)
    set(USE_LIBAUDIOFILE OFF)
    find_library(SNDFILE_LIB NAMES lsndfile libsndfile sndfile)
    if (SNDFILE_LIB)
        set(EDSP_DEPENDENCIES "${EDSP_DEPENDENCIES};${SNDFILE_LIB}")
        add_definitions(-DUSE_LIBSNDFILE)
    else()
        message(FATAL_ERROR "Library SndFile not found")
    endif(SNDFILE_LIB)
endif()

if (USE_LIBAUDIOFILE)
    find_library(AUDIOFILE_LIB NAMES laudiofile libaudiofile audiofile)
    if (AUDIOFILE_LIB)
        set(EDSP_DEPENDENCIES "${EDSP_DEPENDENCIES};${AUDIOFILE_LIB}")
        add_definitions(-DUSE_LIBAUDIOFILE)
    else()
        message(FATAL_ERROR "Library AudioFile not found")
    endif(AUDIOFILE_LIB)
endif()

if (USE_LIBSAMPLERATE)
    set(USE_LIBRESAMPLE OFF)
    find_library(LIBSAMPLERATE_LIB NAMES lsamplerate libsamplerate samplerate)
    if (LIBSAMPLERATE_LIB)
        set(EDSP_DEPENDENCIES "${EDSP_DEPENDENCIES};${LIBSAMPLERATE_LIB}")
        add_definitions(-DUSE_LIBSAMPLERATE)
    else()
        message(FATAL_ERROR "Library samplerate not found")
    endif(LIBSAMPLERATE_LIB)
endif(USE_LIBSAMPLERATE)

if (USE_LIBRESAMPLE)
    find_library(LIBRESAMPLE_LIB NAMES lresample libresample resample)
    if (LIBRESAMPLE_LIB)
        set(EDSP_DEPENDENCIES "${EDSP_DEPENDENCIES};${LIBRESAMPLE_LIB}")
        add_definitions(-DUSE_LIBRESAMPLE)
    else()
        message(FATAL_ERROR "Library resample not found")
    endif(LIBRESAMPLE_LIB)
endif(USE_LIBRESAMPLE)

if (USE_TAGLIB)
    find_library(TAGLIB_LIB NAMES ltag libtag tag)
    if (TAGLIB_LIB)
        set(EDSP_DEPENDENCIES "${EDSP_DEPENDENCIES};${TAGLIB_LIB}")
        add_definitions(-DUSE_TAGLIB)
    else()
        message(FATAL_ERROR "Library taglib not found")
    endif(TAGLIB_LIB)
endif(USE_TAGLIB)


add_library(${EDSP_LIBRARY} INTERFACE)
target_sources(${EDSP_LIBRARY} INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_include_directories(${EDSP_LIBRARY} INTERFACE)
target_link_libraries(${EDSP_LIBRARY} INTERFACE ${EDSP_DEPENDENCIES})
target_include_directories(${EDSP_LIBRARY} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)
target_include_directories(${EDSP_LIBRARY} SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

set(EDSP_LIBRARIES "${EDSP_LIBRARY};${EDSP_DEPENDENCIES}")
set(EDSP_INCLUDEDIRS "${CMAKE_CURRENT_SOURCE_DIR}/include/")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${EDSP_LIBRARY}-config-version.cmake"
        VERSION ${LIB_VERSION}
        COMPATIBILITY ExactVersion
)

# TODO: restore when everything is ready to release
# install(TARGETS ${EDSP_LIBRARY} EXPORT "${EDSP_LIBRARY}-targets" DESTINATION lib)
# install(EXPORT "${EDSP_LIBRARY}-targets" FILE "${EDSP_LIBRARY}-config.cmake" DESTINATION "lib/cmake/${EDSP_LIBRARY}")
# install(FILES
#         "${CMAKE_CURRENT_BINARY_DIR}/${EDSP_LIBRARY}-config-version.cmake"
#         DESTINATION "lib/cmake/${EDSP_LIBRARY}")
# install(DIRECTORY include/ DESTINATION include)

if (BUILD_DOCS)
    find_package(Doxygen REQUIRED dot mscgen dia)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif (BUILD_DOCS)

if (BUILD_C_BINDINGS)
    add_subdirectory(bindings/c)
endif(BUILD_C_BINDINGS)

if (BUILD_PYTHON_BINDINGS)
    if (USE_BOOST_NUMPY_DEPRECATED)
        add_definitions(-DUSE_BOOST_NUMPY_DEPRECATED)
    endif()
    add_subdirectory(bindings/python)
endif(BUILD_PYTHON_BINDINGS)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)

if (BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif(BUILD_BENCHMARK)
