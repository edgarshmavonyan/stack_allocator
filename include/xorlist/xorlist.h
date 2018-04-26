#pragma once
#include "cstdint"
#include "iterator.h"
#include <iostream>

// Definition

template<typename T, class Allocator = std::allocator<T> >
class XorList {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using rvalue_reference = T&&;


    using iterator = XorListIterator<T>;
    using const_iterator = XorListIterator<const T>;
    using reverse_iterator = std::reverse_iterator<XorListIterator<T> >;
    using const_reverse_iterator = std::reverse_iterator<XorListIterator<const T> >;
protected:
    using allocator_pointer = Allocator*;
    using allocator_type = Allocator;
    using node = Node<T>;
    using node_pointer = Node<T>*;
    using node_allocator_type = typename Allocator::template rebind<node>::other;
    using node_allocator_traits = std::allocator_traits<node_allocator_type > ;

    node_allocator_type _alloc;
    node_pointer _start;
    node_pointer _end;
    size_t _size;


    void _free(node_pointer toDelete);

    node_pointer _createNode(rvalue_reference value, node_pointer before, node_pointer next);

    node_pointer _createNode(const_reference value, node_pointer before, node_pointer next);

    void _hook(node_pointer curNode, node_pointer nextNode, node_pointer newNode);

    void _hookOut(node_pointer left, node_pointer right, node_pointer toDelete);

public:
    explicit XorList(const allocator_type& alloc = Allocator());

    allocator_type get_allocator() const;

    XorList(const XorList& other);

    XorList(const XorList& other, const allocator_type& alloc);

    XorList(XorList&& other);

    // to_check
    XorList(XorList&& other, const allocator_type& alloc);

    XorList& operator=(const XorList& other);

    XorList& operator=(XorList&& other);

    ~XorList();

    size_type size() const;

    bool empty() const;

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    const_iterator cbegin() const;

    const_iterator cend() const;

    reverse_iterator rbegin();

    reverse_iterator rend();

    iterator insert_after(iterator pos, const_reference value);

    iterator insert_after(iterator pos, rvalue_reference value);

    iterator insert_before(iterator pos, const_reference value);

    iterator insert_before(iterator pos, rvalue_reference value);

    reference front();

    reference back();

    void erase(iterator cur);

    void push_back(const_reference element);

    void push_back(rvalue_reference element);

    void push_front(const_reference element);

    void push_front(rvalue_reference element);

    void pop_back();

    void pop_front();

    void clear();
};

// Implementation
#include "xorlist.ipp"