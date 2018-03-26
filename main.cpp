#include <iostream>
#include <list>
#include "stack.h"
#include <vector>
#include <ctime>
#include <iomanip>

std::vector<std::pair<int, int> > generateSequence(size_t size) {
    std::vector<std::pair<int, int> > result;
//    for (size_t i = 0; i < size; i++) {
    size_t curSize = 0;
    for (size_t i = 0; i < size; i++) {
        if (curSize > 0 && rand() % 2) {
            result.emplace_back(std::make_pair(-1, -1));
        } else
            result.emplace_back(std::make_pair(1, rand() % 100500));
    }
    return result;
};

template<class alloc>
double doTesting(const std::vector<std::pair<int, int> >& res) {
    std::list<int, alloc> kekos;
//    auto res = generateSequence(10000);
    clock_t t = clock();
    for (auto& el: res) {
        if (el.first == -1) {
            kekos.pop_back();
        } else
            kekos.emplace_back(el.second);
    }
    t = clock() - t;
    return double(t)/CLOCKS_PER_SEC;
}

int main() {
//    srand(time(0));
    auto result = generateSequence(10000000);
    std::cout << doTesting<StackAllocator<int> >(result) << std::endl;
    std::cout << doTesting<std::allocator<int> >(result) << std::endl;
    return 0;
}