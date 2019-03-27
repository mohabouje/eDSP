cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(extension VERSION 0.0.1 LANGUAGES C CXX)

set(EDSP_LIBRARY ${PROJECT_NAME})
set(VERSION_MAJOR       "0")
set(VERSION_MINOR       "0")
set(VERSION_PATCH       "1")

add_library(pffft SHARED pffft/pffft.h pffft/pffft.c)
set_target_properties(pffft PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(pffft PROPERTIES PUBLIC_HEADER pffft/pffft.h)
target_include_directories(pffft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pffft/)
include(GNUInstallDirs)
install(TARGETS pffft
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
