cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(edsp VERSION 0.0.1 LANGUAGES CXX)

option(BUILD_TESTS "Enable to build tests" ON)
option(BUILD_DOCS "Enable to build docs" OFF)
option(BUILD_EXAMPLES "Enable to build examples" ON)
option(BUILD_TOOLS "Enable to build tools" ON)
option(BUILD_BENCHMARKS "Enable to build benchmarks" ON)
option(BUILD_EXTENSIONS "Enable the option to build the extension libraries" ON)
option(ENABLE_COVERAGE "Enable the code coverage" OFF)
option(ENABLE_OPTIMIZATIONS "Enable all the optimizations, in release mode" ON)
option(ENABLE_WARNINGS "Enable all warning during compilation" ON)
option(ENABLE_DEBUG_INFORMATION "Enable debug information, useful for profiling and debugging tools" OFF)
option(USE_MATPLOTLIB "Use the python Matplotlib for charts support" ON)
option(USE_LIBSNDFILE "Use the library SndFile to encodedecode audio files" ON)
option(USE_LIBAUDIOFILE "Use the library AudioFile to encode/decode audio files" OFF)
option(USE_LIBPFFFT "Use the library PFFT to encode/decode audio files" OFF)
option(USE_LIBFFTW "Use the library FFTW to encode/decode audio files" ON)
option(USE_LIBSAMPLERATE "Use the library libsamplerate to resample audio data" ON)
option(USE_LIBRESAMPLE "Use the library libresample to resample audio data" ON)


# Add some useful definitions
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Add all the warnings, if it is enabled
if (ENABLE_WARNINGS)
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-show-option -pedantic -Wall -Wextra -Wunreachable-code")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-show-option -pedantic -Wall -Wextra -Wunreachable-code")
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


# Set the default build type
if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  endif()
endif()

# Set the default install folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

if (USE_LIBFFTW)
    set(EDSP_DEPENDENCIES)
    find_library(FFTW_LIB NAMES lfftw3f libfftw3f fftw3f)
    if (FFTW_LIB)
        add_definitions(-DUSE_LIBFFTW)
        list(APPEND ${EDSP_DEPENDENCIES} ${FFTW_LIB})
    else()
        message(FATAL_ERROR "Library FFTW not found")
    endif(FFTW_LIB)
endif()

if (USE_LIBPFFFT)
    set(EDSP_DEPENDENCIES)
    find_library(PFFFT_LIB NAMES lpffft libpffft pffft)
    if (PFFFT_LIB)
        add_definitions(-DUSE_LIBPFFFT)
        list(APPEND ${EDSP_DEPENDENCIES} ${PFFFT_LIB})
    else()
        message(FATAL_ERROR "Library PFFFT not found")
    endif(PFFFT_LIB)
endif()

if (USE_LIBAUDIOFILE)
    find_library(AUDIOFILE_LIB NAMES laudiofile libaudiofile audiofile)
    if (AUDIOFILE_LIB)
        list(APPEND ${EDSP_DEPENDENCIES} ${AUDIOFILE_LIB})
        add_definitions(-DUSE_LIBAUDIOFILE)
    else()
        message(FATAL_ERROR "Library AudioFile not found")
    endif(AUDIOFILE_LIB)
endif()

if (USE_LIBSNDFILE)
    find_library(SNDFILE_LIB NAMES lsndfile libsndfile sndfile)
    if (SNDFILE_LIB)
        list(APPEND ${EDSP_DEPENDENCIES} ${SNDFILE_LIB})
        add_definitions(-DUSE_LIBSNDFILE)
    else()
        message(FATAL_ERROR "Library SndFile not found")
    endif(SNDFILE_LIB)
endif()

if (USE_MATPLOTLIB)
    set(Python_ADDITIONAL_VERSIONS 2.7)
    find_package(PythonLibs REQUIRED)
    include_directories(${PYTHON_INCLUDE_DIRS})
    list(APPEND ${EDSP_DEPENDENCIES} ${PYTHON_LIBRARIES})
    add_definitions(-DUSE_MATPLOTLIB)
endif(USE_MATPLOTLIB)


if (USE_LIBSAMPLERATE)
    add_definitions(-DUSE_LIBSAMPLERATE)
endif(USE_LIBSAMPLERATE)

if (USE_LIBRESAMPLE)
    add_definitions(-DUSE_LIBRESAMPLE)
endif(USE_LIBRESAMPLE)


set(VERSION_MAJOR  0)
set(VERSION_MINOR  0)
set(VERSION_PATCH  1)

set(LIB_NAME ${PROJECT_NAME})
set(LIB_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

add_library(${LIB_NAME} INTERFACE)
target_sources(${LIB_NAME} INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_include_directories(${LIB_NAME} INTERFACE)
target_link_libraries(${LIB_NAME} INTERFACE ${EDSP_DEPENDENCIES})
target_include_directories(${LIB_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)
target_include_directories(${LIB_NAME} SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-config-version.cmake"
        VERSION ${LIB_VERSION}
        COMPATIBILITY ExactVersion
)

install(TARGETS ${LIB_NAME} EXPORT "${LIB_NAME}-targets" DESTINATION lib)
install(EXPORT "${LIB_NAME}-targets" FILE "${LIB_NAME}-config.cmake" DESTINATION "lib/cmake/${LIB_NAME}")
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-config-version.cmake"
        DESTINATION "lib/cmake/${LIB_NAME}")
install(DIRECTORY include/ DESTINATION include)


if (ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -fprofile-arcs -coverage")
endif(ENABLE_COVERAGE)


if (BUILD_EXTENSIONS)
    add_subdirectory(extension)
    target_link_libraries (${LIB_NAME} INTERFACE ${EDSP_EXTENSION_LIBRARIES})
    target_include_directories (${LIB_NAME} INTERFACE ${EDSP_EXTENSION_INCLUDE_DIRS})
endif(BUILD_EXTENSIONS)

if (BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif(BUILD_BENCHMARKS)


if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif (BUILD_TESTS)


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
