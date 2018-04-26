#pragma once
#include "cstdint"
#include "node.h"
#include <iostream>

template<typename T>
class XorListIterator: public std::iterator<std::bidirectional_iterator_tag, T> {
protected:
    const static bool is_const = std::is_same<std::remove_cv_t<T>, T>::value;

    using self = XorListIterator;
    using node = Node<T>;
    using node_pointer = Node<T>*;
    using calc_type = uintptr_t;

    calc_type _current;
    calc_type _previous;

private:
    template<typename U, typename Allocator>
    friend class XorList;

    using base = std::iterator<std::bidirectional_iterator_tag, T>;

    node_pointer _cast(const calc_type& calc_ptr) const;

    calc_type _cast(const node_pointer& ptr) const;

    node_pointer _getNode();

    node_pointer _getPrevNode();

    node_pointer _getNextNode();

public:
    using value_type = typename base::value_type;
    using pointer = typename base::pointer;
    using difference_type = typename base::difference_type;
    using reference = typename base::reference;
    using iterator_category = typename base::iterator_category;
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