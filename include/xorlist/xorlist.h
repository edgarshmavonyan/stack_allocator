#pragma once
#include "cstdint"
#include "iterator.h"
#include <iostream>

// Definition

template<typename T, class Allocator = std::allocator<T> >
class XorList {
public:
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef XorListIterator<T> iterator;
    typedef std::reverse_iterator<XorListIterator<T> > reverse_iterator;
protected:
    typedef Allocator* allocator_pointer;
    typedef Allocator allocator_type;
    typedef Node<T> node;
    typedef Node<T>* node_pointer;
    typedef typename Allocator::template rebind<node>::other node_allocator_type;
    typedef std::allocator_traits<node_allocator_type > node_allocator_traits;

    node_allocator_type _alloc;
    node_pointer _start;
    node_pointer _end;
    size_t _size;


    void _free(node_pointer);

public:
    explicit XorList(const allocator_type& alloc = Allocator());

    ~XorList();

    size_type size() const;

    bool empty() const;

    void push_back(const_reference element);

    void push_front(const_reference element);

    void pop_back();

    void pop_front();

    void clear();

    iterator begin();

    iterator end();

    reverse_iterator rbegin();

    reverse_iterator rend();
};

// Implementation
#include "xorlist.ipp"