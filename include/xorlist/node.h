#pragma once
#include "cstdint"

template<typename T>
struct Node {
    T _value;
    uintptr_t _neighboursXor;

    inline void _changeNeighbour(Node* old, Node* now);

    explicit Node(const T& value, Node* prev = nullptr, Node* next = nullptr):
            _value(value),
            _neighboursXor(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(next)) {}

    explicit Node(T&& value, Node* prev = nullptr, Node* next = nullptr):
            _value(std::move(value)),
            _neighboursXor(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(next)) {}
};

template<typename T>
inline void Node<T>::_changeNeighbour(Node* old, Node* now) {
    _neighboursXor ^= reinterpret_cast<uintptr_t>(old) ^ reinterpret_cast<uintptr_t>(now);
}