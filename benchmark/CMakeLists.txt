set(BENCHMARK_FILES
        main.cpp
        benchmark_transforms.cpp
        benchmark_window.cpp
        benchmark_vectorutil.cpp
        ../include/base/analog_filter.h ../include/base/types.h ../include/filters/fir.h ../include/algorithm/delay.h ../include/algorithm/echo.h.h ../include/algorithm/envelope_detector.h ../include/algorithm/peak_picker.h ../include/utility/converter.h ../include/algorithm/gain.h ../include/algorithm/multichannel_to_mono_converter.h)
add_executable(runbenchmark  ${BENCHMARK_FILES})
include_directories("${CMAKE_SOURCE_DIR}/third_party/benchmark/include/")
target_link_libraries(runbenchmark ${FFTW_LIB})
target_link_libraries(runbenchmark ${BENCHMARK_LIB})

if (UNIX)
    target_link_libraries(runbenchmark -lpthread)
endif (UNIX)