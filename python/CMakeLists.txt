project(edsp-python VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PythonInterp)
if (PYTHONINTERP_FOUND)
    if (NOT APPLE)
        if (PYTHON_VERSION_MAJOR EQUAL 3)
            find_package(Boost COMPONENTS python${PYTHON_VERSION_SUFFIX} numpy${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
            find_package(PythonInterp 3)
            find_package(PythonLibs 3 REQUIRED)
        else()
            find_package(Boost COMPONENTS python numpy)
            find_package(PythonInterp)
            find_package(PythonLibs REQUIRED)
        endif()
    else()
        if (PYTHON_VERSION_MAJOR EQUAL 3)
            find_package(Boost COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} numpy${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
            find_package(PythonInterp 3)
            find_package(PythonLibs 3 REQUIRED)
        else()
            find_package(Boost COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} numpy${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
            find_package(PythonInterp)
            find_package(PythonLibs REQUIRED)
        endif()
    endif()
else()
    message(FATAL "Python not found")
endif()


include_directories(${Boost_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})

set(HEADER
        include/algorithm_python.hpp
        include/windowing_python.hpp
        include/statistics_python.hpp)

set(SRC
        src/package.cpp
        src/algorithm.cpp
        src/windowing.cpp
        src/statistics.cpp)

set(PEDSP_LIBRARY pedsp)
add_library(${PEDSP_LIBRARY} SHARED ${HEADER} ${SRC})
target_compile_definitions(${PEDSP_LIBRARY} PRIVATE "MODULE_NAME=${PEDSP_LIBRARY}")
target_include_directories(${PEDSP_LIBRARY} PUBLIC include)
target_link_libraries(${PEDSP_LIBRARY} PUBLIC ${CEDSP_LIBRARIES} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

set_target_properties(${PEDSP_LIBRARY} PROPERTIES PREFIX "")
if (APPLE)
    set_target_properties(${PEDSP_LIBRARY} PROPERTIES SUFFIX ".so")  # must be .so (not .dylib)
endif(APPLE)

get_target_property(OUT ${PEDSP_LIBRARY} LINK_LIBRARIES)
message(STATUS "${PEDSP_LIBRARY}-dependencies = ${OUT}")

install(TARGETS ${PEDSP_LIBRARY}
        LIBRARY DESTINATION "${PYTHON_SITE_PACKAGES}" COMPONENT "${PEDSP_LIBRARY}-python"
        ARCHIVE DESTINATION "${PYTHON_SITE_PACKAGES}" COMPONENT "${PEDSP_LIBRARY}-python")
