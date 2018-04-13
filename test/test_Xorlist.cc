#include <gtest/gtest.h>
#include "xorlist/xorlist.h"
#include "test/testGeneration.h"
#include "test/testTime.h"




TEST(XorList, randomSeq_std) {
    auto sequence = generateSequence(TEST_SIZE);
    double stdListTime = doRandomTesting<int, std::list, std::allocator>(sequence);
    double xorListTime = doRandomTesting<int, XorList, std::allocator>(sequence);
    std::cout << "random sequence" << std::endl;
    std::cout << "XorList compare with std::list on std::allocator (int)" << std::endl;
    std::cout << "std::list time: " << stdListTime << std::endl;
    std::cout << "XorList time: " << xorListTime << std::endl;
}

TEST(XorList, randomPushBack_std) {
    auto sequence = generateInsert(TEST_SIZE);
    double stdListTime = doInsertTesting<int, std::list, std::allocator>(sequence);
    double xorListTime = doInsertTesting<int, XorList, std::allocator>(sequence);
    std::cout << "random insert" << std::endl;
    std::cout << "XorList compare with std::list on std::allocator (int)" << std::endl;
    std::cout << "std::list time: " << stdListTime << std::endl;
    std::cout << "XorList time: " << xorListTime << std::endl;
}



int main(int argv, char* argc[]) {
    testing::InitGoogleTest(&argv, argc);
    return RUN_ALL_TESTS();
}