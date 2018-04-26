#pragma once
#include <iostream>
#include <cassert>
#include <list>
#include <memory>
#include "stackChain.h"

// Definition

template<class T>
class StackAllocator {
    template<class U>
    friend class StackAllocator;
public:
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    StackAllocator();

    explicit StackAllocator(StackChain& stackChain);

    template<class U>
    explicit StackAllocator(const StackAllocator<U>& other);

    ~StackAllocator() = default;

    template<class U>
    struct rebind {
        typedef StackAllocator<U> other;
    };

    pointer allocate(std::size_t elementsNumber);

    void deallocate(pointer ptr, size_t size) {}

    template<class T1, class T2>
    bool friend operator==(const StackAllocator<T1>& first, const StackAllocator<T2>& other);

    template<class T1, class T2>
    bool friend operator!=(const StackAllocator<T1>& first, const StackAllocator<T2>& other);

protected:
    std::shared_ptr<StackChain> _chain;
};

#include "stackAllocator.ipp"