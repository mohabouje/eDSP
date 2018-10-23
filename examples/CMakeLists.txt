cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(EasyDSP-Examples VERSION 0.0.0 LANGUAGES CXX)


option(COMPILE_QTAPPS "Enable the compilation of the different apps with Qt dependencies" ON)

add_executable(edsp-library-info library_info.cpp)
target_link_libraries(edsp-library-info pthread edsp)


set(Python_ADDITIONAL_VERSIONS 2.7)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})


add_executable(edsp-filter-designer filter_designer.cpp)
target_link_libraries(edsp-filter-designer pthread edsp ${PYTHON_LIBRARIES})

