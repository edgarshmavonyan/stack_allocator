#pragma once
#include <vector>
#include "testConstants.h"

const size_t TEST_SIZE = 10000000;

std::vector<std::pair<TESTWORD, int> > generateSequence(size_t size) {
    std::vector<std::pair<TESTWORD, int> > result(size);
    size_t curSize = 0;

    for (size_t i = 0; i < size; i++) {
        if (curSize > 0 && rand() % 2) {
            result[i].first = TESTWORD::POP, curSize--;
        } else {
            curSize++;
            result[i].first = static_cast<TESTWORD>(abs(rand()) % 2 + 1);
            result[i].second = rand();
        }
    }
    return result;
}

std::vector<int> generateInsert(size_t size) {
    std::vector<int> result(size);
    for (size_t i = 0; i < size; i++) {
        result[i] = rand();
    }
    return result;
}