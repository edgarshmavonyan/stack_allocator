#pragma once
#include "cstdint"
/*
struct BaseNode {
protected:
    uintptr_t _neighboursXor;
    explicit BaseNode(uintptr_t neighboursXor): _neighboursXor(neighboursXor) {}
}
*/

template<typename T>
struct Node {
private:
    template<typename, class>
    friend class XorList;

    template<typename>
    friend class XorListIterator;

    T _value;
    uintptr_t _neighboursXor;

    void _changeNeighbour(Node* old, Node* now);

public:
    /*
    explicit Node(const T& value, Node* prev = nullptr, Node* next = nullptr):
            _value(value),
            BaseNode(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(next)) {}

    explicit Node(T&& value, Node* prev = nullptr, Node* next = nullptr):
            _value(std::move(value)),
            BaseNode(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(next)) {}
    */
    explicit Node(const T& value, Node* prev = nullptr, Node* next = nullptr):
            _value(value),
            _neighboursXor(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(next)) {}

    explicit Node(T&& value, Node* prev = nullptr, Node* next = nullptr):
            _value(std::move(value)),
            _neighboursXor(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(next)) {}
};

template<typename T>
void Node<T>::_changeNeighbour(Node* old, Node* now) {
    _neighboursXor ^= reinterpret_cast<uintptr_t>(old) ^ reinterpret_cast<uintptr_t>(now);
}