#pragma once
#include "cstdint"
#include "node.h"
#include <iostream>

template<typename T>
struct XorListIterator {

    template<typename U>
    friend class XorList;

    typedef T value_type;
    typedef T* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef T& reference;
    typedef std::bidirectional_iterator_tag iterator_category;

protected:
    typedef XorListIterator<T> self;
    typedef Node<T> node;
    typedef Node<T>* node_pointer;
    typedef uintptr_t calc_type;

    calc_type _current;
    calc_type _previous;

private:

    node_pointer _cast(const calc_type& calc_ptr);

    calc_type _cast(const node_pointer& ptr);

public:
    XorListIterator();

    // only for the start or for the end of a container
    explicit XorListIterator(node_pointer ptr);

    XorListIterator(node_pointer curr, node_pointer prev);

    XorListIterator(const self& other) = default;

    self& operator=(const self& other) = default;

    self& operator++();

    self operator++(int);

    self& operator--();

    self operator--(int);

    reference operator*();

    pointer operator->();

    template<typename U>
    bool friend operator==(const XorListIterator<U>& first, const XorListIterator<U>& other);

    template<typename U>
    bool friend operator!=(const XorListIterator<U>& first, const XorListIterator<U>& other);
};

// Implementation
#include "iterator.ipp"