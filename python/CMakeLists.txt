project(pedsp VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HEADER
        include/algorithm.hpp
        include/windowing.hpp)

set(SRC
        src/package.cpp
        src/algorithm.cpp
        src/windowing.cpp)

find_package(Boost COMPONENTS python REQUIRED)
find_package(PythonInterp)
find_package(PythonLibs REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${HEADER} ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
target_compile_definitions(${PROJECT_NAME} PRIVATE MODULE_NAME=${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC edsp edsp-c ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} -lfftw3 -lboost_numpy)