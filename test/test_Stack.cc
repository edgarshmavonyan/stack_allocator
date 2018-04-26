#include "stackallocator/stackAllocator.h"
#include <gtest/gtest.h>
#include "test/testGeneration.h"
#include "test/testTime.h"


TEST(stackAllocator, testRandomSequence) {
    auto sequence = generateSequence(TEST_SIZE);
    std::cout << "Random test" << std::endl;
    std::cout << "User stack time: " << doRandomTesting<int, std::list, StackAllocator>(sequence) << std::endl;
    std::cout << "Built-in stack time: " << doRandomTesting<>(sequence) << std::endl;
}

TEST(stackAllocator, testFullInsert) {
    auto sequence = generateInsert(TEST_SIZE);
    std::cout << "Insert test" << std::endl;
    std::cout << "User stack time: " << doInsertTesting<int, std::list, StackAllocator>(sequence, false) << std::endl;
    std::cout << "Built-in stack time: " << doInsertTesting<>(sequence, false) << std::endl;
}

TEST(stackAllocator, testInsertPop) {
    auto sequence = generateInsert(TEST_SIZE);
    std::cout << "InsertPop test" << std::endl;
    std::cout << "User stack time: " << doInsertTesting<int, std::list, StackAllocator>(sequence, true) << std::endl;
    std::cout << "Built-in stack time: " << doInsertTesting<>(sequence, true) << std::endl;
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}