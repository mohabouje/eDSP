cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(EasyDSP VERSION 0.0.0 LANGUAGES CXX)

set(LIB_NAME ${PROJECT_NAME})
set(${LIB_NAME}_VERSION_MAJOR       "0")
set(${LIB_NAME}_VERSION_MINOR       "0")
set(${LIB_NAME}_VERSION_PATCH       "0")

option(BUILD_TESTS "Enable to build tests" ON)
option(BUILD_DOCS "Enable to build docs" OFF)
option(BUIL_EXAMPLES "Enable to build examples" OFF)
option(BUILD_TOOLS "Enable to build tools" OFF)
option(ENABLE_OPTIMIZATIONS "Enable all the optimizations, in release mode" ON)
option(ENABLE_WARNINGS "Enable all warning during compilation" ON)
option(ENABLE_DEBUG_INFORMATION "Enable debug information, useful for profiling and debugging tools" OFF)

# Add the C++ Standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14")

# Add some useful definitions
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Add all the warnings, if it is enabled
if (ENABLE_WARNINGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-show-option -pedantic -Wall -Wextra -Wunreachable-code")
endif (ENABLE_WARNINGS)

# Add optimization, if enabled and release mode
if (ENABLE_OPTIMIZATIONS)
    set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -march=native -o3 -ofast -frename-registers -funroll-loops")
endif(ENABLE_OPTIMIZATIONS)

# Add the debug information, if it is enabled
if (ENABLE_DEBUG_INFORMATION)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
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


set(EASYDSP_DEPENDENCIES)
find_library(FFTW_LIB NAMES lfftw3f libfftw3f fftw3f)
if (FFTW_LIB)
    list(APPEND ${EASYDSP_DEPENDENCIES} ${FFTW_LIB})
else()
    message(FATAL_ERROR "Library FFTW not found")
endif(FFTW_LIB)


add_library(${LIB_NAME} INTERFACE)
target_sources(${LIB_NAME} INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_include_directories(${LIB_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include/")
target_link_libraries(${LIB_NAME} INTERFACE ${EASYDSP_DEPENDENCIES})

include(GNUInstallDirs)
install(TARGETS ${LIB_NAME}
        EXPORT "${LIB_NAME}-export"
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
    add_subdirectory(python)
endif (BUILD_TESTS)

