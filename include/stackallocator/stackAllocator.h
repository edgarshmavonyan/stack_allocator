#pragma once
#include <iostream>
#include <cassert>
#include <list>
#include <memory>
#include "stackChain.h"

// Definition

template<class T>
class StackAllocator {
public:
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    StackAllocator();

    StackAllocator(const StackAllocator&);

    explicit StackAllocator(StackChain& stackChain);

    template<class U>
    explicit StackAllocator(const StackAllocator<U>&);

    ~StackAllocator() = default;

    template<class U>
    struct rebind {
        typedef StackAllocator<U> other;
    };

    pointer allocate(size_t elementsNumber);

    void deallocate(pointer ptr, size_t size) {}

protected:
    std::shared_ptr<StackChain> _chain;
};

#include "stackAllocator.ipp"