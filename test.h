#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "stack.h"
#include <list>
#include <iostream>

std::vector<std::pair<int, int> > generateSequence(size_t size) {
    std::vector<std::pair<int, int> > result;
    size_t curSize = 0;
    for (size_t i = 0; i < size; i++) {
        if (curSize > 0 && rand() % 2) {
            result.emplace_back(std::make_pair(-1, -1));
        } else
            result.emplace_back(std::make_pair(1, rand() % 100500));
    }
    return result;
};

std::vector<int> generateInsert(size_t size) {
    std::vector<int> result(size);
    for (size_t i = 0; i < size; i++) {
        result[i] = rand();
    }
    return result;
}

template<class alloc>
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


template<class alloc>
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

TEST(testRandomSequence, stackTest) {
    const size_t testSize = 10000000;
    auto sequence = generateSequence(testSize);
    std::cout << "Random test" << std::endl;
    std::cout << "User stack time: " << doRandomTesting<StackAllocator<int> >(sequence) << std::endl;
    std::cout << "Built-in stack time: " << doRandomTesting<std::allocator<int> >(sequence) << std::endl;
}

TEST(testFullInsert, stackTest) {
    const size_t testSize = 10000000;
    auto sequence = generateInsert(testSize);
    std::cout << "Insert test" << std::endl;
    std::cout << "User stack time: " << doInsertTesting<StackAllocator<int> >(sequence, false) << std::endl;
    std::cout << "Built-in stack time: " << doInsertTesting<std::allocator<int> >(sequence, false) << std::endl;
}

TEST(testInsertPop, stackTest) {
    const size_t testSize = 10000000;
    auto sequence = generateInsert(testSize);
    std::cout << "InsertPop test" << std::endl;
    std::cout << "User stack time: " << doInsertTesting<StackAllocator<int> >(sequence, true) << std::endl;
    std::cout << "Built-in stack time: " << doInsertTesting<std::allocator<int> >(sequence, true) << std::endl;
}