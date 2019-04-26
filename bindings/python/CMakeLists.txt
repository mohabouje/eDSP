project(edsp-python VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (USE_PYTHON3)
    message(STATUS "compiling bindings for python 3...")
    find_package(PythonLibs 3 REQUIRED)
    find_package(PythonInterp 3 REQUIRED)
    execute_process ( COMMAND python3 -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES_GUESS OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(PYTHON_SITE_PACKAGES ${PYTHON_SITE_PACKAGES_GUESS} CACHE PATH "path where to install the python bindings")
    message(STATUS "python site-packages: ${PYTHON_SITE_PACKAGES}")
else()
    message(STATUS "compiling bindings for python 2...")
    find_package(PythonLibs 2.7 REQUIRED)
    find_package(PythonInterp 2.7 REQUIRED)
    execute_process ( COMMAND python -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES_GUESS OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(PYTHON_SITE_PACKAGES ${PYTHON_SITE_PACKAGES_GUESS} CACHE PATH "path where to install the python bindings")
    message(STATUS "python site-packages: ${PYTHON_SITE_PACKAGES}")
endif(USE_PYTHON3)

if (PYTHONINTERP_FOUND)
    if (NOT APPLE)
        if (USE_PYTHON3)
            find_package(Boost COMPONENTS python${PYTHON_VERSION_SUFFIX} REQUIRED)
            if (NOT USE_BOOST_NUMPY_DEPRECATED)
                find_package(Boost COMPONENTS numpy${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} REQUIRED)
            endif(NOT USE_BOOST_NUMPY_DEPRECATED)
        else()
            find_package(Boost COMPONENTS python REQUIRED)
            if (NOT USE_BOOST_NUMPY_DEPRECATED)
                find_package(Boost COMPONENTS numpy REQUIRED)
            endif(NOT USE_BOOST_NUMPY_DEPRECATED)
        endif()
    else()
        if (USE_PYTHON3)
            find_package(Boost COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} REQUIRED)
            if (NOT USE_BOOST_NUMPY_DEPRECATED)
                find_package(Boost COMPONENTS numpy${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}  REQUIRED)
            endif(NOT USE_BOOST_NUMPY_DEPRECATED)
        else()
            find_package(Boost COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} REQUIRED)
            if (NOT USE_BOOST_NUMPY_DEPRECATED)
                find_package(Boost COMPONENTS numpy${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}  REQUIRED)
            endif(NOT USE_BOOST_NUMPY_DEPRECATED)
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
        include/statistics.hpp
        include/spectral.hpp
        include/boost_numpy_dependencies.hpp
        include/converter.hpp 
        include/core.hpp
        include/string.hpp 
        include/oscillator.hpp
        include/auditory.hpp
        include/feature.hpp
        include/filter.hpp
        include/io.hpp)

set(SRC
        src/package.cpp
        src/algorithm.cpp
        src/windowing.cpp
        src/statistics.cpp
        src/spectral.cpp
        src/converter.cpp
        src/core.cpp
        src/string.cpp
        src/oscillator.cpp
        src/auditory.cpp
        src/feature_temporal.cpp
        src/feature_spectral.cpp
        src/feature_statistics.cpp
        src/filter.cpp
        src/io.cpp)

set(PEDSP_LIBRARY pedsp)
add_library(${PEDSP_LIBRARY} SHARED ${HEADER} ${SRC})
target_compile_definitions(${PEDSP_LIBRARY} PRIVATE "MODULE_NAME=${PEDSP_LIBRARY}")
target_include_directories(${PEDSP_LIBRARY} PUBLIC include)
target_link_libraries(${PEDSP_LIBRARY} PRIVATE ${CEDSP_LIBRARIES} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
target_link_libraries(${PEDSP_LIBRARY} PRIVATE ${EDSP_LIBRARIES})
set_target_properties(${PEDSP_LIBRARY} PROPERTIES PREFIX "")
if (APPLE)
    set_target_properties(${PEDSP_LIBRARY} PROPERTIES SUFFIX ".so")  # must be .so (not .dylib)
endif(APPLE)

if (USE_BOOST_NUMPY_DEPRECATED)
    target_link_libraries(${PEDSP_LIBRARY} PUBLIC -lboost_numpy)
endif(USE_BOOST_NUMPY_DEPRECATED)

get_target_property(OUT ${PEDSP_LIBRARY} LINK_LIBRARIES)
message(STATUS "${PEDSP_LIBRARY}-dependencies = ${OUT}")

install(TARGETS ${PEDSP_LIBRARY}
        LIBRARY DESTINATION "${PYTHON_SITE_PACKAGES}" COMPONENT "${PEDSP_LIBRARY}-python"
        ARCHIVE DESTINATION "${PYTHON_SITE_PACKAGES}" COMPONENT "${PEDSP_LIBRARY}-python")
