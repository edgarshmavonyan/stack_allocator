cmake_minimum_required(VERSION 3.8)
project(stackallocator)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(lib/googletest-master/googletest/include)

add_subdirectory(lib/googletest-master)
add_subdirectory(test)
enable_testing()
#target_link_libraries(stackallocator gtest gtest_main)