cmake_minimum_required(VERSION 3.8)
project(stackAllocator_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_Stack test_Stack.cc)
target_link_libraries(test_Stack gtest gtest_main stackAllocator_src)
add_test(NAME Test_Stack COMMAND test_Stack)

add_executable(test_Xorlist test_Xorlist.cc)
target_link_libraries(test_Xorlist gtest gtest_main)
add_test(NAME Test_XorList COMMAND test_Xorlist)