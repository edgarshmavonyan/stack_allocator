#pragma once
#include "testConstants.h"
#include <vector>
#include <list>


template<typename T = int, template <typename...> class Container = std::list, template<typename> class Allocator = std::allocator >
double doRandomTesting(const std::vector<std::pair<TESTWORD, T> >& sequence) {
    Container<T, Allocator<T> > tested;
    clock_t t = clock();
    for (auto& element: sequence) {
        switch(element.first) {
            case TESTWORD::POP: {
                tested.pop_back();
                break;
            }
            case TESTWORD::PUSH_BACK: {
                tested.push_back(element.second);
                break;
            }
            case TESTWORD::PUSH_FRONT: {
                tested.push_front(element.second);
                break;
            }
        }
    }
    t = clock() - t;
    return double(t)/CLOCKS_PER_SEC;
}


template<typename T = int, template <typename...> class Container = std::list, template<typename> class Allocator = std::allocator >
double doInsertTesting(const std::vector<T>& sequence, bool toErase = false) {
    Container<T, Allocator<T> > tested;
    clock_t t = clock();
    for (auto& element: sequence)
        tested.push_back(element);

    if (toErase)
        while (!tested.empty())
            tested.pop_back();

    t = clock() - t;
    return double(t)/CLOCKS_PER_SEC;
}