cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(QFIRDesigner VERSION 0.0.1 LANGUAGES CXX)

find_package(Qt5 COMPONENTS Widgets Qml Quick Charts REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11 -fstrict-aliasing -pedantic-errors -pedantic -Wno-deprecated-declarations -Wno-unused-variable")


set(HEADERS)
set(SOURCES
    src/main.cpp
    src/Main.qml
    src/TextDial.qml
    src/NavigationDrawer.qml
    src/FrequencyTunning.qml)
qt5_add_resources(QT_RESOURCES
    resources/icons.qrc
    src/qml.qrc)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${QT_RESOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
        eDSP
        Qt5::Widgets
        Qt5::Qml
        Qt5::Quick
        Qt5::Charts)
