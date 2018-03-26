cmake_minimum_required(VERSION 3.8)
project(stackallocator)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES test.cpp stack.h)
add_executable(stackallocator ${SOURCE_FILES})
target_link_libraries(stackallocator gtest gtest_main)