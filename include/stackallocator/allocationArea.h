#pragma once
#include <iostream>
#include <cassert>

class AllocationArea {
private:
    friend class StackChain;

    static const std::size_t MAX_ALLOCATION = 1048576;

    void* _cur;
    std::size_t _available;
    AllocationArea* _nextArea;

    bool _checkAvailability(std::size_t requiredMemory) const;

    void* _allocate(std::size_t requiredMemory);

public:
    AllocationArea();

    ~AllocationArea();
};