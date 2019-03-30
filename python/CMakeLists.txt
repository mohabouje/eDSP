project(edsp-python VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(USE_PYTHON3 "Forces the usage of Python3" ON)

if (USE_PYTHON3)
    find_package(PythonLibs 3 REQUIRED)
    find_package(PythonInterp 3 REQUIRED)
    execute_process ( COMMAND python3 -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES_GUESS OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(PYTHON_SITE_PACKAGES ${PYTHON_SITE_PACKAGES_GUESS} CACHE PATH "Where to install the python bindings")
    message(STATUS "python site-packages: ${PYTHON_SITE_PACKAGES}")
else()
    find_package(PythonLibs REQUIRED)
    find_package(PythonInterp REQUIRED)
    execute_process ( COMMAND python -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES_GUESS OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(PYTHON_SITE_PACKAGES ${PYTHON_SITE_PACKAGES_GUESS} CACHE PATH "Where to install the python bindings")
    message(STATUS "python site-packages: ${PYTHON_SITE_PACKAGES}")
endif(USE_PYTHON3)

if (PYTHONINTERP_FOUND)
    if (NOT APPLE)
        if (PYTHON_VERSION_MAJOR EQUAL 3)
            find_package(Boost COMPONENTS python${PYTHON_VERSION_SUFFIX} numpy${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} REQUIRED)
            find_package(PythonInterp 3)
            find_package(PythonLibs 3 REQUIRED)
        else()
            find_package(Boost COMPONENTS python numpy REQUIRED)
            find_package(PythonInterp)
            find_package(PythonLibs REQUIRED)
        endif()
    else()
        if (PYTHON_VERSION_MAJOR EQUAL 3)
            find_package(Boost COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} numpy${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} REQUIRED)
            find_package(PythonInterp 3)
            find_package(PythonLibs 3 REQUIRED)
        else()
            find_package(Boost COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} numpy${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} REQUIRED)
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
        include/algorithm.hpp
        include/windowing.hpp
        include/statistics.hpp include/spectral.hpp)

set(SRC
        src/package.cpp
        src/algorithm.cpp
        src/windowing.cpp
        src/statistics.cpp src/spectral.cpp)

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
