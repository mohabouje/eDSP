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

set_source_files_properties(${SRC} PROPERTIES LANGUAGE CXX)

set(CEDSP_LIBRARY cedsp)
add_library(${CEDSP_LIBRARY} SHARED ${HEADER} ${SRC})
target_include_directories(${CEDSP_LIBRARY} PUBLIC include/)
target_link_libraries(${CEDSP_LIBRARY} PRIVATE ${EDSP_LIBRARIES})
set(CEDSP_LIBRARIES "${EDSP_LIBRARIES};${CEDSP_LIBRARY}" PARENT_SCOPE)

get_target_property(OUT ${CEDSP_LIBRARY} LINK_LIBRARIES)
message(STATUS "${CEDSP_LIBRARY}-dependencies = ${OUT}")


install(TARGETS ${CEDSP_LIBRARY} EXPORT "${CEDSP_LIBRARY}-targets" DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/cedsp)