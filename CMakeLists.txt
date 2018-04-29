cmake_minimum_required(VERSION 3.8)
project(stackAllocator)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

enable_testing()

include_directories(include)
include_directories(lib/googletest-master/googletest/include)

add_subdirectory(lib/googletest-master)
add_subdirectory(src)
add_subdirectory(test)