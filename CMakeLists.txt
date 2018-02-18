cmake_minimum_required(VERSION 3.8)
project(eDSP)
set(CMAKE_CXX_STANDARD 17)

enable_testing ()
add_subdirectory (libedsp)
add_subdirectory (benchmark)
add_subdirectory (test)