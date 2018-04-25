#include "xorlist.h"

template<typename T, class Allocator>
XorList<T, Allocator>::XorList(const allocator_type& alloc):
        _start(nullptr), _end(nullptr), _size(0), _alloc(node_allocator_type(alloc)) {}

template<typename T, class Allocator>
XorList<T, Allocator>::~XorList() {
    clear();
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::size_type
XorList<T, Allocator>::size() const {
    return _size;
}

template<typename T, class Allocator>
bool XorList<T, Allocator>::empty() const {
    return _size == 0;
};


template<typename T, class Allocator>
typename XorList<T, Allocator>::iterator
XorList<T, Allocator>::begin() {
    return iterator(_start);
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::iterator
XorList<T, Allocator>::end() {
    return iterator(nullptr, _end);
}


template<typename T, class Allocator>
typename XorList<T, Allocator>::reverse_iterator
XorList<T, Allocator>::rbegin() {
    return reverse_iterator(end());
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::reverse_iterator
XorList<T, Allocator>::rend() {
    return reverse_iterator(begin());
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::iterator
XorList<T, Allocator>::insert_after(iterator pos, const T &value) {

}

template<typename T, class Allocator>
void XorList<T, Allocator>::push_back(const_reference element) {
    node_pointer newNode = node_allocator_traits::allocate(_alloc, 1);
    node_allocator_traits::construct(_alloc, newNode, element, _end);

    if (_end != nullptr)
        _end->_neighboursXor ^= reinterpret_cast<uintptr_t>(newNode);
    else
        _start = newNode;
    _end = newNode;
    _size++;
}

template<typename T, class Allocator>
void XorList<T, Allocator>::push_front(const_reference element) {
    node_pointer newNode = node_allocator_traits::allocate(_alloc, 1);
    node_allocator_traits::construct(_alloc, newNode, element, nullptr, _start);
//    _alloc.construct(newNode, element, nullptr, _start);

    if (_start != nullptr)
        _start->_neighboursXor ^= reinterpret_cast<uintptr_t>(newNode);
    else
        _end = newNode;
    _start = newNode;
    _size++;
}

template<typename T, class Allocator>
void XorList<T, Allocator>::pop_back() {
    node_pointer toDelete = _end;
    _end = reinterpret_cast<node_pointer>(_end->_neighboursXor);
    if (_size > 1)
        _end->_neighboursXor ^= reinterpret_cast<uintptr_t>(toDelete);
    else
        _start = nullptr;
    _free(toDelete);
}

template<typename T, class Allocator>
void XorList<T, Allocator>::pop_front() {
    node_pointer toDelete = _start;
    _start = reinterpret_cast<node_pointer>(_start->_neighboursXor);
    if (_size > 1)
        _start->_neighboursXor ^= reinterpret_cast<uintptr_t>(toDelete);
    else
        _end = nullptr;
    _free(toDelete);
}

template<typename T, class Allocator>
void XorList<T, Allocator>::clear() {
    while (_size > 0)
        pop_front();
}

template<typename T, class Allocator>
void XorList<T, Allocator>::_free(node_pointer toDelete) {
    node_allocator_traits::destroy(_alloc, toDelete);
    node_allocator_traits::deallocate(_alloc, toDelete, 1);
    _size--;
}
/*
template<typename T, class Allocator>
typename XorList<T, Allocator>::node_pointer
XorList<T, Allocator>::_createNode(T&& value) {

}
*/

