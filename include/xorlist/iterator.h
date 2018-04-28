#pragma once
#include "cstdint"
#include "node.h"
#include <iostream>

template<typename T>
class XorListIterator: public std::iterator<std::bidirectional_iterator_tag, T> {
protected:

    using self = XorListIterator<T>;
    using node = Node<T>;
    using node_pointer = Node<T>*;
    using calc_type = uintptr_t;

    calc_type _current;
    calc_type _previous;


    template<typename U, typename Allocator>
    friend class XorList;
private:
    using base = std::iterator<std::bidirectional_iterator_tag, T>;

    node_pointer _cast(const calc_type& calc_ptr) const;

    calc_type _cast(const node_pointer& ptr) const;

    inline node_pointer _getNode();

    inline node_pointer _getPrevNode();

    inline node_pointer _getNextNode();

public:
    using value_type = typename base::value_type;
    using pointer = typename base::pointer;
    using difference_type = typename base::difference_type;
    using reference = typename base::reference;
    using iterator_category = typename base::iterator_category;
public:
    XorListIterator();

    explicit XorListIterator(node_pointer curr, node_pointer prev = nullptr);

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