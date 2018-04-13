cmake_minimum_required(VERSION 3.8)
project(stackallocator_test)

set(CMAKE_CXX_STANDARD 14)

#include_directories(${CMAKE_SOURCE_DIR}/include)

#add_executable(test_Stack test_Stack.cpp)
#target_link_libraries(test_Stack gtest gtest_main)

add_executable(test_Xorlist test_Xorlist.cc)
target_link_libraries(test_Xorlist gtest gtest_main)
add_test(NAME Test_XorList COMMAND test_Xorlist)