#include "stackallocator/stackAllocator.h"
#include <gtest/gtest.h>
#include "xorlist/xorlist.h"
#include "test/testGeneration.h"
#include "test/testTime.h"


TEST(StackAllocator, threeTestsStd) {
    std::cout << "Comparison on std::list" << std::endl;
    threeTestsForTime<int, std::list>(TEST_SIZE);
}

TEST(StackAllocator, threeTestsXorList) {
    std::cout << "Comparison on XorList" << std::endl;
    threeTestsForTime<int, XorList>(TEST_SIZE);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}