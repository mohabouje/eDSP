set(BENCHMARK_FILES
        main.cpp
        benchmark_transforms.cpp benchmark_window.cpp benchmark_vectorutil.cpp ../include/base/transform.h)
add_executable(runbenchmark  ${BENCHMARK_FILES})
include_directories("${CMAKE_SOURCE_DIR}/third_party/benchmark/include/")
target_link_libraries(runbenchmark ${FFTW_LIB})
target_link_libraries(runbenchmark ${BENCHMARK_LIB})
