cmake_minimum_required(VERSION 3.8)
project(stackallocator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp stack.h)
add_executable(stackallocator ${SOURCE_FILES})