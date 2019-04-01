project(edsp-c VERSION 0.0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HEADER
        include/cedsp/types.h
        include/cedsp/algorithm.h
        include/cedsp/windowing.h
        include/cedsp/statistics.h
        include/cedsp/spectral.h
        include/cedsp/converter.h
        include/cedsp/core.h)

set(SRC
        src/algorithm.c
        src/windowing.c
        src/statistics.c
        src/spectral.c
        src/converter.cpp
        src/core.c)

set_source_files_properties(${SRC} PROPERTIES LANGUAGE CXX)

set(CEDSP_LIBRARY cedsp)
add_library(${CEDSP_LIBRARY} SHARED ${HEADER} ${SRC})
target_include_directories(${CEDSP_LIBRARY} PUBLIC include/)
target_link_libraries(${CEDSP_LIBRARY} PUBLIC ${EDSP_LIBRARIES})
set(CEDSP_LIBRARIES "${EDSP_LIBRARIES};${CEDSP_LIBRARY}" PARENT_SCOPE)

get_target_property(OUT ${CEDSP_LIBRARY} LINK_LIBRARIES)
message(STATUS "${CEDSP_LIBRARY}-dependencies = ${OUT}")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${CEDSP_LIBRARY}-config-version.cmake"
        VERSION ${LIB_VERSION}
        COMPATIBILITY ExactVersion
)

install(TARGETS ${CEDSP_LIBRARY} EXPORT "${CEDSP_LIBRARY}-targets" DESTINATION lib)
#install(EXPORT "${CEDSP_LIBRARY}-targets" FILE "${CEDSP_LIBRARY}-config.cmake" DESTINATION "lib/cmake/${CEDSP_LIBRARY}")
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${CEDSP_LIBRARY}-config-version.cmake"
        DESTINATION "lib/cmake/${CEDSP_LIBRARY}")
install(DIRECTORY include/ DESTINATION include)
