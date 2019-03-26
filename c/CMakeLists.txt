project(edsp-c VERSION 0.0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HEADER
        include/types.h
        include/algorithm.h
        include/windowing.h
        include/statistics.h
        include/spectral.h)

set(SRC
        src/algorithm.c
        src/windowing.c
        src/statistics.c
        src/spectral.c)

SET_SOURCE_FILES_PROPERTIES(${SRC} PROPERTIES LANGUAGE CXX)

add_library(${PROJECT_NAME} SHARED ${HEADER} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})


add_executable("${PROJECT_NAME}-example" example/main.c)
target_link_libraries("${PROJECT_NAME}-example" PRIVATE ${PROJECT_NAME} -lfftw3)