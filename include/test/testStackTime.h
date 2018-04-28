#include "testTime.h"
#include "testGeneration.h"
#include "stackallocator/stackAllocator.h"
#include <iostream>


template<typename T = int, template <typename...> class Container = std::list>
void testRandomSequence(size_t testSize) {
    auto sequence = generateSequence(testSize);
    std::cout << "Random test" << std::endl;
    std::cout << "User stack time: " << doRandomTesting<T, Container, StackAllocator>(sequence) << std::endl;
    std::cout << "Built-in stack time: " << doRandomTesting<T, Container>(sequence) << std::endl;
}

template<typename T = int, template <typename...> class Container = std::list>
void testFullInsert(size_t testSize) {
    auto sequence = generateInsert(testSize);
    std::cout << "Insert test" << std::endl;
    std::cout << "User stack time: " << doInsertTesting<T, Container, StackAllocator>(sequence, false) << std::endl;
    std::cout << "Built-in stack time: " << doInsertTesting<T, Container>(sequence, false) << std::endl;
}

template<typename T = int, template <typename...> class Container = std::list>
void testInsertPop(size_t testSize) {
    auto sequence = generateInsert(testSize);
    std::cout << "InsertPop test" << std::endl;
    std::cout << "User stack time: " << doInsertTesting<T, Container, StackAllocator>(sequence, true) << std::endl;
    std::cout << "Built-in stack time: " << doInsertTesting<T, Container>(sequence, true) << std::endl;
}

template<typename T = int, template <typename...> class Container = std::list>
void threeTestsForTime(size_t testSize) {
    testRandomSequence<T, Container>(testSize);
    testFullInsert<T, Container>(testSize);
    testInsertPop<T, Container>(testSize);
}