//#include "test.h"
#include "stackallocator/stackChain.h"
#include <gtest/gtest.h>
#include "test/testGeneration.h"

template<class alloc = std::allocator<int> >
double doRandomTesting(const std::vector<std::pair<int, int> >& sequence) {
    std::list<int, alloc> tested;
    clock_t t = clock();
    for (auto& element: sequence) {
        if (element.first == -1) {
            tested.pop_back();
        } else
            tested.emplace_back(element.second);
    }
    t = clock() - t;
    return double(t)/CLOCKS_PER_SEC;
}


template<class alloc = std::allocator<int> >
double doInsertTesting(const std::vector<int>& sequence, bool toErase) {
    std::list<int, alloc> tested;
    clock_t t = clock();
    for (auto& element: sequence) {
        tested.emplace_back(element);
    }
    if (toErase) {
        while (!tested.empty())
            tested.pop_back();
    }
    t = clock() - t;
    return double(t)/CLOCKS_PER_SEC;
}

TEST(testRandomSequence, DISABLED_stackTest) {
    auto sequence = generateSequence(TEST_SIZE);
    std::cout << "Random test" << std::endl;
    std::cout << "User stack time: " << doRandomTesting<StackAllocator<int> >(sequence) << std::endl;
    std::cout << "Built-in stack time: " << doRandomTesting<std::allocator<int> >(sequence) << std::endl;
}

TEST(testFullInsert, DISABLED_stackTest) {
    auto sequence = generateInsert(TEST_SIZE);
    std::cout << "Insert test" << std::endl;
    std::cout << "User stack time: " << doInsertTesting<StackAllocator<int> >(sequence, false) << std::endl;
    std::cout << "Built-in stack time: " << doInsertTesting<std::allocator<int> >(sequence, false) << std::endl;
}

TEST(testInsertPop, DISABLED_stackTest) {
    auto sequence = generateInsert(TEST_SIZE);
    std::cout << "InsertPop test" << std::endl;
    std::cout << "User stack time: " << doInsertTesting<StackAllocator<int> >(sequence, true) << std::endl;
    std::cout << "Built-in stack time: " << doInsertTesting<std::allocator<int> >(sequence, true) << std::endl;
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}