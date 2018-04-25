#pragma once
#include <iostream>
#include <cassert>
#include <list>
#include "allocationArea.h"

// Definition

class StackChain {
private:

    using area_pointer = AllocationArea*;
    using area = AllocationArea;

    size_t _areaCount;
    area_pointer _start;
    area_pointer _cur;

    area_pointer _createNode();

public:

    StackChain();

    StackChain(const StackChain&) = delete;

    ~StackChain();

    char* allocate(size_t requiredMemory);
};

//Implementation