#pragma once
#include "cstdint"
#include "node.h"
#include "iterator.h"
#include <iostream>

template<typename T>
class Const_XorListIterator: public std::iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t, const T*, const T&> {
protected:

    using self = Const_XorListIterator<T>;
    using node = const Node<T>;
    using node_pointer = const Node<T>*;
    using calc_type = uintptr_t;
    using iterator = XorListIterator<T>;

    calc_type _current;
    calc_type _previous;

    // for better performance
    template<typename U, typename Allocator>
    friend class XorList;

    using base = std::iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t, const T*, const T&>;

    node_pointer _cast(const calc_type& calc_ptr) const;

    calc_type _cast(const node_pointer& ptr) const;

    inline node_pointer _getNode() const;

    inline node_pointer _getPrevNode() const;

    inline node_pointer _getNextNode() const;

public:
    using value_type = typename base::value_type;
    using pointer = typename base::pointer;
    using difference_type = typename base::difference_type;
    using reference = typename base::reference;
    using iterator_category = typename base::iterator_category;

    Const_XorListIterator();

    explicit Const_XorListIterator(node_pointer curr, node_pointer prev = nullptr);

    Const_XorListIterator(const self& other) = default;

    explicit Const_XorListIterator(const iterator& other);

    Const_XorListIterator& operator=(const self& other) = default;

    Const_XorListIterator& operator=(const iterator& other);

    self& operator++();

    self operator++(int);

    self& operator--();

    self operator--(int);

    reference operator*() const;

    pointer operator->() const;

    template<typename U>
    bool friend operator==(const Const_XorListIterator<U>& first, const Const_XorListIterator<U>& other);

    template<typename U>
    bool friend operator!=(const Const_XorListIterator<U>& first, const Const_XorListIterator<U>& other);
};

// Implementation
#include "const_iterator.ipp"