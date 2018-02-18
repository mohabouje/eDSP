set(BENCHMARK_FILES
        main.cpp
        benchmark_transforms.cpp
        benchmark_window.cpp
        benchmark_vectorutil.cpp
        )

include_directories("${CMAKE_SOURCE_DIR}/third_party/benchmark/include/")
find_library(BENCHMARK_LIB NAMES lbenchmark libbenchmark benchmark REQUIRED)

add_executable(runbenchmark  ${BENCHMARK_FILES})
target_link_libraries(runbenchmark ${BENCHMARK_LIB} libedsp)
target_link_libraries(runbenchmark )

if (UNIX)
    target_link_libraries(runbenchmark -lpthread)
endif (UNIX)