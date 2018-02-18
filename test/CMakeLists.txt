set(TEST_FILES
        test_util.h
        test_config.h
        test_db.h
        main.cpp
        math/stats_test.cpp
        utilitity/vectorutil_test.cpp
        transforms/fft_test.cpp
)


include_directories("${CMAKE_SOURCE_DIR}/third_party/Catch/include/")

add_executable(runtest ${TEST_FILES})
target_link_libraries(runtest libedsp)
add_test (NAME UnitTest COMMAND runtest)