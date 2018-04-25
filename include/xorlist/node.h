#pragma once
#include "cstdint"

template<typename T>
struct Node{
private:
    template<typename, class>
    friend class XorList;

    template<typename>
    friend class XorListIterator;

    T _value;
    uintptr_t _neighboursXor;

public:
    explicit Node(const T& value, Node* prev = nullptr, Node* next = nullptr) :
            _value(value), _neighboursXor(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(next)) {}
};