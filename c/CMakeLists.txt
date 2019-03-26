project(edsp-c VERSION 0.0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HEADER
        include/types.h
        include/algorithm.h
        include/windowing.h)

set(SRC
        src/algorithm.c
        src/windowing.c)

SET_SOURCE_FILES_PROPERTIES(${SRC} PROPERTIES LANGUAGE CXX)

add_library(${PROJECT_NAME} SHARED ${HEADER} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})
