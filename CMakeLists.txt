cmake_minimum_required(VERSION 3.8)
project(stackallocator)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

include_directories(include)
include_directories(lib/googletest-master/googletest/include)

add_subdirectory(lib/googletest-master)
add_subdirectory(test)